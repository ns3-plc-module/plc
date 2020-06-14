/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright  (c) 2012 University of British Columbia, Vancouver
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Alexander Schloegl <alexander.schloegl@gmx.de>
 */

#include <math.h>
#include <boost/graph/copy.hpp>

#include <ns3/double.h>
#include <ns3/log.h>
#include <ns3/simulator.h>
#include <ns3/system-thread.h>

#include "plc-channel.h"
#include "plc-defs.h"
#include "plc-value.h"
#include "plc-edge.h"
#include "plc-backbone.h"
#include "plc-noise.h"
#include "plc-time.h"

namespace ns3
{

NS_LOG_COMPONENT_DEFINE ("PLC_Channel");
NS_OBJECT_ENSURE_REGISTERED (PLC_EdgeTransferUnit);
NS_OBJECT_ENSURE_REGISTERED (PLC_ChannelTransferImpl);
NS_OBJECT_ENSURE_REGISTERED (PLC_Channel);

//////////////////////////////// PLC_TrxMetaInfo ////////////////////////////////////////////////

PLC_TrxMetaInfo::PLC_TrxMetaInfo (void)
{
	m_frame = 0;
	m_message = 0;
	m_header_mcs = ModulationAndCodingScheme (BPSK_1_2, 0);
	m_payload_mcs = ModulationAndCodingScheme (BPSK_1_2, 0);
	m_header_duration = MicroSeconds(0);
	m_payload_duration = MicroSeconds(0);
}

std::ostream&
operator<<(std::ostream& os, const PLC_TrxMetaInfo& metaInfo)
{
    os << "Frame: " << *(metaInfo.GetFrame());
    os << ", Message: " << *(metaInfo.GetMessage());
    os << ", Header MCS: " << metaInfo.GetHeaderMcs();
    os << ", Header duration: " << metaInfo.GetHeaderDuration();
    os << ", Payload MCS: " << metaInfo.GetPayloadMcs();
    os << ", Payload duration: " << metaInfo.GetPayloadDuration();
    return os;
}

//////////////////////////////// PLC_EdgeTransferUnit ////////////////////////////////////////////////

TypeId
PLC_EdgeTransferUnit::GetTypeId (void)
{
	static TypeId tid = ns3::TypeId ("ns3::PLC_EdgeTransferUnit")
    		.SetParent<Object> ()
    		;
	return tid;
}

PLC_EdgeTransferUnit::PLC_EdgeTransferUnit (PLC_Edge *edge, PLC_Node *dst_node, Ptr<const SpectrumModel> sm, bool time_variant)
	: m_edge (edge), m_dst_node (dst_node), m_is_up_2_date (false)
{
	if  (time_variant)
		m_edge_transfer_vector = CreateObject<PLC_TimeVariantTransferVector>  (PLC_ConstValue (sm, PLC_Value (0, 0)));
	else
		m_edge_transfer_vector = CreateObject<PLC_TransferVector>  (PLC_ConstValue (sm, PLC_Value (0, 0)));
}

void
PLC_EdgeTransferUnit::DoDispose (void)
{
	NS_LOG_FUNCTION (this);
	m_spectrum_model = 0;
	m_edge_transfer_vector = 0;
}

void
PLC_EdgeTransferUnit::SetEdgeTransferVector (Ptr<PLC_TransferBase> ctv)
{
	NS_LOG_FUNCTION (this);
	m_edge_transfer_vector = ctv;
	m_is_up_2_date = true;
}

Ptr<PLC_TransferBase>
PLC_EdgeTransferUnit::GetEdgeTransferVector (void)
{
	NS_LOG_FUNCTION (this);
	return m_edge_transfer_vector;
}

bool
PLC_EdgeTransferUnit::IsTimeVariant (void)
{
	NS_LOG_FUNCTION (this);
	NS_ASSERT (m_edge_transfer_vector);
	bool ret = m_edge_transfer_vector->IsTimeVariant ();

	return ret;
}

void
PLC_EdgeTransferUnit::Lock(void) const
{
	m_edge_transfer_unit_mutex.Lock();
}

void
PLC_EdgeTransferUnit::Unlock(void) const
{
	m_edge_transfer_unit_mutex.Unlock();
}

///////////////////////////////////////////// PLC_ChannelTransferImpl /////////////////////////////////////////////////////////

TypeId
PLC_ChannelTransferImpl::GetTypeId  (void)
{
	static TypeId tid = ns3::TypeId ("ns3::PLC_ChannelTransferImpl")
    		.SetParent<Object>  ()
    	    .AddAttribute  ("Delay", "Transmission delay through the p2p channel",
    	    		 	 	TypeId::ATTR_GET | TypeId::ATTR_CONSTRUCT,
    	    		 	 	TimeValue  (Seconds  (0)),
    	    		 	 	MakeTimeAccessor  (&PLC_ChannelTransferImpl::m_delay),
    	    		 	 	MakeTimeChecker  ())
			.AddTraceSource  ("PLC_ChannelData",
							 "Channel Transfer Function Data after every change",
							 MakeTraceSourceAccessor  (&PLC_ChannelTransferImpl::m_channelDataTracer))
    	    ;
	return tid;
}

PLC_ChannelTransferImpl::PLC_ChannelTransferImpl (PLC_TxInterface *txInterface, PLC_RxInterface *rxInterface, Ptr<const SpectrumModel> sm, bool create_backbone_path)
	: m_spectrum_model (sm), m_txInterface (txInterface), m_rxInterface (rxInterface),
	  m_is_time_variant (false), m_ctv_is_up_2_date (false), m_is_up_2_date (false), m_update_scheduled (false)
{
	NS_LOG_FUNCTION (this);
	NS_ASSERT (txInterface->GetNodePeekPointer ()->GetGraph () == rxInterface->GetNodePeekPointer ()->GetGraph ());

	if  (create_backbone_path)
		CreateBackbonePath ();

	m_update_immediately = false;
	m_impedance_hash_sum = 0;
}

void PLC_ChannelTransferImpl::DoDispose (void)
{
	NS_LOG_FUNCTION (this);
	m_channelDataTracer(Now() + Seconds(PLC_Time::GetPeriodS()), m_channel_transfer_vector);
	m_channel_transfer_vector = 0;
	m_spectrum_model = 0;
	m_backbone_path.clear ();
	m_abs_sqr_ctf.clear ();
}

bool
PLC_ChannelTransferImpl::IsTimeVariant (void)
{
	NS_LOG_FUNCTION (this);
	return m_is_time_variant;
}

Ptr<PLC_Graph>
PLC_ChannelTransferImpl::GetGraph (void)
{
	NS_LOG_FUNCTION(this);

	NS_ASSERT (m_txInterface->GetNodePeekPointer ()->GetGraph () == m_rxInterface->GetNodePeekPointer ()->GetGraph ());
	return m_txInterface->GetNodePeekPointer ()->GetGraph ();
}

void PLC_ChannelTransferImpl::CreateBackbonePath (void)
{
	NS_LOG_FUNCTION (this);
	std::list<Ptr<PLC_Node> > shortest_path;
	std::list<Ptr<PLC_Node> >::iterator path_it;

	// first get nodes of the interface tupel
//	m_rxInterface->Lock ();
	Ptr<PLC_Node> rx_node = m_rxInterface->GetNode ();
//	m_rxInterface->Unlock ();

//	m_txInterface->Lock ();
	Ptr<PLC_Node> tx_node = m_txInterface->GetNode ();
//	m_txInterface->Unlock ();

	// PLC_Graph has shortest paths between all nodes after calling Create_Graph(),
	// which performs a Dijkstra search
//	GetGraph ()->Lock ();
	shortest_path = GetGraph ()->GetShortestPath (tx_node, rx_node);
//	GetGraph ()->Unlock ();

	// iterator over the path
	path_it = shortest_path.begin ();

	// indicates direct connection between tx_node and rx_node
	if  (path_it == shortest_path.end ()) return;

	// a backbone node is defined by its own node and both neighbor nodes on the path.
	// more than one backbone path can share the same backbone node
	Ptr<PLC_Node> branch, before, next;

	// iteration over path nodes
	before = tx_node;
	branch = *path_it;

	for  (++path_it; path_it != shortest_path.end (); path_it++) {

		next = *path_it;

		// create new backbone node
		AddBackboneBranch (branch, before, next);

		before = branch;
		branch = next;
	}

	// end node is receiver
	next = rx_node;
	AddBackboneBranch (branch, before, next);

	// register last backbone node at receiver outlet.
	// this reference is needed to update backbone path when outlet impedance changes
	if (m_rxInterface && m_rxInterface->GetOutlet())
	{
//		m_rxInterface->Lock ();
//		m_rxInterface->GetOutlet ()->Lock ();
		m_rxInterface->GetOutlet ()->RegisterBackboneBranch (* (m_backbone_path.rbegin ()));
//		m_rxInterface->GetOutlet ()->Unlock ();
//		m_rxInterface->Unlock ();
	}
}

void
PLC_ChannelTransferImpl::CalculateDirectPathPropagationDelay (void)
{
	NS_LOG_FUNCTION (this);
	double delay = 0;
	PLC_Edge *cur_edge;
	PLC_Node *cur_dst_node;
	PLC_Node *cur_src_node = m_txInterface->GetNodePeekPointer ();

	// traverse backbone path and sum up line delays
	PLC_BackbonePath::iterator bb_it;

	for  (bb_it = m_backbone_path.begin (); bb_it != m_backbone_path.end (); bb_it++) {
//		 (*bb_it)->Lock ();
		cur_dst_node =  (*bb_it)->GetNodePeekPtr ();
//		 (*bb_it)->Unlock ();

//		cur_dst_node->Lock ();
		cur_edge = cur_src_node->GetEdge (cur_dst_node);
//		cur_dst_node->Unlock ();

//		cur_edge->Lock ();
		delay += cur_edge->GetIdealPropagationDelay ();
//		cur_edge->Unlock ();

		cur_src_node = cur_dst_node;
	}

//	cur_src_node->Lock ();
	cur_edge = cur_src_node->GetEdge (m_rxInterface->GetNodePeekPointer ());
//	cur_src_node->Unlock ();

//	cur_edge->Lock ();
	delay += cur_edge->GetIdealPropagationDelay ();
//	cur_edge->Unlock ();

	m_delay = Seconds (delay);
}

Time
PLC_ChannelTransferImpl::GetDirectPathPropagationDelay (void)
{
	NS_LOG_FUNCTION (this);
	if  (m_delay == Seconds (0))
		CalculateDirectPathPropagationDelay ();

	return m_delay;
}

void
PLC_ChannelTransferImpl::AddBackboneBranch (Ptr<PLC_Node> branch, Ptr<PLC_Node> node_before, Ptr<PLC_Node> node_next)
{
	NS_LOG_FUNCTION (this);
	std::pair<unsigned int, unsigned int> tmp;
	std::pair<unsigned int, std::pair<unsigned int, unsigned int> > bb_key;
	Ptr<PLC_BackboneBranch> backbone_branch;

	// the backbone branch is defined by the nodes' IDs
//	branch->Lock ();
	unsigned int branch_id 	= branch->GetVertexId ();
//	branch->Unlock ();
//	node_before->Lock ();
	unsigned int before_id 	= node_before->GetVertexId ();
//	node_before->Unlock ();
//	node_next->Lock ();
	unsigned int next_id 	= node_next->GetVertexId ();
//	node_next->Unlock ();

	// the key for a specific backbone branch is the triple of its branch ID and its neighbour nodes' IDs in ascending order
	if  (before_id < next_id)
		tmp = std::pair<unsigned int, unsigned int>  (before_id, next_id);
	else
		tmp = std::pair<unsigned int, unsigned int>  (next_id, before_id);

	bb_key = std::pair<unsigned int, std::pair<unsigned int, unsigned int> > (branch_id, tmp);

	// insert a new backbone branch with key if it does not exist yet
//	GetGraph ()->Lock ();
	if  (!GetGraph ()->BackboneBranchExists (bb_key)) {
		backbone_branch = CreateObject<PLC_BackboneBranch>  (branch, node_before, node_next, m_spectrum_model);
		backbone_branch->Initialize ();
		GetGraph ()->RegisterBackboneBranch (bb_key, backbone_branch);
		NS_LOG_LOGIC ("Backbone Branch <" << branch_id << "," << tmp.first << "," << tmp.second << "> created");
	}
	else backbone_branch = GetGraph ()->GetBackboneBranch (bb_key);
//	GetGraph ()->Unlock ();

	// register (tx,rx)-tuple at backbone branch to be updated when a change occurs
	backbone_branch->AddInterfacePair (m_txInterface, m_rxInterface);
	m_backbone_path.push_back (backbone_branch);
}

std::list<PLC_BackboneBranch *>
PLC_ChannelTransferImpl::GetBackbonePath (void)
{
	NS_LOG_FUNCTION (this);
	PLC_BackbonePath::iterator it;
	std::list<PLC_BackboneBranch *> ret;

	for  (it = m_backbone_path.begin (); it != m_backbone_path.end (); it++) ret.push_back (PeekPointer (*it));

	return ret;
}

PLC_BackbonePath::iterator PLC_ChannelTransferImpl::BackbonePathBegin (void)
{
	NS_LOG_FUNCTION (this);
	return m_backbone_path.begin ();
}

PLC_BackbonePath::iterator PLC_ChannelTransferImpl::BackbonePathEnd (void)
{
	NS_LOG_FUNCTION (this);
	return m_backbone_path.end ();
}

void
PLC_ChannelTransferImpl::DiscoverBackboneBranches ()
{
	NS_LOG_FUNCTION (this);
	PLC_BackbonePath::iterator bb_it;
	std::vector<PLC_BackboneBranch *> branches2discover;

	boost::UGraph *graph_copy = new boost::UGraph ();
	PLC_Mutex graph_copy_mutex;

	// copy the boost graph for parallel graph discovery
//	GetGraph ()->Lock ();
	boost::copy_graph<boost::UGraph, boost::UGraph>  (* (GetGraph ()->GetGraphPtr ()), *graph_copy);
//	GetGraph ()->Unlock ();

	// get the branches to discover
	for  (bb_it = m_backbone_path.begin (); bb_it != m_backbone_path.end (); bb_it++) {
//		 (*bb_it)->Lock ();
		bool is_up_2_date =  (*bb_it)->IsUp2Date ();
//		 (*bb_it)->Unlock ();

		if  (is_up_2_date) continue;

		branches2discover.push_back (PeekPointer (*bb_it));
	}

	// set initial color of all boost vertices to white
	boost::vertex_iterator ui, ui_end;
	for  (boost::tie (ui, ui_end) = boost::vertices (*graph_copy); ui != ui_end; ++ui) {
		boost::put (boost::vertex_color, *graph_copy, *ui, boost::Color::white ());
	}

	// set vertex color of tx node, rx node and all backbone nodes to black,
	// so that the boost DFS algorithm won't proceed these nodes
//	m_txInterface->Lock ();
	PLC_Node *tx_node = m_txInterface->GetNodePeekPointer ();
//	m_txInterface->Unlock ();

//	tx_node->Lock ();
	boost::put (boost::vertex_color, *graph_copy, boost::vertex_descriptor (tx_node->GetVertexId ()), boost::Color::black ());
//	tx_node->Unlock ();

//	m_rxInterface->Lock ();
	PLC_Node *rx_node = m_rxInterface->GetNodePeekPointer ();
//	m_rxInterface->Unlock ();

//	rx_node->Lock ();
	boost::put (boost::vertex_color, *graph_copy, boost::vertex_descriptor (rx_node->GetVertexId ()), boost::Color::black ());
//	rx_node->Unlock ();

	for  (bb_it = m_backbone_path.begin (); bb_it != m_backbone_path.end (); bb_it++) {
//		 (*bb_it)->Lock ();
		PLC_Node *cur_node =  (*bb_it)->GetNodePeekPtr ();
//		 (*bb_it)->Unlock ();

//		cur_node->Lock ();
		boost::vertex_descriptor v_descr = cur_node->GetVertexId ();
//		cur_node->Unlock ();

		boost::put (boost::vertex_color, *graph_copy, v_descr, boost::Color::black ());
	}

	std::list<PLC_BackboneBranch *>::iterator bb2discover_it;

	int i;
	uint32_t size = branches2discover.size ();
	NS_ASSERT (size <= INT_MAX);

	// trigger a parallel depth first search to register this backbone branch at each
	// outlet connected to the bridge tap of the branch
//#ifdef PLC_MULTITHREADING
//#pragma omp parallel for
//#endif
	for  (i = 0; i <  (int) size; i++) {
//		branches2discover[i]->Lock ();
		if  (!branches2discover[i]->IsUp2Date ())
			branches2discover[i]->DiscoverOutlets (*graph_copy, &graph_copy_mutex);
//		branches2discover[i]->Unlock ();
	}

	delete graph_copy;

	bool set_time_variant = false;

	// check if rx load is time variant
	// and initialize channel transfer vectors of the backbone path
//	rx_node->Lock ();
	if  (!rx_node->IsOpenCircuit ()) {
		PLC_Impedance *rx_imp = rx_node->GetImpedancePeekPtr ();
//		rx_imp->Lock ();
		set_time_variant = rx_imp->IsTimeVariant ();
//		rx_imp->Unlock ();
	}
//	rx_node->Unlock ();

	PLC_Edge *cur_edge;

	// indicates direct connection between txInterface and rxInterface
	if  (m_backbone_path.size () == 0) {

//		tx_node->Lock ();
		cur_edge = tx_node->GetEdge (rx_node);
//		tx_node->Unlock ();

//		cur_edge->Lock ();
		cur_edge->InitEdgeTransferFactor (rx_node, set_time_variant);
//		cur_edge->Unlock ();

		InitializeChannelTransferVector (set_time_variant);

		return;
	}

	PLC_BackbonePath::reverse_iterator bb_rit;
	PLC_Node *first_node, *second_node;

	first_node = rx_node;

	for  (bb_rit = m_backbone_path.rbegin (); bb_rit != m_backbone_path.rend (); bb_rit++) {
		bool bb_is_time_variant;

//		 (*bb_rit)->Lock ();
		second_node =  (*bb_rit)->GetNodePeekPtr ();
		bb_is_time_variant =  (*bb_rit)->IsTimeVariant ();
//		 (*bb_rit)->Unlock ();

//		first_node->Lock ();
		cur_edge = first_node->GetEdge (second_node);
//		first_node->Unlock ();

//		cur_edge->Lock ();
		cur_edge->InitEdgeTransferFactor (first_node, set_time_variant);
//		cur_edge->Unlock ();

		if  (bb_is_time_variant) set_time_variant = true;

		first_node = second_node;
	}

	bb_it = m_backbone_path.begin ();
//	 (*bb_it)->Lock ();
	first_node =  (*bb_it)->GetNodePeekPtr ();
	if  ( (*bb_it)->IsTimeVariant ()) set_time_variant = true;
//	 (*bb_it)->Unlock ();

//	first_node->Lock ();
	cur_edge = first_node->GetEdge (tx_node);
//	first_node->Unlock ();

//	cur_edge->Lock ();
	cur_edge->InitEdgeTransferFactor (first_node, set_time_variant);
//	cur_edge->Unlock ();

	InitializeChannelTransferVector (set_time_variant);
}

void
PLC_ChannelTransferImpl::CalculateChannelTransferVector (void)
{
	NS_LOG_FUNCTION (this);

	m_update_scheduled = false;

	PLC_Node *tx_node, *rx_node, *cur_dst_node;
	PLC_Edge *cur_edge;
	PLC_EdgeTransferUnit *etu;
	PLC_TransferBase *etv;
	Ptr<PLC_TransferBase> result;

	tx_node = m_txInterface->GetNodePeekPointer ();
	rx_node = m_rxInterface->GetNodePeekPointer ();

	if  (!IsTimeVariant () && rx_node->IsTimeVariant ())
		SetTimeVariant ();

	// init channel transfer vector as neutral for multiplication.
	// will be multiplied by the edge transfer vectors of the backbone path
	if  (IsTimeVariant ())
	{
		result = CreateObject<PLC_TimeVariantTransferVector>  (m_spectrum_model, PLC_Time::GetNumTimeslots(), PLC_Value (1, 0));
	}
	else
	{
		result = CreateObject<PLC_TransferVector>  (m_spectrum_model, PLC_Value (1, 0));
	}

	if  (m_backbone_path.begin () == m_backbone_path.end ())
	{
		// direct connection
		cur_edge = tx_node->GetEdge (rx_node);

//		cur_edge->Lock ();
		etu = cur_edge->GetUpdatedEdgeTransferUnit (rx_node);
//		cur_edge->Unlock ();

		etv = etu->GetEdgeTransferVectorPtr ();

		// channel transfer vector is equal to edge transfer vector
		if  (etv->IsTimeVariant ())
		{
			SetTimeVariant ();

			if  (result->IsTimeVariant ())
			{
				*static_cast<PLC_TimeVariantTransferVector *>  (PeekPointer (result)) =
						*static_cast<PLC_TimeVariantTransferVector *>  (etv);
			}

			else
			{
				result = CreateObject<PLC_TimeVariantTransferVector>  (*static_cast<PLC_TimeVariantTransferVector *>  (etv));
			}
		}

		else
		{
			if  (result->IsTimeVariant ())
			{
				SetTimeVariant ();

				*static_cast<PLC_TimeVariantTransferVector *>  (PeekPointer (result)) =
						*static_cast<PLC_TransferVector *>  (etv);
			}

			else
			{
				*static_cast<PLC_TransferVector *>  (PeekPointer (result)) =
						*static_cast<PLC_TransferVector *>  (etv);
			}
		}

		m_channel_transfer_vector = result;

		NS_LOG_LOGIC ("Channel transfer vector result: " << *result);

		// trace channel data
		m_channelDataTracer (Simulator::Now (), result);

		NS_LOG_INFO ("Channel Transfer Data from Node" << m_txInterface->GetNodePeekPointer ()->GetVertexId () << " to Node" << m_rxInterface->GetNodePeekPointer ()->GetVertexId () << " updated");

		m_ctv_is_up_2_date = true;
		m_is_up_2_date = false;

		return;
	}

	// no direct connection between rx and tx,

	// iterate in reverse direction over the backbone path
	PLC_BackbonePath::reverse_iterator rit = m_backbone_path.rbegin ();

	// Multiply channel transfer vector with all edge transfer vectors
	// of the backbone path

	rit = m_backbone_path.rbegin ();
	cur_dst_node = rx_node;

	PLC_Node *backbone_node;
	PLC_BackboneBranch *cur_bb = PeekPointer (*rit);

	backbone_node = (*rit)->GetNodePeekPtr ();
	cur_edge = backbone_node->GetEdge (cur_dst_node);

//	cur_edge->Lock ();
	etu = cur_edge->GetUpdatedEdgeTransferUnit (cur_dst_node);
//	cur_edge->Unlock ();

	etv = etu->GetEdgeTransferVectorPtr ();
	NS_LOG_LOGIC("Edge transfer vector: " << *etv);
	result = MultiplyChannelTransferVector (result, etv);
	NS_LOG_LOGIC("Intermediate result: " << *result);

	cur_dst_node = cur_bb->GetNodePeekPtr ();

	for  (++rit; rit != m_backbone_path.rend (); rit++) {

		backbone_node = (*rit)->GetNodePeekPtr ();
		cur_edge = backbone_node->GetEdge (cur_dst_node);

//		cur_edge->Lock ();
		etu = cur_edge->GetUpdatedEdgeTransferUnit (cur_dst_node);
//		cur_edge->Unlock ();

		etv = etu->GetEdgeTransferVectorPtr ();
		NS_LOG_LOGIC("Edge transfer vector: " << *etv);
		NS_LOG_LOGIC("Before multiplication: " << *result);
		result = MultiplyChannelTransferVector (result, etv);
		NS_LOG_LOGIC("Intermediate result: " << *result);

		cur_dst_node = backbone_node;
	}

	cur_edge = tx_node->GetEdge (cur_dst_node);

//	cur_edge->Lock ();
	etu = cur_edge->GetUpdatedEdgeTransferUnit (cur_dst_node);
//	cur_edge->Unlock ();

	etv = etu->GetEdgeTransferVectorPtr ();
	NS_LOG_LOGIC("Edge transfer vector: " << *etv);
	result = MultiplyChannelTransferVector (result, etv);

	m_channel_transfer_vector = result;

	m_ctv_is_up_2_date = true;
	m_is_up_2_date = false;

	// trace channel data
	m_channelDataTracer (Simulator::Now (), result);

	NS_LOG_INFO ("Channel Transfer Data from Node" << m_txInterface->GetNodePeekPointer ()->GetVertexId () << " to Node" << m_rxInterface->GetNodePeekPointer ()->GetVertexId () << " updated");
}

Ptr<PLC_TransferBase>
PLC_ChannelTransferImpl::MultiplyChannelTransferVector (Ptr<PLC_TransferBase> result, PLC_TransferBase *ctv)
{
	NS_LOG_FUNCTION (this << result << ctv);

	NS_LOG_LOGIC("factor: " << *result);
	NS_LOG_LOGIC("multiply with: " << *ctv);

	if  (ctv->IsTimeVariant ()) {
		SetTimeVariant ();

		if  (result->IsTimeVariant ()) {
			*static_cast<PLC_TimeVariantTransferVector *>  (PeekPointer (result)) *=
					*static_cast<PLC_TimeVariantTransferVector *>  (ctv);
		}

		else {
			Ptr<PLC_TimeVariantTransferVector> tmp = CreateObject<PLC_TimeVariantTransferVector> (*static_cast<PLC_TransferVector *>  (PeekPointer (result)));

			*tmp *= *static_cast<PLC_TimeVariantTransferVector *>  (ctv);

			NS_LOG_LOGIC("tmp1: " << *tmp);

			result = tmp;
		}
	}

	else {
		if  (result->IsTimeVariant ()) {
			SetTimeVariant ();

			*static_cast<PLC_TimeVariantTransferVector *>  (PeekPointer (result)) *=
					*static_cast<PLC_TransferVector *>  (ctv);
		}

		else {
			*static_cast<PLC_TransferVector *>  (PeekPointer (result)) *=
					*static_cast<PLC_TransferVector *>  (ctv);
		}
	}

	return result;
}

Ptr<PLC_TransferBase>
PLC_ChannelTransferImpl::GetChannelTransferVector (void)
{
	NS_LOG_FUNCTION (this);

	if  (!m_ctv_is_up_2_date)
	{
#ifdef PLC_USE_IMPEDANCE_HASHING
		NS_LOG_LOGIC ("Impedance hash sum for cached channel transfer vector: " << m_impedance_hash_sum);
		NS_LOG_LOGIC ("Current impedance hash sum: " << PLC_Node::GetImpedanceHashSum ());

		if  (m_impedance_hash_sum != PLC_Node::GetImpedanceHashSum ())
		{
#endif
			CalculateChannelTransferVector ();

#ifdef PLC_USE_IMPEDANCE_HASHING
			m_impedance_hash_sum = PLC_Node::GetImpedanceHashSum ();
		}
		else
		{
			NS_LOG_LOGIC ("Known impedance hash sum. Using previously calculated channel transfer vector");
		}
#endif
	}

	return m_channel_transfer_vector;
}

void
PLC_ChannelTransferImpl::InitializeChannelTransferVector (bool set_time_variant)
{
	NS_LOG_FUNCTION (this);

	// Create data structure for the channel transfer vector
	if  (set_time_variant)
	{
		m_channel_transfer_vector = CreateObject<PLC_TimeVariantTransferVector>  (m_spectrum_model);
		m_is_time_variant = true;
	}
	else
	{
		m_channel_transfer_vector = CreateObject<PLC_TransferVector>  (m_spectrum_model);
	}
}

void
PLC_ChannelTransferImpl::SetTimeVariant (void)
{
	NS_LOG_FUNCTION (this);

	NS_LOG_LOGIC ("IsTimeVariant: " << IsTimeVariant());

	// convert channel transfer vector to time variant data if necessary
	if  (!IsTimeVariant ()) {
		NS_LOG_LOGIC ("Setting ctv time-variant");

		if  (m_channel_transfer_vector != NULL) {
			NS_LOG_LOGIC ("Old ctv: " << *m_channel_transfer_vector);
			m_channel_transfer_vector = CreateObject<PLC_TimeVariantTransferVector>
				 (*static_cast<PLC_TransferVector *> (PeekPointer (m_channel_transfer_vector)));

			NS_ASSERT (m_spectrum_model == m_channel_transfer_vector->GetSpectrumModel ());
		}
		else {
			m_channel_transfer_vector = CreateObject<PLC_TimeVariantTransferVector> (m_spectrum_model);
		}

		NS_LOG_LOGIC (*m_channel_transfer_vector);
	}

	m_is_time_variant = true;
	m_is_up_2_date = false;

	NS_LOG_INFO ("Channel transfer function between " << m_txInterface->GetNode()->GetName() << " and " << m_rxInterface->GetNode()->GetName() << " set time variant");
}

Ptr<SpectrumValue>
PLC_ChannelTransferImpl::GetAbsSqrCtf (unsigned int timeslot)
{
	NS_LOG_FUNCTION(this << timeslot);

	NS_LOG_LOGIC ("Is CTV time-variant (" << m_txInterface->GetTxIfIdx() << " -> " << m_rxInterface->GetRxIfIdx() << "): " << m_channel_transfer_vector->IsTimeVariant());

	if  (!m_is_up_2_date)
		GenerateAbsSqrCtf ();

	NS_LOG_INFO ("TX node: " << m_txInterface->GetNode()->GetName() << ", RX node: " << m_rxInterface->GetNode()->GetName());
	NS_ASSERT_MSG (timeslot < m_abs_sqr_ctf.size (), "Timeslot: " << timeslot << " ctf size: " << m_abs_sqr_ctf.size () << "\n" << *m_abs_sqr_ctf[0]);

	NS_LOG_LOGIC ("Timeslot: " << timeslot << ", AbsSqrCtf: " << *m_abs_sqr_ctf[timeslot]);

	return m_abs_sqr_ctf[timeslot];
}

void
PLC_ChannelTransferImpl::GenerateAbsSqrCtf ()
{
	NS_LOG_FUNCTION (this);
	unsigned int i, j;

	// clear cached magnitude square values
	m_abs_sqr_ctf.clear ();

	NS_LOG_INFO ("IsTimeVariant: " << IsTimeVariant() << " , tx: " << m_txInterface->GetNode()->GetName() << " , rx: " << m_rxInterface->GetNode()->GetName());

	Ptr<PLC_TransferBase> ctv = GetChannelTransferVector ();

	// compute new values
	if  (IsTimeVariant ())
	{
		PLC_TimeVariantTransferVector *tv_ctv = static_cast<PLC_TimeVariantTransferVector *>  (PeekPointer (ctv));

		for  (i = 0; i < PLC_Time::GetNumTimeslots(); i++)
		{
			Ptr<SpectrumValue> abs_sqr_ctf = Create<SpectrumValue> (m_spectrum_model);

			PLC_ValueSpectrum vs =  (*tv_ctv)[i];

			Values::iterator it;
			for  (it = abs_sqr_ctf->ValuesBegin (), j = 0; it != abs_sqr_ctf->ValuesEnd (); it++, j++)
			{
				PLC_Value value = vs[j];
				*it = pow (real (value), 2) + pow (imag (value), 2);
			}

			m_abs_sqr_ctf.push_back (abs_sqr_ctf);
		}

		NS_LOG_LOGIC ("PLC_ChannelTransferImpl: Time variant magnitude square channel transfer function created; size: " << m_abs_sqr_ctf.size());

	}
	else
	{
		PLC_TransferVector *tiv_ctv = static_cast<PLC_TransferVector *>  (PeekPointer (ctv));
		NS_LOG_INFO ("ctv: " << *tiv_ctv);
		Ptr<SpectrumValue> abs_sqr_ctf = Create<SpectrumValue> (m_spectrum_model);

		Values::iterator it;
		for  (it = abs_sqr_ctf->ValuesBegin (), j = 0; it != abs_sqr_ctf->ValuesEnd (); it++, j++)
		{
			PLC_Value value =  (*tiv_ctv)[j];
			*it = pow (real (value), 2) + pow (imag (value), 2);
		}

		m_abs_sqr_ctf.push_back (abs_sqr_ctf);

		NS_LOG_LOGIC ("PLC_ChannelTransferImpl: Time invariant magnitude square channel transfer function created: " << *abs_sqr_ctf);
	}

	NS_LOG_INFO ("TX node: " << m_txInterface->GetNode()->GetName() << ", RX node: " << m_rxInterface->GetNode()->GetName());

	m_is_up_2_date = true;
}

Ptr<SpectrumValue>
PLC_ChannelTransferImpl::CalculateRxPowerSpectralDensity (Ptr<const SpectrumValue> txPsd, Timeslot timeslot)
{
	NS_LOG_FUNCTION (this << txPsd << timeslot);

	Ptr<SpectrumValue> ret = Create<SpectrumValue> (txPsd->GetSpectrumModel ());
	Ptr<SpectrumValue> abs_sqr_ctv = GetAbsSqrCtf (timeslot);

	// rxPsd = txPsd * |H(f)|^2
	*ret =  (*txPsd) *  (*abs_sqr_ctv);

	NS_LOG_LOGIC ("RxPsd for timeslot " << timeslot << ":\n" << *ret);

	return ret;
}

void
PLC_ChannelTransferImpl::SetOutOfDate (void)
{
	NS_LOG_FUNCTION (this);
	m_ctv_is_up_2_date = false;
	m_is_up_2_date = false;

	// immediate recalculation for correct channel transfer vector tracing.
	// m_update_scheduled flag to avoid multiple recalculation to the same point in simulation time
	if  (m_update_immediately && !m_update_scheduled)
	{
		Simulator::ScheduleNow (&PLC_ChannelTransferImpl::CalculateChannelTransferVector, this);
		m_update_scheduled = true;
	}
}

///////////////////////////////////// PLC_Channel ////////////////////////////////////////////////////////

TypeId
PLC_Channel::GetTypeId  (void)
{
	static TypeId tid = ns3::TypeId ("ns3::PLC_Channel")
    		.SetParent<Channel>  ()
    	    .AddTraceSource ("PLC_ChannelState",
    	                     "Trace occupancy of the channel",
    	                     MakeTraceSourceAccessor (&PLC_Channel::m_occupancyLogger))
			.AddTraceSource ("PLC_ActiveTransmitters",
							 "Trace active transmission sources",
							 MakeTraceSourceAccessor (&PLC_Channel::m_activeTxIfLogger))
			;
	return tid;
}

PLC_Channel::PLC_Channel (Ptr<PLC_Graph> graph) : m_graph (graph), /*m_numRealTxPhys (0),*/ m_timeslot_tasks_scheduled (false)
{
	graph->SetChannel(this);
}

PLC_Channel::PLC_Channel (void)
{
	NS_LOG_FUNCTION (this);
	m_graph = 0;
	m_timeslot_tasks_scheduled = false;
}

PLC_Channel::~PLC_Channel (void)
{
	NS_LOG_FUNCTION (this);
}

void PLC_Channel::DoInitialize (void)
{
	NS_LOG_FUNCTION (this);
#ifdef PLC_INFO_SCHEDULE
	Simulator::Schedule (Seconds (0), &PLC_Channel::ProcessTimeslotTasks, this, 0);
#endif
	Channel::DoInitialize ();
}

void PLC_Channel::DoDispose (void)
{
	NS_LOG_FUNCTION (this);
	// Dispose all connected instances for correct cleanup
	std::vector<Ptr<PLC_TxInterface> >::iterator txit;
	for  (txit = m_txInterfaces.begin (); txit != m_txInterfaces.end (); txit++)
	{
		(*txit) = 0;
	}
	m_txInterfaces.clear ();

	std::vector<Ptr<PLC_RxInterface> >::iterator rxit;
	for  (rxit = m_rxInterfaces.begin (); rxit != m_rxInterfaces.end (); rxit++)
	{
		 (*rxit) = 0;
	}
	m_rxInterfaces.clear ();

	std::vector<Ptr<NetDevice> >::iterator devit;
	for  (devit = m_devices.begin (); devit != m_devices.end (); devit++)
	{
		(*devit) = 0;
	}
	m_devices.clear ();

	m_transmission_descriptors.clear ();

	m_graph = 0;
	Channel::DoDispose ();
}

void
PLC_Channel::SetGraph(Ptr<PLC_Graph> graph)
{
	NS_LOG_FUNCTION(this);
	m_graph = graph;
	graph->SetChannel(this);
}

void
PLC_Channel::InitTransmissionChannels (void)
{
	NS_LOG_FUNCTION (this);
	NS_ASSERT_MSG (m_graph, "PLC graph not set");
	m_graph->CreatePLCGraph ();

	for  (size_t i = 0; i < m_txInterfaces.size (); i++)
	{
		 m_txInterfaces[i]->InitializeChannelTransferImpls ();
	}
}

void
PLC_Channel::CalcTransmissionChannels (void)
{
	NS_LOG_FUNCTION (this);

#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for  (size_t i = 0; i < m_txInterfaces.size (); i++)
	{
		int thread = omp_get_thread_num();
		NS_LOG_LOGIC ("Num threads: " << omp_get_num_threads ());
		NS_LOG_LOGIC ("Initialize channel calculation, thread " << thread);
		m_txInterfaces[i]->Lock ();
		m_txInterfaces[i]->CalculateChannels ();
		m_txInterfaces[i]->Unlock ();
		NS_LOG_LOGIC ("Channel calculation complete, thread " << thread);
	}
}

Ptr<PLC_TransferBase>
PLC_Channel::GetChannelTransferData(uint32_t txId, uint32_t rxId)
{
	NS_LOG_FUNCTION (this << txId << rxId);
	Ptr<PLC_TxInterface> txIf = GetTxInterface(txId);
	Ptr<PLC_RxInterface> rxIf = GetRxInterface(rxId);
	Ptr<PLC_ChannelTransferImpl> ch_impl = txIf->GetChannelTransferImpl(PeekPointer(rxIf));

	if (ch_impl)
	{
		return ch_impl->GetChannelTransferVector();
	}
	else
	{
		return NULL;
	}
}

uint32_t
PLC_Channel::GetNTxInterfaces (void) const
{
	NS_LOG_FUNCTION (this);
	return m_txInterfaces.size ();
}

Ptr<PLC_TxInterface>
PLC_Channel::GetTxInterface (uint32_t i) const
{
	NS_LOG_FUNCTION (this);
	NS_ASSERT (i > 0);
	NS_ASSERT (i <= m_txInterfaces.size ());
	return m_txInterfaces[i-1];
}

uint32_t
PLC_Channel::AddTxInterface (Ptr<PLC_TxInterface> txInterface)
{
	NS_LOG_FUNCTION  (this << txInterface);
	m_txInterfaces.push_back (txInterface);

	return m_txInterfaces.size ();
}

uint32_t
PLC_Channel::AddRxInterface (Ptr<PLC_RxInterface> rxInterface)
{
	NS_LOG_FUNCTION  (this << rxInterface);
	m_rxInterfaces.push_back (rxInterface);
	return m_rxInterfaces.size ();
}

uint32_t
PLC_Channel::GetNRxInterfaces (void) const
{
	NS_LOG_FUNCTION_NOARGS();
	return m_rxInterfaces.size ();
}

Ptr<PLC_RxInterface>
PLC_Channel::GetRxInterface (uint32_t i) const
{
	NS_LOG_FUNCTION(i);
	NS_ASSERT (i > 0);
	NS_ASSERT (i <= m_rxInterfaces.size ());
	return m_rxInterfaces[i-1];
}

uint32_t
PLC_Channel::AddDevice (Ptr<NetDevice> dev)
{
	NS_LOG_FUNCTION  (this << dev);
	m_devices.push_back (dev);
	return m_devices.size ();
}

std::size_t
PLC_Channel::GetNDevices (void) const
{
	NS_LOG_FUNCTION (this);
	return m_devices.size ();
}

Ptr<NetDevice> PLC_Channel::GetDevice  (std::size_t i) const
{
	NS_LOG_FUNCTION (this);
	return m_devices[i];
}

void
PLC_Channel::TransmissionInitialize (uint32_t txId, Ptr<const SpectrumValue> txPsd, Time duration, Ptr<const PLC_TrxMetaInfo> metaInfo)
{
	NS_LOG_FUNCTION (this << txPsd << duration << metaInfo);
	NS_ASSERT (txId > 0);
	NS_ASSERT (txId <= m_txInterfaces.size ());

	// BUG workaround
	if (m_transmitting.find (txId) != m_transmitting.end ()) return;

	NS_LOG_INFO ("Initializeing transmission from TX-Interface: " << txId << ", duration: " << duration);

	// Get transmission interface
	Ptr<PLC_TxInterface> txInterface = GetTxInterface (txId);

	// trace channel occupancy
	m_occupancyLogger(Now(), txId, true);

	// transmission data, i.e. the rx PSDs, will be cached for the transmission
	// create entry for txId if not existing yet
	if  (m_transmission_descriptors.find (txId) == m_transmission_descriptors.end ())
	{
		NS_LOG_LOGIC ("Created transmission descriptor map for tx interface " << txId);
		m_transmission_descriptors[txId] = PLC_ReceiveDescriptorMap ();
	}

	// BUG
//	NS_ASSERT (m_transmitting.find (txId) == m_transmitting.end ());
	m_transmitting.insert (txId);

	// Log active transmitters
	m_activeTxIfLogger(Now(), m_transmitting);

	if (g_log.IsEnabled (ns3::LOG_LOGIC))
	{
		std::clog << Now() << " Transmitting:";
		std::set<uint32_t>::iterator it;
		for (it = m_transmitting.begin(); it != m_transmitting.end(); it++)
		{
			std::clog << " " << (int) *it << " " << GetTxInterface(*it)->GetNode()->GetName();
		}
		std::clog << std::endl;
	}

	Timeslot cur_timeslot = GetCurrentTimeslot ();
	Time max_delay = Seconds (0);

	PLC_ReceiveDescriptorMap& rxMap = m_transmission_descriptors[txId];

	uint32_t rxId;
//#ifdef PLC_MULTITHREADING
//#pragma omp parallel for
//#endif
	for  (rxId = 1; rxId <= m_rxInterfaces.size (); rxId++)
	{
		Ptr<PLC_RxInterface> rx = GetRxInterface(rxId);
		if  (rx->GetNode () == txInterface->GetNode ()) continue;

		PLC_ChannelTransferImpl *ch_impl;
		if  ((ch_impl = txInterface->GetChannelTransferImpl (PeekPointer (rx))) == NULL)
		{
			// continue if channel implementation doesn't exist  (e.g. rxInterface is out of range)
			NS_LOG_INFO ("No channel implementation from txInterface" << txId << " to rxInterface" << rxId << " found!");
			continue;
		}

		// TODO: if rxPsd will arrive at receiver only the next timeslot then choose the right rxPSD, or:
		// delay becomes dispensable for symbol level time resolution, as duration << t_symbol
		Time delay = ch_impl->GetDirectPathPropagationDelay ();
		if  (delay > max_delay) max_delay = delay;

		Ptr<const SpectrumValue> cur_rxPsd;
		if  (ch_impl->IsTimeVariant ()) {
			Timeslot end_timeslot = PLC_Time::GetTimeslot (Simulator::Now () + duration);

			NS_ASSERT (cur_timeslot < INT_MAX);
			NS_ASSERT (end_timeslot < INT_MAX);
			NS_ASSERT (PLC_Time::GetNumTimeslots() < INT_MAX);

			if  (rxMap.find (rxId) == rxMap.end ())
			{
				PLC_RxPsdMap rxPsdMap;

				MakeRxPsdMapEntries (cur_timeslot, end_timeslot, rxPsdMap, ch_impl, txPsd);
				rxMap[rxId] = rxPsdMap;
			}
			else
			{
				MakeRxPsdMapEntries (cur_timeslot, end_timeslot, rxMap[rxId], ch_impl, txPsd);
			}

			cur_rxPsd = rxMap[rxId][cur_timeslot].second;
		}
		else
		{
			if (rxMap.find (rxId) == rxMap.end ())
			{
				rxMap[rxId] = PLC_RxPsdMap ();
			}

			// time invariant value supposed to have always key = 0 in receive psd map
			PLC_RxPsdMap& rxPsdMap = rxMap[rxId];

			if  (rxPsdMap.size () > 1 || rxPsdMap.find (0) == rxPsdMap.end ())
			{
				rxPsdMap.clear ();
			}

//			ch_impl->Lock ();
			Ptr<SpectrumValue> rxPsd = ch_impl->CalculateRxPowerSpectralDensity (txPsd, 0);
//			ch_impl->Unlock ();
			rxPsdMap[0] = std::pair<Timeslot, Ptr<SpectrumValue> >  (0, rxPsd);

			cur_rxPsd = rxPsdMap[0].second;
		}

		Ptr<Node> rxNode = rx->GetObject<Node> ();
		NS_ASSERT_MSG(rxNode, "RX Interface not aggregated to an instance of ns3::Node");

		// Schedule reception
		NS_LOG_LOGIC ("RxPsd from " << txId << " to " << rxId << " " << *cur_rxPsd);
		Simulator::ScheduleWithContext (rxNode->GetId(), delay, &PLC_RxInterface::InitializeRx, rx, txId, cur_rxPsd, duration, metaInfo);
//		Simulator::ScheduleWithContext (rxNode->GetId(), delay, &PLC_Channel::InvokeReception, this, rx, txId, cur_rxPsd, duration, metaInfo);
	}

	// free the channel after transmission
	Simulator::Schedule(duration, &PLC_Channel::TransmissionEnd, this, txId, max_delay);

	// schedule next time slot task for updating rxPsds of active transmissions
	ScheduleNextTimeslotTasks ();
}

void
PLC_Channel::InvokeReception(Ptr<PLC_RxInterface> rxIf, uint32_t txId, Ptr<const SpectrumValue> rxPsd, Time duration, Ptr<const PLC_TrxMetaInfo> metaInfo)
{

}


void
PLC_Channel::MakeRxPsdMapEntries (Timeslot cur_timeslot, Timeslot end_timeslot, PLC_RxPsdMap& rxPsdMap, PLC_ChannelTransferImpl *ch_impl, Ptr<const SpectrumValue> txPsd)
{
	NS_LOG_FUNCTION (this << "Timeslot range: " << cur_timeslot << end_timeslot);
	NS_ASSERT (cur_timeslot <= INT_MAX && end_timeslot <= INT_MAX);

	int ts;
	if  (end_timeslot < cur_timeslot) {
		for  (ts =  (int) cur_timeslot; ts <  (int) PLC_Time::GetNumTimeslots(); ts++) {
//			ch_impl->Lock ();
			Ptr<SpectrumValue> rxPsd = ch_impl->CalculateRxPowerSpectralDensity (txPsd, ts);
//			ch_impl->Unlock ();
			rxPsdMap[ts] = std::pair<Timeslot, Ptr<SpectrumValue> >  (ts, rxPsd);
		}
		for  (ts = 0; ts <=  (int) end_timeslot; ts++) {
//			ch_impl->Lock ();
			Ptr<SpectrumValue> rxPsd = ch_impl->CalculateRxPowerSpectralDensity (txPsd, ts);
//			ch_impl->Unlock ();
			rxPsdMap[ts] = std::pair<Timeslot, Ptr<SpectrumValue> >  (ts, rxPsd);
		}
	}
	else {
		for  (ts =  (int) cur_timeslot; ts <=  (int) end_timeslot; ts++) {
//			ch_impl->Lock ();
			Ptr<SpectrumValue> rxPsd = ch_impl->CalculateRxPowerSpectralDensity (txPsd, ts);
//			ch_impl->Unlock ();
			rxPsdMap[ts] = std::pair<Timeslot, Ptr<SpectrumValue> >  (ts, rxPsd);
		}
	}
}

bool
PLC_Channel::TransmissionEnd (uint32_t srcId, Time propagation_delay)
{
	NS_LOG_FUNCTION  (this << srcId << propagation_delay);

	NS_ASSERT (m_transmitting.find (srcId) != m_transmitting.end ());
	m_transmitting.erase (srcId);
	m_propagating.insert (srcId);

	// Log active transmitters
	m_activeTxIfLogger(Now(), m_transmitting);

	Simulator::Schedule (propagation_delay, &PLC_Channel::PropagationCompleteEvent, this, srcId);

	return true;
}

void
PLC_Channel::PropagationCompleteEvent (uint32_t srcId)
{
	NS_LOG_FUNCTION  (this << srcId);

	NS_ASSERT (m_propagating.find (srcId) != m_transmitting.end ());
	m_propagating.erase (srcId);

	m_occupancyLogger(Now(), srcId, false);
}

Timeslot
PLC_Channel::GetCurrentTimeslot (void)
{
	NS_LOG_FUNCTION (this);
	return PLC_Time::GetTimeslot (Simulator::Now ());
}

Time
PLC_Channel::GetRemainingSlotTime (Time time)
{
	NS_LOG_FUNCTION (this);
	return Seconds ( (PLC_Time::GetResolutionS() - fmod (time.GetSeconds (), PLC_Time::GetResolutionS())));
}

void
PLC_Channel::ProcessTimeslotTasks (Timeslot timeslot)
{
	NS_LOG_FUNCTION (this << "Timeslot: " << timeslot);
	UpdateReceivePSDs (timeslot);

#ifdef PLC_INFO_SCHEDULE
	Simulator::Schedule (Seconds (PLC_Time::GetResolutionS()), &PLC_Channel::ProcessTimeslotTasks, this,  (++timeslot) % PLC_Time::GetNumTimeslots());
#else
	if  (m_transmitting.size () > 0 || m_propagating.size () > 0)
	{
		// while at least one transmission is active all corresponding rx PSDs have to be updated for every time slot in advance
		Simulator::Schedule (Seconds (PLC_Time::GetResolutionS()), &PLC_Channel::ProcessTimeslotTasks, this,  (++timeslot) % PLC_Time::GetNumTimeslots());
	}
	else
	{
//		m_schedule_mutex.Lock ();
		m_timeslot_tasks_scheduled = false;
//		m_schedule_mutex.Unlock ();
	}
#endif
}

void
PLC_Channel::ScheduleNextTimeslotTasks ()
{
	NS_LOG_FUNCTION (this);
//	m_schedule_mutex.Lock ();
	// conditionally schedule next time slot task
	if  (!m_timeslot_tasks_scheduled) {

		Time residual_time = GetRemainingSlotTime (Simulator::Now ());
		Simulator::Schedule (residual_time, &PLC_Channel::ProcessTimeslotTasks, this,  (GetCurrentTimeslot () + 1) % PLC_Time::GetNumTimeslots());

		m_timeslot_tasks_scheduled = true;
	}
//	m_schedule_mutex.Unlock ();
}

void
PLC_Channel::UpdateReceivePSDs (Timeslot timeslot, bool channel_changed)
{
	NS_LOG_FUNCTION (this << timeslot << channel_changed);
	// if the time slot advances or if an network impedance abruptly changes all currently used PSD values have to be updated

	NS_LOG_INFO ("PLC_Channel::UpdateReceivePSDs (), Timeslot: " << timeslot << ", active transmissions: " << m_transmitting.size());
	std::set<uint32_t>::iterator tx_it;

	if (channel_changed)
	{
		std::vector<Ptr<PLC_TxInterface> > txInterfaces;
		for  (tx_it = m_transmitting.begin (); tx_it != m_transmitting.end (); tx_it++)
		{
			txInterfaces.push_back (GetTxInterface(*tx_it));
		}

		size_t i;
#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
		for (i = 0; i < txInterfaces.size (); i++)
		{
			txInterfaces[i]->Lock ();

			uint32_t rxId;
			for  (rxId = 1; rxId <= m_rxInterfaces.size (); rxId++)
			{
				Ptr<PLC_RxInterface> rx = GetRxInterface(rxId);

				if  (rx->GetNode () == txInterfaces[i]->GetNode ()) continue;

				PLC_ChannelTransferImpl *ch_impl;
				if  ((ch_impl = txInterfaces[i]->GetChannelTransferImpl (PeekPointer (rx))) == NULL) continue;

				ch_impl->Lock ();
				ch_impl->GetChannelTransferVector ();
				ch_impl->Unlock ();
			}

			txInterfaces[i]->Unlock ();
		}
	}

	// foreach active transmission
	for  (tx_it = m_transmitting.begin (); tx_it != m_transmitting.end (); tx_it++) {
		NS_LOG_LOGIC ("TX interface id: " << *tx_it);

		NS_ASSERT (m_transmission_descriptors.find (*tx_it) != m_transmission_descriptors.end ());
		Ptr<PLC_TxInterface> tx = GetTxInterface(*tx_it);

		// get cached rx PSDs
		PLC_ReceiveDescriptorMap& rxMap = m_transmission_descriptors[*tx_it];
		NS_LOG_LOGIC ("RxMap size of TxInterface" << *tx_it << " " << rxMap.size());

		uint32_t rxId;
		for  (rxId = 1; rxId <= m_rxInterfaces.size (); rxId++) {
			Ptr<PLC_RxInterface> rx = GetRxInterface(rxId);

			if  (rx->GetNode () == tx->GetNode ()) continue;

			PLC_ChannelTransferImpl *ch_impl;
			if  ((ch_impl = tx->GetChannelTransferImpl (PeekPointer (rx))) == NULL) continue;

			NS_ASSERT (rxMap.find (rxId) != rxMap.end ());

			if  (!ch_impl->IsTimeVariant ())
			{
				if  (rxMap[rxId].find (0) == rxMap[rxId].end ())
				{
					NS_LOG_INFO ("Recalculating non-time-varying receive PSD of signal transmitted from PHY (" << tx->GetNode ()->GetName () << ") to PHY  (" << rx->GetNode ()->GetName () << ")");
					// recalculate rxPsd
					Ptr<SpectrumValue> rxPsd = ch_impl->CalculateRxPowerSpectralDensity (tx->GetTxPsd (*tx_it), 0);
					rxMap[rxId][0] = std::pair<Timeslot, Ptr<SpectrumValue> > (0, rxPsd);
				}
				else if (channel_changed == false) continue;

				// notify all receiver interfaces of PSD change
				rx->RxPsdChanged (*tx_it, rxMap[rxId][0].second);
			}

			else
			{
				if  (rxMap[rxId].find (timeslot) == rxMap[rxId].end ())
				{
					NS_LOG_INFO ("Recalculating time-varying receive PSD of signal transmitted from PHY (" << tx->GetNode ()->GetName () << ") to PHY  (" << rx->GetNode ()->GetName () << ")");
					// recalculate rxPsd
					Ptr<SpectrumValue> rxPsd = ch_impl->CalculateRxPowerSpectralDensity (tx->GetTxPsd (*tx_it), timeslot);
					rxMap[rxId][timeslot] = std::pair<Timeslot, Ptr<SpectrumValue> > (timeslot, rxPsd);
				}

				// notify all receiver interfaces of PSD change
				rx->RxPsdChanged (*tx_it, rxMap[rxId][timeslot].second);
			}
		}
	}
}

void PLC_Channel::DeleteOutOfDatePSDs (Ptr<PLC_TxInterface> tx, Ptr<PLC_RxInterface> rx)
{
	NS_LOG_FUNCTION(this << tx << rx);
	// deletion of cached rx PSDs from txInterface to rxInterface induces
	// recalculation when needed next time, i.e. the values will be up to date
	m_transmission_descriptors[tx->GetTxIfIdx ()][rx->GetRxIfIdx ()].clear ();
}

}

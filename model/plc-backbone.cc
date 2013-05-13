/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2012 University of British Columbia, Vancouver
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

#include "ns3/plc-backbone.h"
#include "ns3/plc-node.h"
#include "ns3/plc-channel.h"
#include "ns3/plc-defs.h"
#include "ns3/plc-undirected-dfs.h"
#include "ns3/plc-value.h"
#include "ns3/plc-visitor.h"
#include "ns3/log.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE("PLC_BackboneBranch");
NS_OBJECT_ENSURE_REGISTERED (PLC_BackboneBranch);

/**
 *
 * @return
 */
TypeId PLC_BackboneBranch::GetTypeId (void)
{
	static TypeId tid = ns3::TypeId("ns3::PLC_BackboneBranch")
    		.SetParent<Object> ()
    		;
	return tid;
}

PLC_BackboneBranch::PLC_BackboneBranch(Ptr<PLC_Node> node, Ptr<PLC_Node> before, Ptr<PLC_Node> next, Ptr<const SpectrumModel> sm)
: m_spectrum_model(sm), m_node(node), m_node_before(before), m_node_next(next),
  m_is_up_2_date(false), m_is_time_variant(false)
{
	m_equivalent_bridge_tap_impedance = CreateObject<PLC_FreqSelectiveImpedance> (sm);

	this->m_parallel_output_impedances[PeekPointer(before)] = NULL;
	this->m_parallel_output_impedances[PeekPointer(next)] 	= NULL;

	std::pair<unsigned int, unsigned int> tmp;
	std::pair<unsigned int, std::pair<unsigned int, unsigned int> > bb_key;

	// the backbone branch is defined by the nodes' IDs
	node->Lock ();
	unsigned int branch_id 	= node->GetVertexId ();
	node->Unlock ();
	before->Lock ();
	unsigned int before_id 	= before->GetVertexId ();
	before->Unlock ();
	next->Lock ();
	unsigned int next_id 	= next->GetVertexId ();
	next->Unlock ();

	// the key for a specific backbone branch is the triple of its branch ID and its neighbor nodes' IDs in ascending order
	if  (before_id < next_id)
		tmp = std::pair<unsigned int, unsigned int>  (before_id, next_id);
	else
		tmp = std::pair<unsigned int, unsigned int>  (next_id, before_id);

	m_key = std::pair<unsigned int, std::pair<unsigned int, unsigned int> > (branch_id, tmp);
}

void PLC_BackboneBranch::DoStart(void)
{
	m_node->AssociateBackboneBranch(this);
}

void PLC_BackboneBranch::DoDispose(void)
{
	m_spectrum_model = 0;
	m_node = 0;
	m_node_before = 0;
	m_node_next = 0;
	m_equivalent_bridge_tap_impedance = 0;
	m_parallel_output_impedances.clear();
	m_registered_ifPairs.clear();
}

void
PLC_BackboneBranch::AddInterfacePair(PLC_TxInterface *txInterface, PLC_RxInterface *rxInterface)
{
	this->m_registered_ifPairs.insert(std::pair<PLC_TxInterface *, PLC_RxInterface *> (txInterface, rxInterface));
}

void
PLC_BackboneBranch::DiscoverOutlets(boost::UGraph& graph_copy, PLC_Mutex *graph_copy_mutex)
{
	PLC_LOG_FUNCTION(this);
  	PLC_Node *branch_node = this->GetNodePeekPtr();

  	NS_LOG_DEBUG ("Discovering outlets affecting BackboneBranch <" << m_key.first << "," << m_key.second.first << "," << m_key.second.second << ">");

	PLC_OutletDiscoverVisitor vis(this);

   	boost::VertexColorMap vertex_color_map = boost::get(boost::vertex_color, graph_copy);
   	boost::EdgeColorMap edge_color_map 	= boost::get(boost::edge_color, graph_copy);
   	boost::vertex_descriptor backbone_vertex = boost::vertex_descriptor(branch_node->GetVertexId());

    boost::detail::plc_undir_dfv_impl<boost::UGraph, PLC_OutletDiscoverVisitor, boost::VertexColorMap, boost::EdgeColorMap>
    (graph_copy, backbone_vertex, vis, vertex_color_map, edge_color_map, graph_copy_mutex);

  	this->m_is_up_2_date = true;
}

void
PLC_BackboneBranch::CalculateEquivalentBridgeTapImpedance(void)
{
	PLC_LOG_FUNCTION(this);
	if (this->m_is_time_variant && !this->m_equivalent_bridge_tap_impedance->IsTimeVariant()) {
		this->m_equivalent_bridge_tap_impedance = CreateObject<PLC_TimeVariantFreqSelectiveImpedance> (this->m_spectrum_model);
	}

	this->m_node->Lock();
	PLC_NodeOutEdgesMap outEdges = m_node->GetEdges();
	this->m_node->Unlock();

	if (outEdges.size() > 2) {
		if (this->m_equivalent_bridge_tap_impedance->IsTimeVariant())
			*static_cast<PLC_TimeVariantFreqSelectiveValue *> (PeekPointer(this->m_equivalent_bridge_tap_impedance)) = PLC_ConstValue(this->m_spectrum_model, PLC_Value(0,0));
		else
			*static_cast<PLC_FreqSelectiveValue *> (PeekPointer(this->m_equivalent_bridge_tap_impedance)) = PLC_ConstValue(this->m_spectrum_model, PLC_Value(0,0));

		PLC_NodeOutEdgesMap::iterator it;
		for (it = outEdges.begin(); it != outEdges.end(); it++) {
			if (it->first == this->m_node_before || it->first == this->m_node_next) continue;

			PLC_Edge *cur_edge = PeekPointer(it->second);

			cur_edge->Lock();
			PLC_Impedance *input_impedance = cur_edge->GetInputImpedance(it->first);
			cur_edge->Unlock();

			if (input_impedance->IsTimeVariant())
				this->SetTimeVariant();

			input_impedance->Lock();
			AddInverseValue(PeekPointer(this->m_equivalent_bridge_tap_impedance), input_impedance);
			input_impedance->Unlock();
		}

		if (this->m_equivalent_bridge_tap_impedance->IsTimeVariant())
			*static_cast<PLC_TimeVariantFreqSelectiveValue *> (PeekPointer(this->m_equivalent_bridge_tap_impedance)) = 1 / (*static_cast<PLC_TimeVariantFreqSelectiveValue *> (PeekPointer(this->m_equivalent_bridge_tap_impedance)));
		else
			*static_cast<PLC_FreqSelectiveValue *> (PeekPointer(this->m_equivalent_bridge_tap_impedance)) = 1 / (*static_cast<PLC_FreqSelectiveValue *> (PeekPointer(this->m_equivalent_bridge_tap_impedance)));
	}

	this->m_is_up_2_date = true;
}

void
PLC_BackboneBranch::SetTimeVariant(void)
{
	this->m_is_time_variant = true;
	PLC_InterfaceTupel::iterator it;

	if (!this->m_equivalent_bridge_tap_impedance->IsTimeVariant())
	{
		NS_ASSERT(this->m_equivalent_bridge_tap_impedance->GetValueType() == PLC_ValueBase::FREQ_SELECTIVE);
		this->m_equivalent_bridge_tap_impedance = CreateObject<PLC_TimeVariantFreqSelectiveImpedance>(*(static_cast<PLC_FreqSelectiveImpedance *> (PeekPointer(this->m_equivalent_bridge_tap_impedance))));
	}

	for (it = this->m_registered_ifPairs.begin(); it != this->m_registered_ifPairs.end(); it++)
	{
		it->first->Lock();
		PLC_ChannelTransferImpl *cur_channel_ti = it->first->GetChannelTransferImpl(it->second);
		it->first->Unlock();

		cur_channel_ti->SetTimeVariant();
	}
}

}

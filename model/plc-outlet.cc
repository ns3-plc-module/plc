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

#include "ns3/plc-outlet.h"
#include "ns3/plc-channel.h"
#include "ns3/log.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("PLC_Outlet");
NS_OBJECT_ENSURE_REGISTERED  (PLC_Outlet);

PLC_Outlet::PLC_Outlet (Ptr<PLC_Node> node, Ptr<PLC_Impedance> impedance)
	: m_node (node)
{
	PLC_LOG_INFO ("Outlet created on Node" << node->GetVertexId ());
	node->SetOutlet (Ptr<PLC_Outlet> (this));
	if  (impedance)
		node->SetImpedance (impedance);
}

void
PLC_Outlet::DoDispose ()
{
	m_node = 0;
	m_rxInterface = 0;
	m_registered_backbone_branches.clear ();
}

void
PLC_Outlet::SetRxInterface (Ptr<PLC_RxInterface> interface)
{
	NS_LOG_FUNCTION (this);
	m_rxInterface = interface;
}

Ptr<PLC_RxInterface>
PLC_Outlet::GetRxInterface (void)
{
	NS_LOG_FUNCTION (this);
	return m_rxInterface;
}

TypeId
PLC_Outlet::GetTypeId (void)
{
	static TypeId tid = ns3::TypeId ("ns3::PLC_Outlet")
    		.SetParent<Object>  ()
    		;
	return tid;
}

void
PLC_Outlet::RegisterBackboneBranch (Ptr<PLC_BackboneBranch> bb_branch)
{
	this->m_registered_backbone_branches.insert (bb_branch);
}

bool
PLC_Outlet::IsTimeVariant (void)
{
	bool ret = false;

	if  (!this->m_node->IsOpenCircuit ())
	{
		this->m_node->GetImpedancePeekPtr ()->Lock ();
		if  (this->m_node->GetImpedancePeekPtr ()->IsTimeVariant ()) ret = true;
		this->m_node->GetImpedancePeekPtr ()->Unlock ();
	}

	return ret;
}

void
PLC_Outlet::SetImpedance (Ptr<PLC_Impedance> impedance, bool updateImmediately)
{
	PLC_LOG_FUNCTION (this << impedance);

	if (m_node->GetImpedancePtr() == impedance) return;

	if (impedance == NULL)
	{
		NS_LOG_DEBUG ("Switching to open circuit");
	}

	this->m_node->SetImpedance (impedance);

	PLC_LOG_INFO ("Outlet impedance of Node" << this->m_node->GetVertexId () << " has changed");

	this->AcquaintAffectedInstances ();

	if  (updateImmediately)
	{
		Ptr<PLC_Channel> ch = this->m_node->GetGraph ()->GetChannel ();
		NS_ASSERT (ch);

		// update active psds
		ch->UpdateReceivePSDs (ch->GetCurrentTimeslot (), true);
	}
}

Ptr<PLC_Impedance>
PLC_Outlet::GetImpedance (void)
{
	PLC_LOG_FUNCTION (this);
	return m_node->GetImpedancePtr ();
}

void
PLC_Outlet::AcquaintAffectedInstances (void)
{
	PLC_LOG_FUNCTION (this);

	NS_LOG_DEBUG ("Node name: " << m_node->GetName());
	NS_LOG_DEBUG ("Number of registered backbone branches: " << m_registered_backbone_branches.size());

	NS_ASSERT(m_node);
	Ptr<PLC_Graph> graph = m_node->GetGraph ();
	NS_ASSERT(graph);
	Ptr<PLC_Channel> ch = graph->GetChannel ();
	NS_ASSERT (ch);

	// if a receiving device is attached to the outlet, all tx interfaces have to be informed
	// of the impedance change
	if  (m_rxInterface)
	{
		uint32_t rxNodeId = m_node->GetVertexId ();

		// set paths to all transmitters out of date
		size_t i;
		for  (i = 0; i < ch->GetNTxInterfaces (); i++)
		{
			Ptr<PLC_TxInterface> txInterface = ch->GetTxInterface (i);
			uint32_t txNodeId = txInterface->GetNode ()->GetVertexId ();

			// same node, i.e. same device --> continue
			if  (txNodeId == rxNodeId) continue;

			txInterface->Lock ();
			if  (txInterface->GetChannelTransferImpl (PeekPointer (m_rxInterface)) == NULL)
			{
				txInterface->Unlock ();
				continue;
			}
			PLC_BackbonePath::iterator bp_begin = txInterface->BackbonePathBegin (PeekPointer (m_rxInterface));
			PLC_BackbonePath::iterator bp_end 	= txInterface->BackbonePathEnd (PeekPointer (m_rxInterface));
			txInterface->Unlock ();

			PLC_Node *prev_node = txInterface->GetNodePeekPointer ();
			PLC_Edge *edge;
			PLC_BackbonePath::iterator bp_it;
			for  (bp_it = bp_begin; bp_it != bp_end; bp_it++) {
				PLC_Node *bb_node =  (*bp_it)->GetNodePeekPtr ();

				edge = prev_node->GetEdge (bb_node);

				edge->Lock ();
				edge->SetInputImpedanceOutOfDate (bb_node);
				edge->SetEdgeTransferFactorOutOfDate (bb_node);
				edge->Unlock ();

				prev_node = bb_node;
			}

			PLC_Node *rxNode = m_rxInterface->GetNodePeekPointer ();
			edge = prev_node->GetEdge (rxNode);

			edge->Lock ();
			edge->SetInputImpedanceOutOfDate (rxNode);
			edge->SetEdgeTransferFactorOutOfDate (rxNode);
			edge->Unlock ();

			txInterface->Lock ();
			if  (this->IsTimeVariant ()) {
				txInterface->SetTimeVariantChannel (PeekPointer (m_rxInterface));
			}
			txInterface->SetChannelTransferImplsOutOfDate ();
			txInterface->Unlock ();

			// delete cached psds
			ch->DeleteOutOfDatePSDs (txInterface, m_rxInterface);
		}
	}
	else
	{
		// combine registered backbone branches with backbone branches that are associated to the rx node for joint processing
		std::set<Ptr<PLC_BackboneBranch> > m_bb_set = this->m_node->m_associated_backbone_branches;
		m_bb_set.insert (m_registered_backbone_branches.begin (), m_registered_backbone_branches.end ());

		std::set<Ptr<PLC_BackboneBranch> >::iterator bb_it;

		for  (bb_it = m_bb_set.begin (); bb_it != m_bb_set.end (); bb_it++)
		{
			std::pair<unsigned int, std::pair<unsigned int, unsigned int> > bb_key = (*bb_it)->GetKey();
			NS_LOG_DEBUG ("<" << bb_key.first << "," << bb_key.second.first << "," << bb_key.second.second << ">");

			// set all impedances on path to registered backbone branch out of date
			 (*bb_it)->Lock ();
			Ptr<PLC_Node> backbone_node =  (*bb_it)->GetNodePtr ();
			 (*bb_it)->Unlock ();

			if  (backbone_node != this->m_node) {
				std::list<Ptr<PLC_Node> > path2bb = this->m_node->GetGraph ()->GetShortestPath (Ptr<PLC_Node>  (this->m_node),  (*bb_it)->GetNodePtr ());

				PLC_Edge *cur_edge;
				PLC_Node *cur_node = PeekPointer (this->m_node);

				if  (path2bb.size () > 0) {
					std::list<Ptr<PLC_Node> >::iterator n_it;
					for  (n_it = path2bb.begin (); n_it != path2bb.end (); n_it++) {
						cur_node->Lock ();
						cur_edge = cur_node->GetEdge (PeekPointer (*n_it));
						cur_node->Unlock ();

						cur_edge->Lock ();
						NS_ASSERT (cur_edge->m_edge_transfer_data.find (cur_node) != cur_edge->m_edge_transfer_data.end ());
						PLC_InputImpedance& eq_imp = cur_edge->m_edge_transfer_data[cur_node].input_impedance;
						eq_imp.second.IsUp2Date = false;
						cur_edge->Unlock ();

						cur_node = PeekPointer (*n_it);
					}
				}

				 (*bb_it)->Lock ();
				cur_edge =  (*bb_it)->GetNodePeekPtr ()->GetEdge (cur_node);
				 (*bb_it)->Unlock ();

				cur_edge->Lock ();
				NS_ASSERT (cur_edge->m_edge_transfer_data.find (cur_node) != cur_edge->m_edge_transfer_data.end ());
				PLC_InputImpedance& eq_imp = cur_edge->m_edge_transfer_data[cur_node].input_impedance;
				eq_imp.second.IsUp2Date = false;
				cur_edge->Unlock ();
			}

			// set path impedances and channel transfer functions from txInterface to the affected backbone branch out of date
			 (*bb_it)->Lock ();
			 (*bb_it)->m_is_up_2_date = false;
			PLC_InterfaceTupel& interface_pairs =  (*bb_it)->m_registered_ifPairs;

			PLC_InterfaceTupel::iterator p_it;
			for  (p_it = interface_pairs.begin (); p_it != interface_pairs.end (); p_it++) {
				PLC_TxInterface *tx = p_it->first;
				PLC_RxInterface *rx = p_it->second;

				NS_LOG_DEBUG ("TX/RX-Tupel: <" << tx->GetNode()->GetName() << ", " << rx->GetNode()->GetName() << ">");

				tx->Lock ();
				PLC_BackbonePath::iterator bp_begin = tx->BackbonePathBegin (rx);
				PLC_BackbonePath::iterator bp_end 	= tx->BackbonePathEnd (rx);
				tx->Unlock ();
				NS_ASSERT (bp_begin != bp_end);

				PLC_Node *prev_node = tx->GetNodePeekPointer ();
				PLC_BackbonePath::iterator bp_it;

				for  (bp_it = bp_begin; bp_it != bp_end; bp_it++) {
					PLC_Node *bb_node =  (*bp_it)->GetNodePeekPtr ();
					PLC_Edge *edge = prev_node->GetEdge (bb_node);

					edge->Lock ();
					PLC_EdgeTransferUnit *etu = edge->GetEdgeTransferUnit (bb_node);
					NS_ASSERT (edge->m_edge_transfer_data.find (bb_node) != edge->m_edge_transfer_data.end ());
					PLC_InputImpedance& eq_imp = edge->m_edge_transfer_data[bb_node].input_impedance;
					eq_imp.second.IsUp2Date = false;
					edge->Unlock ();

					etu->Lock ();
					etu->SetOutOfDate ();
					etu->Unlock ();

					if  ( (*bp_it) ==  (*bb_it)) break;

					prev_node = bb_node;
				}
				NS_ASSERT ( (*bp_it) ==  (*bb_it));

				tx->Lock ();
				tx->SetChannelTransferImplsOutOfDate ();
				if  (this->IsTimeVariant ()) {
					NS_LOG_DEBUG ("Set ctv (" << tx->GetNode()->GetName() << " -> " << rx->GetNode()->GetName() << ") timevariant");
					tx->SetTimeVariantChannel (rx);
				}
				tx->Unlock ();

				// delete cached psds
				ch->DeleteOutOfDatePSDs (Ptr<PLC_TxInterface>  (tx), Ptr<PLC_RxInterface>  (rx));
			}
			 (*bb_it)->Unlock ();
		}

		ch->ScheduleNextTimeslotTasks ();
	}
}

}

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

#ifndef PLC_BACKBONE_H_
#define PLC_BACKBONE_H_

#include <map>

#include "ns3/plc-defs.h"
#include "ns3/plc-value.h"

namespace ns3 {

class PLC_Graph;
class PLC_TxInterface;
class PLC_RxInterface;

/**
 * \class PLC_BackboneBranch
 *
 * \brief Element of a backbone path.
 *
 * The shortest path between each transmitter-receiver pair is described by one
 * backbone path maintained by PLC_ChannelTransferImpl.
 * A backbone branch is uniquely defined by three adjacent nodes on this path and therefore
 * gives information about the graph edges contributing to the computation of channel transfer
 * function. Thereby several backbone branches of different transmitter-receiver paths can
 * be associated with the same plc node as well as one backbone branch can be part of multiple
 * backbone branches. Thus, memory allocation and recomputation effort is minimized.
 * Besides the equivalent shunt impedances of the bridge tap of one backbone node is cached.
 */
class PLC_BackboneBranch : public Object
{
	friend class PLC_Outlet;

public:
	static TypeId GetTypeId(void);

	/**
	 * Constructor
	 * @param node Backbone node
	 * @param before Adjacent node 1
	 * @param next Adjacent node 2
	 * @param sm Spectrum model
	 */
	PLC_BackboneBranch(Ptr<PLC_Node> node, Ptr<PLC_Node> before, Ptr<PLC_Node> next, Ptr<const SpectrumModel> sm);
	~PLC_BackboneBranch() {}

	/**
	 * @return Backbone node
	 */
	Ptr<PLC_Node> GetNodePtr(void) 		{ return this->m_node; }
	PLC_Node *GetNodePeekPtr(void) 		{ return PeekPointer(m_node); }

	/**
	 * @return First adjacent node pointer
	 */
	Ptr<PLC_Node> GetBeforeNodePtr(void) { return this->m_node_before; }
	PLC_Node *GetBeforeNodePeekPtr(void) { return PeekPointer(m_node_before); }

	/**
	 * @return Second adjacent node pointer
	 */
	Ptr<PLC_Node> GetNextNodePtr(void) 	{ return this->m_node_next; }

	/**
	 * Register transmitter-receiver which is using this backbone branch
	 * for its backbone path. That is needed to notify PLC_ChannelTransferImpl after
	 * a change of bridge tap impedance
	 * @param txInterface TX interface of the backbone path to be registered
	 * @param rxInterface RX interface of the backbone path to be registered
	 */
	void AddInterfacePair(PLC_TxInterface *txInterface, PLC_RxInterface *rxInterface);

	/**
	 * Triggers a depth first search on all bridge tap edges of this branch to find outlets
	 * and to register on them for notification
	 * @param graph_copy Copy of the boost graph (for parallel processing)
	 * @param graph_copy_mutex Shared mutex
	 */
	void DiscoverOutlets(boost::UGraph& graph_copy, PLC_Mutex *graph_copy_mutex);

	/**
	 * Calculates the access impedance of the bridge tap (recursively)
	 */
	void CalculateEquivalentBridgeTapImpedance(void);

	/**
	 * @return access impedance of the bridge tap
	 */
	Ptr<PLC_Impedance> GetEquivalentBridgeTapImpedance(void) const
	{
		NS_ASSERT(m_is_up_2_date);
		return m_equivalent_bridge_tap_impedance;
	}

	/**
	 * @return True if equivalent bridge tap impedance is still up to date
	 */
	bool IsUp2Date(void) const { return m_is_up_2_date; }

	/**
	 * @return True if equivalent bridge tap impedance is time variant
	 */
	bool IsTimeVariant(void) const { return m_is_time_variant; }

	/**
	 * Convert equivalent bridge tap impedance to time variant value
	 */
	void SetTimeVariant(void);

	/**
	 * @return Key of the backbone branch (id triple of m_node, m_node_before, m_node_next)
	 */
	std::pair<unsigned int, std::pair<unsigned int, unsigned int> > GetKey(void) { return m_key; }

	/**
	 * Mutex lock an unlock
	 */
	void Lock(void) { m_branch_mutex.Lock(); }
	void Unlock(void) { m_branch_mutex.Unlock(); }

private:
	virtual void DoStart(void);
	virtual void DoDispose(void);

	Ptr<const SpectrumModel> 	m_spectrum_model;
	mutable PLC_Mutex			m_branch_mutex;
	Ptr<PLC_Node> 				m_node, m_node_before, m_node_next;
	Ptr<PLC_Impedance> 			m_equivalent_bridge_tap_impedance;

	std::map<PLC_Node *, Ptr<PLC_Impedance> > m_parallel_output_impedances;
	std::pair<unsigned int, std::pair<unsigned int, unsigned int> > m_key;

	PLC_InterfaceTupel 	m_registered_ifPairs;
	bool 				m_is_up_2_date;
	bool				m_is_time_variant;
};

}

#endif /* PLC_BACKBONE_H_ */

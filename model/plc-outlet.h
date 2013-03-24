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

#ifndef PLC_OUTLET_H_
#define PLC_OUTLET_H_

#include <set>
#include "ns3/object.h"
#include "ns3/plc-defs.h"
#include "ns3/plc-edge.h"
#include "ns3/plc-node.h"
#include "ns3/plc-backbone.h"

namespace ns3 {

class PLC_Node;
class PLC_RxInterface;

/**
 * \class PLC_Outlet
 *
 * Class representing an outlet in the PLC network. An outlet has to be bound to a PLC_Node
 * and an impedance can be assigned to it. The main purpose of PLC_Outlet is to define network
 * nodes that may sporadically change their shunt impedance while the simulation is running.
 * If this happens all affected cached equivalent impedances, edge transfer units and
 * channel transfer functions are set out of date resulting in a recomputation of these values
 * when needed the next time.
 */
class PLC_Outlet : public Object
{

public:
	/**
	 * \brief Constructor
	 *
	 * \param node PLC_Node the outlet is connected to
	 * \param impedance PLC_Impedance to connect with the outlet
	 */
	PLC_Outlet(Ptr<PLC_Node> node, Ptr<PLC_Impedance> impedance = 0);
	~PLC_Outlet() {}

	static TypeId GetTypeId(void);

	/**
	 * Register a PLC_BackboneBranch which is affected by an impedance
	 * change of this outlet. This is done by the depth first search
	 * algorithm within PLC_ChannelTransferImpl::DiscoverOutlets
	 *
	 * @param bb_branch Affected PLC_BackboneBranch
	 */
	void RegisterBackboneBranch(Ptr<PLC_BackboneBranch> bb_branch);

	/**
	 * Change the shunt impedance of the outlet and set all affected
	 * values of the PLC network out of date.
	 *
	 * @param impedance New shunt impedance
	 * @param updateImmediately If true all channels and currently active receive PSDs will be recalculated
	 */
	void SetImpedance(Ptr<PLC_Impedance> impedance, bool updateImmediately = true);

	/**
	 * @return The shunt impedance currently connected to the outlet
	 */
	Ptr<PLC_Impedance> GetImpedance(void);

	/**
	 * @return True if the outlet's impedance is time variant
	 */
	bool IsTimeVariant(void);

	/**
	 * @return The associated PLC_Node
	 */
	Ptr<PLC_Node> GetNode(void) { return m_node; }

	/**
	 * Notify the outlet that it has an RX interface on top.
	 * This is necessary to set out of date all backbone paths
	 * leading to this node.
	 */
	void SetRxInterface(Ptr<PLC_RxInterface> interface);

	/**
	 * @return PLC_RxInterface bound to this node or NULL
	 */
	Ptr<PLC_RxInterface> GetRxInterface(void);

	/**
	 * Mutex lock and unlock
	 */
	void Lock(void) const { m_mutex.Lock(); }
	void Unlock(void) const { m_mutex.Unlock(); }

private:
	virtual void DoDispose(void);

	mutable PLC_Mutex m_mutex;
	void AcquaintAffectedInstances(void);

	Ptr<PLC_Node> m_node;
	Ptr<PLC_RxInterface> m_rxInterface;
	std::set<Ptr<PLC_BackboneBranch> > m_registered_backbone_branches;
};

}

#endif /* PLC_OUTLET_H_ */

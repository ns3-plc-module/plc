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

#ifndef PLC_GRAPH_H_
#define PLC_GRAPH_H_

#include <map>

#include <ns3/type-id.h>

#include "plc-defs.h"
#include "plc-node.h"
#include "plc-channel.h"

namespace ns3 {

class PLC_Outlet;
class PLC_BranchDiscoverVisitor;
class PLC_TxInterface;
class PLC_RxInterface;
class PLC_Channel;

/**
 *	\brief Graph of the PLC network
 *
 *	This class describes the PLC network topology as an undirected graph. Annotation: As the simulation has only
 *	graph and one channel instance the correspondent classes could be combined, but to have a logical seperation
 *	they are realized in different classes.
 *	It is currently not allowed to have cycles in the topology as the Dijkstra Algorithm for the shortest path calculation will fail!
 *	Although there should be no cycles in a real world power line network for the power transmission
 *	frequency, it is possible to (galvanically) recouple an HF signal over a redundant path to the network.
 *	TODO: segment graph to support cycles
 */
class PLC_Graph : public Object
{
	friend class PLC_TxInterface;

public:
	static TypeId GetTypeId(void);

	PLC_Graph();
	~PLC_Graph(void) {}

	/**
	 * Add a Node to the graph.
	 * All network nodes have to be added before calling CreateGraph
	 * @param node Node to be added
	 */
	void AddNode(Ptr<PLC_Node> node);

	/**
	 * Sets the channel instance to be used.
	 * @param channel
	 */
	void SetChannel(Ptr<PLC_Channel> channel) { this->m_channel = channel; }

	/**
	 *
	 * @return Used channel instance
	 */
	Ptr<PLC_Channel> GetChannel(void)
	{
		NS_ASSERT_MSG(m_channel, "Channel for the graph has not been created yet");
		return this->m_channel;
	}

	Ptr<PLC_Channel> GetChannel(void) const
	{
		NS_ASSERT_MSG(m_channel, "Channel for the graph has not been created yet");
		return this->m_channel;
	}

	/**
	 *
	 * @return All connected RX interfaces of the used channel instance
	 */
	std::vector<Ptr<PLC_RxInterface> > GetConnectedRxInterfaces();
	std::vector<PLC_RxInterface *> GetConnectedRxInterfacePeekPtrs(void);

	/**
	 * Creates the PLC graph, i.e. the method performs a Dijkstra search to calculate the shortest
	 * paths between all network nodes (needed for the "line of sight" path of signal transmission
	 * over the PLC fading channel). It uses the boost graph library
	 */
	void CreatePLCGraph(void);

	/**
	 * Get the node pointer associated with id
	 * @param id
	 * @return
	 */
	Ptr<PLC_Node> GetNodePtr(unsigned int id);
	PLC_Node *GetNodePeekPtr(unsigned int id);

	std::vector<Ptr<PLC_Node> > GetNodes(void) { return m_nodes; }

	/**
	 * Get the underlying boost graph.
	 * Used by the parallelized dijkstra and depth first search algorithms
	 * @return Boost graph pointer
	 */
	boost::UGraph *GetGraphPtr(void) { return &this->m_graph; }

	/**
	 * Returns the shortest path between two nodes in form of a list of intermediate nodes
	 * An empty list indicates a direct connection between from and to.
	 * Note that an existing path between the nodes is mandatory!
	 * @param from First node
	 * @param to Second node
	 * @return
	 */
	std::list<Ptr<PLC_Node> > GetShortestPath(Ptr<PLC_Node> from, Ptr<PLC_Node> to);

	/**
	 * Returns the distance between \from and \to calculated by the Dijkstra algorithm
	 * with the sum of directed distances of the paths nodes as the cost function
	 * @param from First node
	 * @param to Second node
	 * @return Distance
	 */
	double GetDistance(Ptr<PLC_Node> from, Ptr<PLC_Node> to);

	/**
	 * Proof if a backbone branch already exists (see plc-backbone.h for further information)
	 * @param key
	 * @return True if there is already a backbone branch with \key registered, false otherwise
	 */
	bool BackboneBranchExists(PLC_BackboneBranchKey key);

	/**
	 * Register a backbone branch instance with \key
	 * @param bb_key Key
	 * @param bb_branch Backbone branch
	 */
	void RegisterBackboneBranch(PLC_BackboneBranchKey bb_key, Ptr<PLC_BackboneBranch> bb_branch);

	/**
	 * Get the backbone branch associated with \key or NULL if it does not exist
	 * @param bb_key Key
	 * @return Backbone branch
	 */
	Ptr<PLC_BackboneBranch> GetBackboneBranch(PLC_BackboneBranchKey bb_key);

	/**
	 * Proof if there is an existing path between \from and \to
	 * @param from First node
	 * @param to Second nod
	 * @return True if path exists, false otherwise
	 */
	bool PathExists(Ptr<PLC_Node> from, Ptr<PLC_Node> to);

	/**
	 * Lock graph mutex for mutual exclusion
	 */
	void Lock() { m_graph_mutex.Lock(); }

	/**
	 * Unlock graph mutex
	 */
	void Unlock() { m_graph_mutex.Unlock(); }

protected:
	virtual void DoStart(void);
	virtual void DoDispose(void);

	void CalculateShortestPaths(void);

	boost::UGraph 		m_graph;
	mutable PLC_Mutex 	m_graph_mutex;

	Ptr<PLC_Channel>	m_channel;

	std::vector<Ptr<PLC_Node> > m_nodes;

	// key<from, to> => distance + node list
	std::map<std::pair<unsigned int, unsigned int>, std::pair<double, std::list<Ptr<PLC_Node> > > > m_shortest_paths;
	std::map<PLC_BackboneBranchKey, Ptr<PLC_BackboneBranch> > m_backbone_branches;
};

}

#endif /* PLC_GRAPH_H_ */

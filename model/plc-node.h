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

#ifndef PLC_NODE_H_
#define PLC_NODE_H_

#include <map>
#include <set>
#include <list>
#include <string>

#include <ns3/object.h>
#include <ns3/type-id.h>
#include <ns3/vector.h>

#include "plc-defs.h"
#include "plc-time.h"
#include "plc-value.h"
#include "plc-edge.h"
#include "plc-outlet.h"
#include "plc-backbone.h"

namespace ns3 {

class PLC_Graph;
class PLC_Line;
class PLC_Outlet;
class PLC_Channel;

/**
 * \brief Node of the PLC graph
 *
 * In order to calculate the transmission channels of the PLC network an undirected
 * graph will be constructed. This class defines the graph nodes which are used as an abstract
 * representation of network components, e.g. impedances, outlets, branches, etc.
 */

class PLC_Node : public Object
{
	friend class PLC_Graph;
	friend class PLC_Outlet;

public:
	static TypeId GetTypeId (void);

	PLC_Node ();
	~PLC_Node ();

	/**
	 *
	 * @return the node's assigned position
	 */
	Vector3D GetPosition (void) { return m_position; }

	/**
	 *
	 * @param pos position to be assigned to the node
	 */
	void SetPosition (Vector3D pos) { m_position = pos; }

	/**
	 *
	 * @param pos_x x coordinate
	 * @param pos_y y coordinate
	 * @param pos_z z coordinate
	 */
	void SetPosition(double pos_x, double pos_y, double pos_z);

	/**
	 * Connect an impedance in parallel to all two wire transission lines
	 * linked to this node
	 *
	 * @param impedance
	 */
	void SetImpedance(Ptr<PLC_Impedance> impedance);

	/**
	 *
	 * @return node impedance smart pointer
	 */
	Ptr<PLC_Impedance> GetImpedancePtr (void) { return m_impedance; }

	/**
	 *
	 * @return node impedance raw poiner
	 */
	PLC_Impedance *GetImpedancePeekPtr (void) const { return PeekPointer(m_impedance); }

	/**
	 *
	 * @return id assigned to this node by the network graph
	 */
	unsigned int GetVertexId (void) { return m_vertex_id; }

	/**
	 *
	 * @return pointer to the outlet or NULL if it doesn't have one
	 */
	Ptr<PLC_Outlet> GetOutlet (void) { return this->m_outlet; }

	/**
	 *
	 * @return raw pointer to the outlet or NULL if it doesn't have one
	 */
	PLC_Outlet *GetOutletPeekPtr (void);

	/**
	 *
	 * @return true if node has an outlet
	 */
	bool HasOutlet (void) { return m_outlet == NULL ? false : true; }

	/**
	 *
	 * @return true if node has no impedance assigned
	 */
	bool IsOpenCircuit (void)	{ return m_open_circuit; }

	/**
	 * disconnects a contigent impedance
	 */
	void OpenCircuit (void) 	{ m_open_circuit = true; }

	/**
	 * reconnects the impedance to the circuit if existing
	 */
	void CloseCircuit (void);


	/**
	 * Links an edge to the node. An edge represents a two port
	 * network (e.g. a cable or transformer instance so far)
	 *
	 * @param to destination node
	 * @param edge instance
	 */
	void AddEdge (Ptr<PLC_Node> to, Ptr<PLC_Edge> edge);

	/**
	 *
	 * @return the number of edges assigned to this node
	 */
	size_t GetNumEdges (void) { return m_edges.size(); }

	/**
	 *
	 * @param node
	 * @return the linked edge leading to node
	 */
	PLC_Edge *GetEdge (PLC_Node *node);

	/**
	 * @return a std::map of all linked edges of the node
	 */
	PLC_NodeOutEdgesMap GetEdges (void);

	/**
	 * associates an instance of a backbone branch to this node.
	 * A reference to the backbone branches is needed by PLC_Outlet
	 * to set them out of date in case of an impedance change
	 *
	 * @param pointer to the backbone branch
	 */
	void AssociateBackboneBranch (Ptr<PLC_BackboneBranch> backboneBranch);

	/**
	 *
	 * @return the start iterator of the edge map
	 */
	PLC_NodeOutEdgesMap::iterator OutEdgesBegin (void) { return m_edges.begin(); }

	/**
	 *
	 * @return the end iterator of the edge map
	 */
	PLC_NodeOutEdgesMap::iterator OutEdgesEnd (void) { return m_edges.end(); }

	/**
	 * Assign a name to the node
	 * @param name
	 */
	void SetName(std::string name) { m_name = name; }

	/**
	 * Get the assigned name of the node
	 * @return
	 */
	std::string GetName(void) { return m_name; }

	/**
	 * Locks the mutex of this node
	 */
	void Lock(void) { m_node_mutex.Lock(); }

	/**
	 * Unlocks the mutex of this node
	 */
	void Unlock(void) { m_node_mutex.Unlock(); }

	/**
	 *
	 * @return whether the connected impedance is time variant
	 */
	bool IsTimeVariant(void);

	/**
	 *
	 * @return pointer to the graph
	 */
	Ptr<PLC_Graph> GetGraph(void) { return this->m_graph; }

	/**
	 * @return the global channel instance
	 */
	Ptr<PLC_Channel> GetChannel(void);

	/**
	 *
	 * @param graph set the graph
	 */
	void SetGraph(Ptr<PLC_Graph> graph);

	/**
	 * allocates outlet to the node
	 *
	 * @param outlet
	 */
	void SetOutlet(Ptr<PLC_Outlet> outlet);

	static uint64_t GetImpedanceHashSum(void) { return m_impedance_hash_sum; }

protected:
	virtual void DoStart(void);
	virtual void DoDispose(void);

	static uint64_t m_impedance_hash_sum;

	Vector3D m_position;
	mutable PLC_Mutex	m_node_mutex;
	unsigned int m_vertex_id;
	bool m_open_circuit;

	Ptr<PLC_Graph> 		m_graph;
	Ptr<PLC_Impedance> 	m_impedance;
	Ptr<PLC_Outlet> 	m_outlet;

	PLC_NodeOutEdgesMap m_edges;
	std::set<Ptr<PLC_BackboneBranch> > m_associated_backbone_branches;

	std::string m_name;
};

}

#endif /* PLC_NODE_H_ */

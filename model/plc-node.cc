/*
 * plc-node.cc
 *
 *  Created on: 2011-12-20
 *      Author: Alexander Schloegl <alexander.schloegl@gmx.de>
 */

#include "ns3/plc-node.h"
#include "ns3/plc-edge.h"
#include "ns3/plc-channel.h"
#include "ns3/log.h"
#include "ns3/boolean.h"
#include "ns3/uinteger.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("PLC_Node");
NS_OBJECT_ENSURE_REGISTERED (PLC_Node);

uint64_t PLC_Node::m_impedance_hash_sum = 0;

PLC_Node::PLC_Node ()
{
	this->m_open_circuit = true;
	this->m_impedance = 0;
}

PLC_Node::~PLC_Node()
{
}

void
PLC_Node::DoStart ()
{
	NS_ASSERT(m_graph);

}

void PLC_Node::DoDispose (void)
{
	m_open_circuit = true;
	m_graph = 0;
	m_impedance = 0;
	m_outlet = 0;
	m_edges.clear();
	m_associated_backbone_branches.clear();
}

TypeId
PLC_Node::GetTypeId (void)
{
	static TypeId tid = ns3::TypeId("ns3::PLC_Node")
    		.SetParent<Object> ()
    		.AddAttribute("Node Id", "identifier of the node", TypeId::ATTR_GET | TypeId::ATTR_CONSTRUCT, UintegerValue(0), MakeUintegerAccessor(&PLC_Node::m_vertex_id), MakeUintegerChecker<unsigned int>())
    		.AddAttribute("Position", "position of the node", Vector3DValue(Vector3D(0, 0, 0)), MakeVectorAccessor(&PLC_Node::m_position), MakeVectorChecker())
    		.AddAttribute("Open Circuit", "indicates infinity impedance", BooleanValue(true), MakeBooleanAccessor(&PLC_Node::m_open_circuit), MakeBooleanChecker())
    		;
	return tid;
}

void
PLC_Node::SetPosition (double pos_x, double pos_y, double pos_z)
{
	this->m_position.x = pos_x;
	this->m_position.y = pos_y;
	this->m_position.z = pos_z;
}

void
PLC_Node::SetGraph(Ptr<PLC_Graph> graph)
{
	NS_LOG_FUNCTION(this << graph);
	NS_LOG_DEBUG(m_name << " " << graph);
	this->m_graph = graph;
}

void
PLC_Node::SetOutlet (Ptr<PLC_Outlet> outlet)
{
	NS_LOG_FUNCTION(this << outlet);
	this->m_outlet = outlet;
}

PLC_Outlet *
PLC_Node::GetOutletPeekPtr (void)
{
	NS_LOG_FUNCTION(this);
	return PeekPointer(this->m_outlet);
}

void PLC_Node::AssociateBackboneBranch (Ptr<PLC_BackboneBranch> backboneBranch)
{
	NS_LOG_FUNCTION(this);
	m_associated_backbone_branches.insert(backboneBranch);
}

void
PLC_Node::AddEdge (Ptr<PLC_Node> to, Ptr<PLC_Edge> edge)
{
	NS_LOG_FUNCTION(this << to << edge);
	this->m_edges[PeekPointer(to)] = edge;
}

PLC_Edge *
PLC_Node::GetEdge (PLC_Node *node)
{
	NS_ASSERT(this->m_edges.find(node) != this->m_edges.end());
	return PeekPointer(this->m_edges[node]);
}

PLC_NodeOutEdgesMap
PLC_Node::GetEdges(void)
{
	NS_LOG_FUNCTION(this);
	return this->m_edges;
}

void
PLC_Node::SetImpedance(Ptr<PLC_Impedance> impedance)
{
	NS_LOG_FUNCTION(impedance);
	NS_LOG_LOGIC("Node Id: " << m_vertex_id);

	NS_LOG_DEBUG ("Old impedance hash sum: " << m_impedance_hash_sum);
	NS_LOG_DEBUG ("Old impedance peek pointer: " << PeekPointer(m_impedance));
	NS_LOG_DEBUG ("New impedance peek pointer: " << PeekPointer(impedance));
	NS_LOG_DEBUG ("this: " << this);

#ifdef PLC_USE_IMPEDANCE_HASHING
	m_impedance_hash_sum ^= ((uint64_t) PeekPointer(m_impedance) ^ (uint64_t) (this));
	m_impedance_hash_sum ^= ((uint64_t) PeekPointer(impedance) ^ (uint64_t) (this));
#endif

	NS_LOG_DEBUG ("New impedance hash sum: " << m_impedance_hash_sum);

	m_impedance = impedance;
	if (impedance)
	{
		m_open_circuit = false;
	}
	else
	{
		m_open_circuit = true;
	}
}

void PLC_Node::CloseCircuit(void)
{
	NS_LOG_FUNCTION(this);
	if (m_impedance)
	{
		m_open_circuit = false;
	}
}

bool PLC_Node::IsTimeVariant(void)
{
	NS_LOG_FUNCTION(this);
	if (!m_open_circuit && m_impedance)
	{
		if (this->m_impedance->IsTimeVariant()) return true;
	}
	return false;
}

Ptr<PLC_Channel>
PLC_Node::GetChannel(void)
{
	NS_LOG_FUNCTION(this);
	NS_ASSERT_MSG(m_graph, "Node has not been attached to a PLC_Graph");
	return m_graph->GetChannel();
}

} // namespace ns3

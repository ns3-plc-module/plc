/*
 * plc-graph.cc
 *
 *  Created on: 2011-12-22
 *      Author: Alexander Schloegl <alexander.schloegl@gmx.de>
 */

#include <boost/graph/copy.hpp>

#include <ns3/log.h>
#include <ns3/config.h>
#include <ns3/plc-undirected-dfs.h>
#include <ns3/object-vector.h>

#include "plc-graph.h"
#include "plc-defs.h"
#include "plc-time.h"
#include "plc-interface.h"
#include "plc-node.h"
#include "plc-edge.h"
#include "plc-channel.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("PLC_Graph");
NS_OBJECT_ENSURE_REGISTERED (PLC_Graph);

PLC_Graph::PLC_Graph (void)
{
	Config::RegisterRootNamespaceObject(this);
}

TypeId
PLC_Graph::GetTypeId (void)
{
	static TypeId tid = ns3::TypeId("ns3::PLC_Graph")
    		.SetParent<Object> ()
    		.AddAttribute("Nodes", "list of registered PLC_Nodes", TypeId::ATTR_GET | TypeId::ATTR_CONSTRUCT, ObjectVectorValue(), MakeObjectVectorAccessor(&PLC_Graph::m_nodes), MakeObjectVectorChecker<PLC_Node>())
    		;
	return tid;
}

void
PLC_Graph::AddNode (Ptr<PLC_Node> node)
{
	NS_LOG_FUNCTION(this << node);
	unsigned int vertex_id = this->m_nodes.size();
	NS_ASSERT(vertex_id < UINT_MAX);
	node->m_vertex_id = vertex_id;
	this->m_nodes.push_back(node);
	node->SetGraph(this);

	PLC_LOG_INFO("Node (id: " << vertex_id << ") added to PLC grid");
}

void
PLC_Graph::DoStart (void)
{
}

void
PLC_Graph::DoDispose (void)
{
	NS_LOG_FUNCTION(this);
	std::map<PLC_BackboneBranchKey, Ptr<PLC_BackboneBranch> >::iterator bit;
	for (bit = m_backbone_branches.begin(); bit != m_backbone_branches.end(); bit++)
	{
		bit->second->Dispose();
	}
	m_backbone_branches.clear();
	m_shortest_paths.clear();
	m_nodes.clear();
}

Ptr<PLC_Node>
PLC_Graph::GetNodePtr (unsigned int id)
{
	NS_LOG_FUNCTION(this);
	boost::property_map<boost::UGraph, boost::vertex_nodeptr_t>::type nodeptr = boost::get(boost::vertex_nodeptr, this->m_graph);
	return Ptr<PLC_Node> (boost::get(nodeptr, id));
}

PLC_Node *PLC_Graph::GetNodePeekPtr(unsigned int id)
{
	NS_LOG_FUNCTION(this);
	boost::property_map<boost::UGraph, boost::vertex_nodeptr_t>::type nodeptr = boost::get(boost::vertex_nodeptr, this->m_graph);
	return boost::get(nodeptr, id);
}

std::vector<Ptr<PLC_RxInterface> >
PLC_Graph::GetConnectedRxInterfaces (void)
{
	NS_LOG_FUNCTION(this);
	std::vector<Ptr<PLC_RxInterface> > ret;

	uint32_t i;
	for (i = 0; i < this->m_channel->GetNRxInterfaces(); i++)
			ret.push_back(this->m_channel->GetRxInterface(i));

	return ret;
}

std::vector<PLC_RxInterface *>
PLC_Graph::GetConnectedRxInterfacePeekPtrs (void)
{
	NS_LOG_FUNCTION(this);
	std::vector<PLC_RxInterface *> ret;

	uint32_t i;
	for (i = 0; i < this->m_channel->GetNRxInterfaces(); i++)
			ret.push_back(PeekPointer(this->m_channel->GetRxInterface(i)));

	return ret;
}

void PLC_Graph::CreatePLCGraph (void)
{
	NS_LOG_FUNCTION(this);
	PLC_LOG_INFO("Creating PLC graph...");

	std::vector<Ptr<PLC_Node> >::iterator it;

	this->m_graph = boost::UGraph(m_nodes.size());

	boost::property_map<boost::UGraph, boost::edge_weight_t>::type weightmap 	= boost::get(boost::edge_weight, this->m_graph);
	boost::property_map<boost::UGraph, boost::vertex_nodeptr_t>::type nodeptr 	= boost::get(boost::vertex_nodeptr, this->m_graph);
	boost::property_map<boost::UGraph, boost::edge_plc_edgeptr_t>::type plc_edgeptr = boost::get(boost::edge_plc_edgeptr, this->m_graph);


	for (it=m_nodes.begin(); it!=m_nodes.end(); it++) {
		PLC_NodeOutEdgesMap::iterator outEdges_it;

		boost::put(nodeptr, boost::vertex_descriptor((*it)->GetVertexId()), PeekPointer(*it));

		for (outEdges_it = (*it)->OutEdgesBegin(); outEdges_it != (*it)->OutEdgesEnd(); outEdges_it++) {
			boost::edge_descriptor e;
			bool inserted;
			unsigned int from, to;

			PLC_Edge *edge = PeekPointer((*outEdges_it).second);

			if (!edge->added2graph) {

				edge->Lock();
				PLC_EdgeTransferDataMap::iterator con_nodes_it = edge->m_edge_transfer_data.begin();

				con_nodes_it->first->Lock();
				from 	= con_nodes_it->first->GetVertexId();
				con_nodes_it->first->Unlock();

				(++con_nodes_it)->first->Lock();
				to		= con_nodes_it->first->GetVertexId();
				con_nodes_it->first->Unlock();

				edge->Unlock();

				boost::tie(e, inserted) = boost::add_edge(boost::vertex_descriptor(from), boost::vertex_descriptor(to), this->m_graph);
				weightmap[e] = edge->GetLength();
 				boost::put(plc_edgeptr, e, edge);

				edge->added2graph = true;
			}
		}
	}

	this->CalculateShortestPaths();

	PLC_LOG_INFO("PLC_Graph created");
}

void PLC_Graph::CalculateShortestPaths(void)
{
	NS_LOG_FUNCTION(this);
	PLC_LOG_INFO("Calculating shortest paths...");

	std::vector<Ptr<PLC_Node> >::iterator it;

	int i;
	unsigned int size;
	NS_ASSERT((size = this->m_nodes.size()) < INT_MAX);

	for (i = 0; i < (int) size; i++) {
		boost::UGraph *graph_copy = new boost::UGraph();
		this->m_graph_mutex.Lock();
		boost::copy_graph<boost::UGraph, boost::UGraph> (this->m_graph, *graph_copy);
		this->m_graph_mutex.Unlock();

		unsigned int root = this->m_nodes[i]->GetVertexId();

		std::vector<boost::vertex_descriptor> p(boost::num_vertices(*graph_copy));
		std::vector<double> d(boost::num_vertices(*graph_copy));
		boost::vertex_descriptor s = boost::vertex(root, *graph_copy);

#if defined(BOOST_MSVC) && BOOST_MSVC <= 1300
		// VC++ has trouble with the named parameters mechanism
		boost::property_map<boost::UGraph, boost::vertex_index_t>::type indexmap = boost::get(boost::vertex_index, *graph_copy);
		boost::property_map<boost::UGraph, boost::edge_weight_t>::type weightmap = boost::get(boost::edge_weight, *graph_copy);

		dijkstra_shortest_paths(this->m_graph, s, &p[0], &d[0], weightmap, indexmap,
								std::less<int>(), closed_plus<int>(),
								(std::numeric_limits<int>::max)(), 0,
								default_dijkstra_visitor());
#else
		dijkstra_shortest_paths(*graph_copy, s, boost::predecessor_map(&p[0]).distance_map(boost::make_iterator_property_map(d.begin(), get(boost::vertex_index, *graph_copy))));
#endif

		boost::graph_traits <boost::UGraph>::vertex_iterator vi, vend;
		for (boost::tie(vi, vend) = boost::vertices(*graph_copy); vi != vend; ++vi) {
			std::pair<int, int> key;
			bool reverse = false;

			if (root < *vi) {
				key.first = root;
				key.second = *vi;
			}
			else if (root > *vi) {
				key.first = *vi;
				key.second = root;

				reverse = true;
			}
			else continue;

			if (this->m_shortest_paths.find(key) == this->m_shortest_paths.end()) {
				unsigned int parent_id	= p[*vi];

				Ptr<PLC_Node> root_node = this->GetNodePtr(root);
				Ptr<PLC_Node> cur_node 	= this->GetNodePtr(parent_id);

				if (parent_id == *vi) {
					// indicates missing connection between nodes
					this->m_shortest_paths[key].first = -1;
					this->m_shortest_paths[key].second.push_front(root_node);
					continue;
				}
				else {
					// save distance
					this->m_shortest_paths[key].first = d[*vi];
				}

				while (cur_node != root_node) {

					if (reverse)
						this->m_shortest_paths[key].second.push_back(cur_node);
					else
						this->m_shortest_paths[key].second.push_front(cur_node);

					parent_id = p[parent_id];
					cur_node = this->GetNodePtr(parent_id);
				}
			}
		}
		delete graph_copy;
	}
}

std::list<Ptr<PLC_Node> >
PLC_Graph::GetShortestPath (Ptr<PLC_Node> from, Ptr<PLC_Node> to)
{
	unsigned int from_id, to_id;

	from_id 	= from->GetVertexId();
	to_id 		= to->GetVertexId();

	std::list<Ptr<PLC_Node> > ret;

	if (from_id < to_id)
		ret = this->m_shortest_paths[std::pair<unsigned int, unsigned int>(from_id, to_id)].second;
	else if (to_id < from_id) {
		ret = this->m_shortest_paths[std::pair<unsigned int, unsigned int>(to_id, from_id)].second;
		ret.reverse();
	}

	return ret;
}

double
PLC_Graph::GetDistance (Ptr<PLC_Node> from, Ptr<PLC_Node> to)
{
	NS_LOG_FUNCTION(this);
	unsigned int from_id, to_id;

	from_id 	= from->GetVertexId();
	to_id 		= to->GetVertexId();

	double ret;
	std::pair<unsigned int, unsigned int> key;

	if (from_id < to_id)
	{
		key = std::pair<unsigned int, unsigned int> (from_id, to_id);
	}
	else if (to_id < from_id)
	{
		key = std::pair<unsigned int, unsigned int> (to_id, from_id);
	}
	else
	{
		return -1;
	}

	if (m_shortest_paths.find(key) == m_shortest_paths.end())
	{
		ret = -1;
	}
	else
	{
		ret = this->m_shortest_paths[key].first;
	}

	return ret;
}

void
PLC_Graph::RegisterBackboneBranch (PLC_BackboneBranchKey bb_key, Ptr<PLC_BackboneBranch> bb_branch)
{
	NS_LOG_FUNCTION(this);
	m_backbone_branches[bb_key] = bb_branch;
}

Ptr<PLC_BackboneBranch>
PLC_Graph::GetBackboneBranch (PLC_BackboneBranchKey bb_key)
{
	NS_LOG_FUNCTION(this);

	if (m_backbone_branches.find(bb_key) != m_backbone_branches.end())
		return m_backbone_branches[bb_key];
	else
		return NULL;
}


bool
PLC_Graph::BackboneBranchExists (PLC_BackboneBranchKey key)
{
	NS_LOG_FUNCTION(this);
	if (this->m_backbone_branches.find(key) != this->m_backbone_branches.end()) return true;

	return false;
}

bool
PLC_Graph::PathExists (Ptr<PLC_Node> from, Ptr<PLC_Node> to)
{
	NS_LOG_FUNCTION(this);
	unsigned int from_id, to_id;
	bool ret = true;

	from->Lock();
	from_id 	= from->GetVertexId();
	from->Unlock();
	to->Lock();
	to_id 		= to->GetVertexId();
	to->Unlock();

	if (from_id < to_id) {
		if (*this->m_shortest_paths[std::pair<unsigned int, unsigned int> (from_id, to_id)].second.begin() == from) ret = false;
	}
	else if (to_id < from_id) {
		if (*this->m_shortest_paths[std::pair<unsigned int, unsigned int> (to_id, from_id)].second.begin() == to) ret = false;
	}

	return ret;
}

}

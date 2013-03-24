//
//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
//
#ifndef PLC_BOOST_GRAPH_UNDIRECTED_DFS_HPP
#define PLC_BOOST_GRAPH_UNDIRECTED_DFS_HPP

#include <boost/graph/depth_first_search.hpp>
#include <vector>

#include "ns3/plc-graph.h"

namespace boost {

  namespace detail {

// Define BOOST_RECURSIVE_DFS to use older, recursive version.
// It is retained for a while in order to perform performance
// comparison.
    template <typename IncidenceGraph, typename DFSVisitor, 
              typename VertexColorMap, typename EdgeColorMap>
    void plc_undir_dfv_impl
      (
       const IncidenceGraph& g,
       typename graph_traits<IncidenceGraph>::vertex_descriptor u, 
       DFSVisitor& vis,
       VertexColorMap vertex_color,
       EdgeColorMap edge_color,
       ns3::PLC_Mutex *graph_copy_mutex
      )
    {
      function_requires<IncidenceGraphConcept<IncidenceGraph> >();
      function_requires<DFSVisitorConcept<DFSVisitor, IncidenceGraph> >();
      typedef typename graph_traits<IncidenceGraph>::vertex_descriptor Vertex;
      typedef typename graph_traits<IncidenceGraph>::edge_descriptor Edge;
      function_requires<ReadWritePropertyMapConcept<VertexColorMap,Vertex> >();
      function_requires<ReadWritePropertyMapConcept<EdgeColorMap,Edge> >();
      typedef typename property_traits<VertexColorMap>::value_type ColorValue;
      typedef typename property_traits<EdgeColorMap>::value_type EColorValue;
      function_requires< ColorValueConcept<ColorValue> >();
      function_requires< ColorValueConcept<EColorValue> >();
      typedef color_traits<ColorValue> Color;
      typedef color_traits<EColorValue> EColor;
      typedef typename graph_traits<IncidenceGraph>::out_edge_iterator Iter;
      typedef std::pair<Vertex, std::pair<Iter, Iter> > VertexInfo;

      std::vector<VertexInfo> stack;

      graph_copy_mutex->Lock();
      put(vertex_color, u, Color::gray());
      graph_copy_mutex->Unlock();

      vis.discover_vertex(u, g);
      stack.push_back(std::make_pair(u, out_edges(u, g)));
      while (!stack.empty()) {
        VertexInfo& back = stack.back();
        u = back.first;
        Iter ei, ei_end;
        boost::tie(ei, ei_end) = back.second;
        stack.pop_back();
        while (ei != ei_end) {
          Vertex v = target(*ei, g);
          vis.examine_edge(*ei, g);

          graph_copy_mutex->Lock();
          ColorValue v_color = get(vertex_color, v);
          EColorValue uv_color = get(edge_color, *ei);
          put(edge_color, *ei, EColor::black());
          graph_copy_mutex->Unlock();

          if (v_color == Color::white()) {
            vis.tree_edge(*ei, g);
            stack.push_back(std::make_pair(u, std::make_pair(++ei, ei_end)));
            u = v;

            graph_copy_mutex->Lock();
            put(vertex_color, u, Color::gray());
            graph_copy_mutex->Unlock();

            vis.discover_vertex(u, g);
            boost::tie(ei, ei_end) = out_edges(u, g);
          } else if (v_color == Color::gray()) {
            if (uv_color == EColor::white()) vis.back_edge(*ei, g);
            ++ei;
          } else { // if (v_color == Color::black())
            ++ei;
          }
        }

        graph_copy_mutex->Lock();
        put(vertex_color, u, Color::black());
        graph_copy_mutex->Unlock();

        vis.finish_vertex(u, g);
      }
    }

  } // namespace detail

} // namespace boost

#endif

//
//  Graph_algorithms.h
//  Task1
//
//  Created by Taygrim on 15.03.13.
//  Copyright (c) 2013 Taygrim. All rights reserved.
//

#ifndef Task1_Graph_algorithms_h
#define Task1_Graph_algorithms_h

#include "Graph.h"
#include "Topsort.h"
#include "Bridges_and_cutpoints.h"
#include "Strongly_connected_components.h"
#include "Eulerian_сycle.h"
#include "LCA.h"

namespace graph_algorithms
{
    using topsort_ns::topsort;      //vector <long> topsort(const graph::Graph &gr);
                                    //returns vector = {-1} if graph has a cycle
    
    using bridges_and_cutpoints::find_bridges; // vector <Edge> find_bridges(const Graph &gr);
    using bridges_and_cutpoints::find_cutpoints; // vector <long> find_cutpoints(const Graph &gr);
    using bridges_and_cutpoints::biconnected_edged_components; // vector <Graph> biconnected_edged_components(const Graph &gr);
    using bridges_and_cutpoints::biconnected_vertex_components; // vector <Graph> biconnected_vertex_components(const Graph &gr);

    using strongly_connected_components::Tarjan; // vector<Graph> Tarjan(const Graph &gr);
    using strongly_connected_components::Kosaraju; // vector<Graph> Kosaraju(const Graph &gr);
    
    using eulerian_cycle_ns::eulerian_cycle; // vector<long> Eulerian_cycle(const Graph &gr);
                                             // returns vector = {-1} if graph doesn't has an eulerian cycle;
    
    using lca_ns::lca; // vector<long> lca(const Graph &gr, const vector<pair<long, long> > &requests);

}
#endif

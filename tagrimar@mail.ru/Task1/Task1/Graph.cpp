//
//  Graph.cpp
//  Task1
//
//  Created by Taygrim on 15.03.13.
//  Copyright (c) 2013 Taygrim. All rights reserved.
//

#include "Graph.h"

namespace graph
{
    using graph::Graph;
    
    Graph::Graph()
    {
        directed = false;
    }
    
    void Graph::Build(long n, const vector<Edge> &edg, bool dir)
    {
        set_belonging(vector<bool>(n, true));
        edges = edg;
        directed = dir;
        g.assign(n, vector<long>(0,0));
        for(long i=0; i<edg.size(); i++)
        {
            g[edg[i].v1].push_back(edg[i].v2);
            if(!dir)
                g[edg[i].v2].push_back(edg[i].v1);
        }
    }
    
    Graph::Graph(long n, const vector<Edge> &edg, bool dir)
    {
        Build(n, edg, dir);
    }
    
    void Graph::AddEdge(Edge e)
    {
        g[e.v1].push_back(e.v2);
        if(!directed)
            g[e.v2].push_back(e.v1);
        edges.push_back(e);
    }
    
    const vector <vector<long> >& Graph::get_g() const
    {
        return g;
    }
    
    const vector<Edge>& Graph::get_edges() const
    {
        return edges;
    }
    
    const vector <bool>& Graph::get_belonging() const
    {
        return belonging;
    }
    
    void Graph::set_belonging(const vector <bool>&  mask)
    {
        belonging = mask;
    }
    
    void Graph::add_vertex(long i)
    {
        belonging[i] = true;
    }
}
//
//  Graph.h
//  Task1
//
//  Created by Taygrim on 15.03.13.
//  Copyright (c) 2013 Taygrim. All rights reserved.
//

#ifndef __Task1__Graph__
#define __Task1__Graph__

#include <vector>

using std::vector;

namespace graph
{
    struct Edge
    {
        long v1;
        long v2;
        
        Edge(long vv1 = 0, long vv2 = 0)
        {
            v1 = vv1;
            v2 = vv2;
        }
    };
    
    class Graph
    {
    public:
        Graph();
        Graph(long n, const vector<Edge> &edg = vector<Edge>(0), bool dir = false);
        void Build(long n, const vector<Edge> &edg = vector<Edge>(0), bool dir = false);
        void AddEdge(Edge e);
        const vector <vector<long> >& get_g() const;
        const vector <Edge>& get_edges() const;
        const vector <bool>& get_belonging() const;
        void set_belonging(const vector <bool>&  mask);
        void add_vertex(long i);
        
    private:
        bool directed;
        vector <Edge> edges;
        vector <vector<long> > g;
        vector <bool> belonging;
    };
}
#endif /* defined(__Task1__Graph__) */

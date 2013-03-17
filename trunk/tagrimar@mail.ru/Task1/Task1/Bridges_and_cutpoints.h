//
//  Bridges_and_cutpoints.h
//  Task1
//
//  Created by Taygrim on 15.03.13.
//  Copyright (c) 2013 Taygrim. All rights reserved.
//

#ifndef __Task1__Bridges_and_cutpoints__
#define __Task1__Bridges_and_cutpoints__
#include "Graph.h"

using namespace graph;

namespace bridges_and_cutpoints
{
    union value
    {
        struct
        {
            long v1;
            long v2;
        };
        long cutpoint;
    };

    enum color {WHITE, GREY, BLACK};
    extern vector <color> state;
    extern vector <vector <long> > g;
    extern vector <long> tin;
    extern vector <value> dfs_result;
    extern Graph current_component;
    extern long timer;
    extern long type;
    
    void dfs(long v, long p);
    
    
    void dfs(long v, long prev = -1);
    void dfs_cutpoints(long v, long num, vector <Graph>& res, long prev = -1);
    void dfs_bridges(long v, long num, vector <Graph>& res, long prev = -1);
    vector <Edge> find_bridges(const Graph &gr);
    vector <long> find_cutpoints(const Graph &gr);
    vector <Graph> biconnected_edged_components(const Graph &gr);
    vector <Graph> biconnected_vertex_components(const Graph &gr);

}

#endif /* defined(__Task1__Bridges_and_cutpoints__) */

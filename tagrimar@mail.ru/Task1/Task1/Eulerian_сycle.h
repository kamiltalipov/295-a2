//
//  Eulerian_сycle.h
//  Task1
//
//  Created by Taygrim on 17.03.13.
//  Copyright (c) 2013 Taygrim. All rights reserved.
//

#ifndef __Task1__Eulerian__ycle__
#define __Task1__Eulerian__ycle__

#include "Graph.h"

using namespace graph;

namespace eulerian_cycle_ns
{
    extern vector< vector <long> >g;
    extern vector<bool> used;
    
    void dfs(long v);
    vector<long> eulerian_cycle(const Graph &gr);
}

#endif /* defined(__Task1__Eulerian__ycle__) */

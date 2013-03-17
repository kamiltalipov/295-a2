//
//  Strongly_connected_components.h
//  Task1
//
//  Created by Taygrim on 17.03.13.
//  Copyright (c) 2013 Taygrim. All rights reserved.
//

#ifndef __Task1__Strongly_connected_components__
#define __Task1__Strongly_connected_components__
#include "Graph.h"
#include <stack>

using std::stack;
using namespace graph;

namespace strongly_connected_components
{
    extern vector <vector <long> > g, gt;
    extern vector<long> root;
    extern vector<long> index;
    extern vector<bool> in_component;
    extern vector<Graph> res;
    extern vector<bool> used;
    extern vector<bool> sorted;
    extern long ind;
    
    void dfs_tar(long v, stack<long> &st);
    vector<Graph> Tarjan(const Graph &gr);
    
    
    void dfs1(long v);
    void dfs2(long v);
    vector<Graph> Kosaraju(const Graph &gr);
}


#endif /* defined(__Task1__Strongly_connected_components__) */

//
//  LCA.h
//  Task1
//
//  Created by Taygrim on 17.03.13.
//  Copyright (c) 2013 Taygrim. All rights reserved.
//

#ifndef __Task1__LCA__
#define __Task1__LCA__
#include "Graph.h"
#include "DSU.h"

using namespace graph;
using namespace dsu;
using std::pair;
using std::make_pair;

namespace lca_ns
{
    extern vector<bool> used;
    extern vector<vector<long> > g;
    extern vector<vector<pair<long, long> > > q;
    extern vector<long> res;
    extern vector<long> ancestor;
    extern DSU d;
    
    void dfs(long v);
    
    vector<long> lca(const Graph &gr, const vector<pair<long, long> > &requests);
}

#endif /* defined(__Task1__LCA__) */

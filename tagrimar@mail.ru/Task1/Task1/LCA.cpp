//
//  LCA.cpp
//  Task1
//
//  Created by Taygrim on 17.03.13.
//  Copyright (c) 2013 Taygrim. All rights reserved.
//

#include "LCA.h"

namespace lca_ns
{
    vector<bool> used;
    vector<vector<long> > g;
    vector<vector<pair<long, long> > > q;
    vector<long> res;
    vector<long> ancestor;
    DSU d;
    
    void dfs(long v)
    {
        used[v] = true;
        for(long i=0; i<g[v].size(); i++)
            if(!used[g[v][i]])
            {
                dfs(g[v][i]);
                d.unit_sets(v, g[v][i]);
                ancestor[d.find_set(v)] = v;
            }
        for(long i=0; i<q[v].size();i++)
            if(used[q[v][i].first])
                res[q[v][i].second] = ancestor[d.find_set(q[v][i].first)];
    }
    
    vector<long> lca(const Graph &gr, const vector<pair<long, long> > &requests)
    {
        g = gr.get_g();
        res.assign(requests.size(), 0);
        ancestor.assign(g.size(),0);
        for(long i=0; i<g.size(); i++)
            ancestor[i] = i;
        used.assign(g.size(), false);
        q.assign(g.size(), vector<pair<long, long> >(0));
        d = DSU(g.size());
        
        for(long i=0; i<requests.size(); i++)
        {
            q[requests[i].first].push_back(make_pair(requests[i].second, i));
            q[requests[i].second].push_back(make_pair(requests[i].first, i));
        }
        
        dfs(0);
        return res;
    }
}

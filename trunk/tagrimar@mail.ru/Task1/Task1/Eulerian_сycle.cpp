//
//  Eulerian_сycle.cpp
//  Task1
//
//  Created by Taygrim on 17.03.13.
//  Copyright (c) 2013 Taygrim. All rights reserved.
//

#include "Eulerian_сycle.h"
#include <stack>
#include <set>

using std::stack;
using std::set;

namespace eulerian_cycle_ns
{
    vector< vector <long> >g;
    vector<bool> used;
    
    void dfs(long v)
    {
        used[v] = true;
        for(long i=0; i<g[v].size(); i++)
            if(!used[g[v][i]])
                dfs(g[v][i]);
    }
    
    vector<long> eulerian_cycle(const Graph &gr)
    {
        g=gr.get_g();
        bool flag=true, flag2=false;
        used.assign(g.size(), false);
        
        for(long i=0; i<g.size(); i++)
        {
            if(g[i].size() && !used[i])
                if(flag2)
                    flag = false;
                else
                {
                    dfs(i);
                    flag2=true;
                }
                
            if(g[i].size() % 2)
                flag = false;
        }
        
        if(flag == false)
            return vector<long>(1, -1);
        
        vector<long> res;
        vector<Edge> edges = gr.get_edges();
        vector<long> last(g.size(),0);
        used.assign(edges.size(),false);
        g.assign(g.size(), vector<long>(0));
        
        for(long i=0; i<edges.size(); i++)
        {
            g[edges[i].v1].push_back(i);
            g[edges[i].v2].push_back(i);
        }
        
        stack <long> st;
        
        for(long i=0; i<g.size(); i++)
            if(g[i].size())
            {
                st.push(i);
                break;
            }
        
        while(!st.empty())
        {
            long v = st.top();
            for(last[v]; last[v]<g[v].size(); last[v]++)
                if(!used[g[v][last[v]]])
                    break;
            
            if(last[v] != g[v].size())
            {
                long k = g[v][last[v]];
                if(edges[k].v1 == st.top())
                    st.push(edges[k].v2);
                else
                    st.push(edges[k].v1);
                
                used[k] = true;
            }
            else
            {
                res.push_back(v);
                st.pop();
            }
        }
        return res;
    }
}

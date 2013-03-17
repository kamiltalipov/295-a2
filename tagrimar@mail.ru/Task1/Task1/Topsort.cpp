//
//  Topsort.cpp
//  Task1
//
//  Created by Taygrim on 15.03.13.
//  Copyright (c) 2013 Taygrim. All rights reserved.
//

#include "Topsort.h"
#include <stack>
#include <algorithm>
using std::stack;
using std::pair;
using std::make_pair;

namespace topsort_ns
{
    vector <color> state;
    vector <vector <long> > g;
    vector <long> sorted;
    bool cycle;
    
    void dfs(long v)
    {
        stack <pair<long, long> > st;
        st.push(make_pair(v, 0));
        state[v] = GREY;
        
        while(!st.empty())
        {
            v = st.top().first;
            state[v]=GREY;
            bool flag = false;
            
            for(size_t i=st.top().second; i<g[v].size(); i++)
                if(state[g[v][i]] == WHITE)
                {
                    st.top().second++;
                    st.push(make_pair(g[v][i], 0));
                    flag = true;
                    break;
                }
                else
                    if(state[g[v][i]] == GREY)
                        cycle = true;
            if(!flag)
            {
                state[v] = BLACK;
                sorted.push_back(v);
                st.pop();
            }
        }
    }
   
    vector <long> topsort(const graph::Graph &gr)
    {
        g = gr.get_g();
        state.assign(g.size(), WHITE);
        sorted.clear();
        cycle = false;
        
        for(long i=0; i<g.size(); i++)
            if(state[i] == WHITE)
                dfs(i);
        std::reverse(sorted.begin(), sorted.end());
        if(cycle)
            return vector<long>(1, -1);
        
        return sorted;
    }
}
//
//  Strongly_connected_components.cpp
//  Task1
//
//  Created by Taygrim on 17.03.13.
//  Copyright (c) 2013 Taygrim. All rights reserved.
//

#include "Strongly_connected_components.h"
using std::min;
namespace strongly_connected_components
{
    vector< vector<long> > g, gt;
    vector<long> root;
    vector<long> index;
    vector<bool> in_component;
    vector<bool> used;
    vector<bool> sorted;
    vector<Graph> res;
    long ind;
    
    void dfs_tar(long v, stack<long> &st)
    {
        root[v] = index[v] = ++ind;
        st.push(v);
        
        for(long i=0; i<g[v].size(); i++)
        {
            if(index[g[v][i]] == -1)
                dfs_tar(g[v][i], st);
        
            if(!in_component[g[v][i]])
                root[v] = min(root[v], root[g[v][i]]);
        }
        
        if(root[v] == index[v])
        {
            long n = res.size();
            res.push_back(Graph(g.size()));
            res[n].set_belonging(vector<bool> (g.size(),false));
            bool flag = true;
            while(flag)
            {
                if(st.top() == v)
                    flag = false;
                
                res[n].add_vertex(st.top());
                for(long i=0; i<g[st.top()].size(); i++)
                    if((!in_component[g[st.top()][i]] && root[g[st.top()][i]] >= root[v]) || res[n].get_belonging()[g[st.top()][i]] == true)
                        res[n].AddEdge(Edge(st.top(), g[st.top()][i]));
                
                in_component[st.top()] = true;
                st.pop();
            }
        }
    }
    
    vector<Graph> Tarjan(const Graph &gr)
    {
        g = gr.get_g();
        ind = 0;
        index.assign(g.size(), -1);
        root.assign(g.size(), 1000000000);
        in_component.assign(g.size(), false);
        res.resize(0);
        
        stack <long> st;
        for(long i=0; i<g.size(); i++)
            if(index[i] == -1)
                dfs_tar(i, st);
        return res;
    }
    
    void dfs1(long v)
    {
        used[v] = true;
        for(long i=0; i<g[v].size(); i++)
            if(!used[g[v][i]])
                dfs1(g[v][i]);
        
        sorted.push_back(v);
    }

    void dfs2(long v)
    {
        used[v] = true;
        res[res.size()-1].add_vertex(v);
        index[v] = res.size();
        for(long i=0; i<gt[v].size(); i++)
            if(!used[gt[v][i]])
            {
                dfs2(gt[v][i]);
                res[res.size()-1].AddEdge(Edge(gt[v][i], v));
            }
            else
                if(index[g[v][i]] == res.size())
                    res[res.size()-1].AddEdge(Edge(gt[v][i], v));
    }
    
    vector<Graph> Kosaraju(const Graph &gr)
    {
        g = gr.get_g();
        gt.assign(g.size(), vector<long>(0));
        used.assign(g.size(),false);
        res.resize(0);
        
        for(long i=0; i<g.size(); i++)
            for(long j=0; j<g[i].size(); j++)
                gt[g[i][j]].push_back(i);
        
        for(long i=0; i<g.size(); i++)
            if(!used[i])
                dfs1(i);
        
        used.assign(g.size(), false);
        index.assign(g.size(), -1);
        
        for(long i=0; i<g.size(); i++)
            if(!used[i])
            {
                long n = res.size();
                res.push_back(Graph(g.size()));
                res[n].set_belonging(vector<bool> (g.size(),false));
                dfs2(i);
            }
        return res;
    }
}

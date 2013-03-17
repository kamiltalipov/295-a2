//
//  Bridges_and_cutpoints.cpp
//  Task1
//
//  Created by Taygrim on 15.03.13.
//  Copyright (c) 2013 Taygrim. All rights reserved.
//

#include "Bridges_and_cutpoints.h"
using std::min;

namespace bridges_and_cutpoints
{
    vector <color> state;
    vector <vector <long> > g;
    vector <long> tin;
    vector <long> fup;
    vector <value> dfs_result;
    Graph current_component;
    long timer;
    long type; //0 - bridges, 1 - cutpoints
    
    void dfs(long v, long prev)
    {
        value temp;
        state[v] = GREY;
        fup[v] = tin[v] = timer++;
        
        long children = 0;
        for(long i=0; i<g[v].size(); i++)
        {
            if(g[v][i] == prev)
                continue;
            
            if(state[g[v][i]] != WHITE)
                fup[v] = min(fup[v], tin[g[v][i]]);
            else
            {
                dfs(g[v][i], v);
                fup[v] = min(fup[v], fup[g[v][i]]);
                if(type && fup[g[v][i]] >= tin[v] && prev!=-1)
                {
                    temp.cutpoint = v;
                    dfs_result.push_back(temp);
                }
                
                if(!type && fup[g[v][i]] > tin[v])
                {
                    temp.v1 = v;
                    temp.v2 = g[v][i];
                    dfs_result.push_back(temp);
                }
                children++;
            }
        }
        if(type && prev == -1 && children > 1)
        {
            temp.cutpoint = v;
            dfs_result.push_back(temp);
        }
    }
    
    void dfs_bridges(long v, long num, vector <Graph>& res, long prev)
    {
        state[v] = GREY;
        res[num].add_vertex(v);
        
        for(long i=0; i<g[v].size(); i++)
        {
            
            if(state[g[v][i]] != BLACK && prev != g[v][i]  && !(fup[g[v][i]] > tin[v]))
                res[num].AddEdge(Edge(v, g[v][i]));
                
            if(state[g[v][i]] == WHITE)
                if(fup[g[v][i]] > tin[v])
                {
                    long num1 = res.size();
                    res.push_back(Graph(g.size()));
                    res[num1].set_belonging(vector<bool>(g.size(),false));
                    dfs_bridges(g[v][i], num1, res, v);
                }
                else
                    dfs_bridges(g[v][i], num, res, v);
        }
        state[v] = BLACK;
    }

    void dfs_cutpoints(long v, long num, vector <Graph>& res, long prev)
    {
        state[v] = GREY;
        res[num].add_vertex(v);
        
        long children = 0;
        for(long i=0; i<g[v].size(); i++)
        {
            
            if(state[g[v][i]] != BLACK && ((prev == -1 && children < 1)|| (prev != g[v][i]  && !(fup[g[v][i]] >= tin[v]))))
                res[num].AddEdge(Edge(v, g[v][i]));
            
            if(state[g[v][i]] == WHITE)
            {
                children++;
                
                if((fup[g[v][i]] >= tin[v] && prev != -1) || (prev == -1 && children > 1))
                {
                    long num1 = res.size();
                    res.push_back(Graph(g.size()));
                    res[num1].set_belonging(vector<bool>(g.size(),false));
                    res[num1].AddEdge(Edge(v, g[v][i]));
                    res[num1].add_vertex(v);
                    dfs_cutpoints(g[v][i], num1, res, v);
                }
                else
                    dfs_cutpoints(g[v][i], num, res, v);
            }
        }
        state[v] = BLACK;
    }

    vector <Edge> find_bridges(const Graph &gr)
    {
        type = 0;
        g = gr.get_g();
        tin.resize(g.size());
        fup.resize(g.size());
        dfs_result.clear();
        timer = 0;
        state.assign(g.size(), WHITE);
        
        for(long i=0; i<g.size(); i++)
            if(state[i] == WHITE)
                dfs(i);
        
        vector <Edge> res(dfs_result.size());
        for(long i=0; i<dfs_result.size(); i++)
            res[i] = Edge(dfs_result[i].v1, dfs_result[i].v2);
        
        return res;
    }
    
    vector <long> find_cutpoints(const Graph &gr)
    {
        type = 1;
        g = gr.get_g();
        tin.resize(g.size());
        fup.resize(g.size());
        dfs_result.clear();
        timer = 0;
        state.assign(g.size(), WHITE);
        
        for(long i=0; i<g.size(); i++)
            if(state[i] == WHITE)
                dfs(i);
        
        vector <long> res;
        vector <bool> point(g.size(), false);
        
        for(long i=0; i<dfs_result.size(); i++)
            point[dfs_result[i].cutpoint] = true;
        
        for(long i=0; i<g.size(); i++)
            if(point[i])
                res.push_back(i);
        
        return res;
    }
    
    vector <Graph> biconnected_edged_components(const Graph &gr)
    {
        vector <Graph> res;
        find_bridges(gr);
        
        state.assign(g.size(), WHITE);
        for(long i=0; i<g.size(); i++)
            if(state[i] == WHITE)
            {
                long num = res.size();
                res.push_back(Graph(g.size()));
                res[res.size()-1].set_belonging(vector<bool> (g.size(),false));
                dfs_bridges(i, num, res);
                
            }
        return res;
    }
    
    vector <Graph> biconnected_vertex_components(const Graph &gr)
    {
        vector <Graph> res;
        find_cutpoints(gr);
        
        state.assign(g.size(), WHITE);
        for(long i=0; i<g.size(); i++)
            if(state[i] == WHITE)
            {
                long num = res.size();
                res.push_back(Graph(g.size()));
                res[res.size()-1].set_belonging(vector<bool> (g.size(),false));
                dfs_cutpoints(i, num, res);
            }
        return res;
    }
}
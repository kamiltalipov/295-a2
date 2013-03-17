//
//  main.cpp
//  Task1
//
//  Created by Taygrim on 15.03.13.
//  Copyright (c) 2013 Taygrim. All rights reserved.
//

#include "Graph.h" // Vertex numeration from 0
#include "Graph_algorithms.h"
#include "DSU.h"
#include <iostream>
#include <vector>

using namespace graph_algorithms;
using std::vector;
using std::cin;
using std::cout;
using namespace graph;
using namespace dsu;

void problem_1() //topsort
{
    long n, m;
    cin>>n>>m;
    vector <Edge> mass(m);
    for(long i=0; i<m; i++)
        cin>>mass[i].v1>>mass[i].v2;
    
    Graph g(n, mass, true);
    
    vector <long> res = topsort(g);
    if(res == vector <long>(1,-1))
        cout<<"Graph has a cycle.\n";
    else
        for(long i=0; i<res.size(); i++)
            cout<<res[i]<<" ";
    cout<<"\n";
}

void problem_2() //cutpoints, bridges, biconnected edged components, biconnected vertex components
{
    long n, m;
    cin>>n>>m;
    vector <Edge> mass(m);
    for(long i=0; i<m; i++)
        cin>>mass[i].v1>>mass[i].v2;
    
    Graph g(n, mass, false);
    
    vector <Edge> bridges = find_bridges(g);
    cout<<"Bridges:\n";
    for(long i=0; i<bridges.size(); i++)
        cout<<bridges[i].v1<<" "<<bridges[i].v2<<"\n";
    
    vector <long> cutpoints = find_cutpoints(g);
    cout<<"Cutpoints:\n";
    for(long i=0; i<cutpoints.size(); i++)
        cout<<cutpoints[i]<<" ";
    cout<<"\n";
    
    vector <Graph> ed_comp = biconnected_edged_components(g);
    cout<<"Biconnected edged components:\n";
    for(long i=0; i<ed_comp.size(); i++)
    {
        cout<<"Component "<<i+1<<":\n";
        cout<<"    Points:\n    ";
        vector <bool> temp = ed_comp[i].get_belonging();
        for(long j=0; j<temp.size(); j++)
            if(temp[j])
                cout<<j<<" ";
        cout<<"\n    Edges:\n";
        vector <Edge> temp2 = ed_comp[i].get_edges();
        for(long j=0; j<temp2.size(); j++)
            cout<<"    "<<temp2[j].v1<<" "<<temp2[j].v2<<"\n";
    }
    
    vector <Graph> ver_comp = biconnected_vertex_components(g);
    cout<<"Biconnected vertex components:\n";
    for(long i=0; i<ver_comp.size(); i++)
    {
        cout<<"Component "<<i+1<<":\n";
        cout<<"    Points:\n    ";
        vector <bool> temp = ver_comp[i].get_belonging();
        for(long j=0; j<temp.size(); j++)
            if(temp[j])
                cout<<j<<" ";
        cout<<"\n    Edges:\n";
        vector <Edge> temp2 = ver_comp[i].get_edges();
        for(long j=0; j<temp2.size(); j++)
            cout<<"    "<<temp2[j].v1<<" "<<temp2[j].v2<<"\n";
    }
    
}

void problem_3() //strongly connected components
{
    long n, m;
    cin>>n>>m;
    vector <Edge> mass(m);
    for(long i=0; i<m; i++)
        cin>>mass[i].v1>>mass[i].v2;
    
    Graph g(n, mass, true);
    
    vector <Graph> strong_comp = Tarjan(g);
    cout<<"Strongly connected components by Tarjan:\n";
    for(long i=0; i<strong_comp.size(); i++)
    {
        cout<<"Component "<<i+1<<":\n";
        cout<<"    Points:\n    ";
        vector <bool> temp = strong_comp[i].get_belonging();
        for(long j=0; j<temp.size(); j++)
            if(temp[j])
                cout<<j<<" ";
        cout<<"\n    Edges:\n";
        vector <Edge> temp2 = strong_comp[i].get_edges();
        for(long j=0; j<temp2.size(); j++)
            cout<<"    "<<temp2[j].v1<<" "<<temp2[j].v2<<"\n";
    }
    
    strong_comp = Kosaraju(g);
    cout<<"Strongly connected components by Kosaraju:\n";
    for(long i=0; i<strong_comp.size(); i++)
    {
        cout<<"Component "<<i+1<<":\n";
        cout<<"    Points:\n    ";
        vector <bool> temp = strong_comp[i].get_belonging();
        for(long j=0; j<temp.size(); j++)
            if(temp[j])
                cout<<j<<" ";
        cout<<"\n    Edges:\n";
        vector <Edge> temp2 = strong_comp[i].get_edges();
        for(long j=0; j<temp2.size(); j++)
            cout<<"    "<<temp2[j].v1<<" "<<temp2[j].v2<<"\n";
    }
}

void problem_4() //eulerian cycle
{
    long n, m;
    cin>>n>>m;
    vector <Edge> mass(m);
    for(long i=0; i<m; i++)
        cin>>mass[i].v1>>mass[i].v2;
    
    Graph g(n, mass, false);
    
    vector<long> res = eulerian_cycle(g);
    if(res.size() == 1 && res[0] == -1)
    {
        cout<< "No eulerian cycle.\n";
        return;
    }
    
    for(long i=0; i<res.size(); i++)
        cout<<res[i]<<" ";
    cout<<"\n";
}

void problem_5() //DSU
{
    long n, m, k; //описание графа и количество запросов
    cin>>n>>m;
    
    DSU conherence(n);
    for(long i=0; i<m; i++)
    {
        long a, b;
        cin>>a>>b;
        conherence.unit_sets(a, b);
    }
    
    cin>>k;
    
    for(long i=0; i<k; i++)
    {
        long type, a, b;
        cin>>type; // 0 - добавить ребро, 1 - запрос про связность
        cin>>a>>b;
        if(type)
            if(conherence.same_set(a, b))
                cout<<"They are connected\n";
            else
                cout<<"They are not connected\n";
        else
            conherence.unit_sets(a, b);
    }
}

void problem_6() //LCA
{
    long n, m;
    cin>>n>>m;
    vector <Edge> mass(m);
    for(long i=0; i<m; i++)
        cin>>mass[i].v1>>mass[i].v2;
    
    Graph g(n, mass, false);

    long k;
    cin>>k;
    
    vector <pair<long, long> > req(k);
    for(long i=0; i<k; i++)
        cin>>req[i].first>>req[i].second;
    
    vector<long> res = lca(g, req);
    
    for(long i=0; i<k; i++)
        cout<<res[i]<<" ";
    cout<<"\n";
}

int main(int argc, const char * argv[])
{
    problem_6();
    return 0;
}

//
//  main.cpp
//  4
//
//  Created by Taygrim on 15.04.13.
//  Copyright (c) 2013 Taygrim. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include "DSU.h"

using namespace dsu;
using namespace std;

struct edge
{
    int v1;
    int v2;
    int len;
    edge(int a = 0, int b = 0, int l = 0)
    {
        v1 = a;
        v2 = b;
        len = l;
    }
};

bool operator < (const edge &a, const edge &b)
{
    return a.len < b.len;
}

int main()
{
    int n, m;
    cin>>n>>m;
    
    vector<edge> edges(m);
    DSU connected(n);
    
    for(int i=0; i<m; i++)
    {
        int a, b, l;
        cin>>a>>b>>l;
        edges[i] = edge(a, b, l);
    }
    
    sort(edges.begin(), edges.end());
    
    vector<edge> res;
    int sum = 0;
    
    for(int i=0; i<m; i++)
        if(!connected.same_set(edges[i].v1, edges[i].v2))
        {
            res.push_back(edges[i]);
            sum+=edges[i].len;
            connected.unit_sets(edges[i].v1, edges[i].v2);
        }
    
    
    cout<<sum<<"\n";
    for(int i=0; i<res.size(); i++)
        cout<<res[i].v1<<" "<<res[i].v2<<" "<<res[i].len<<"\n";
}


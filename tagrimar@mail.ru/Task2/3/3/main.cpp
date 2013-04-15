//
//  main.cpp
//  3
//
//  Created by Taygrim on 14.04.13.
//  Copyright (c) 2013 Taygrim. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include "DSU.h"

using namespace std;
using namespace dsu;

struct edge
{
    int v1;
    int v2;
    double len;
};

bool operator < (const edge &a, const edge &b)
{
    return (a.len < b.len);
}

int main(int argc, const char * argv[])
{
    int n, m;
    cin>>n>>m;
    
    vector<edge> e(m);
    
    for(int i=0; i<m; i++)
        cin>>e[i].v1>>e[i].v2>>e[i].len;
    
    sort(e.begin(), e.end());
    
    DSU d(n);
    
    vector<edge> res;
    for(int  i=0; i<m; i++)
        if(d.same_set(e[i].v1, e[i].v2))
        {
            d.unit_sets(e[i].v1, e[i].v2);
            for(int j=0; j<i; j++)
                if(d.same_set(e[i].v1, e[j].v1))
                    res.push_back(e[j]);
            break;
        }
        else
            d.unit_sets(e[i].v1, e[i].v2);
    
    double average_cost = 0;
    for(int i=0; i<res.size(); i++)
    {
        cout<<res[i].v1<<" "<<res[i].v2<<" "<<res[i].len<<"\n";
        average_cost += res[i].len;
    }
    
    average_cost /= res.size();
    
    cout<<"average cost = "<<average_cost<<"\n";
}


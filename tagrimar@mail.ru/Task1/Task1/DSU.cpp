//
//  DSU.cpp
//  Task1
//
//  Created by Taygrim on 17.03.13.
//  Copyright (c) 2013 Taygrim. All rights reserved.
//

#include "DSU.h"

namespace dsu
{
    DSU::DSU()
    {
    }
    
    DSU::DSU(long n)
    {
        parent = vector<long> (n);
        for(long i=0; i<n; i++)
            parent[i] = i;
        
        rank = vector<long> (n,0);
    }
    
    void DSU::make_set(long v)
    {
        if(v >= parent.size())
        {
            long n = parent.size();
            
            parent.resize(v+1);
            rank.resize(v+1);
            
            for(long i=n; i<v; i++)
                make_set(i);
        }
        parent[v] = v;
        rank[v] = 0;
    }
    long DSU::find_set(long v)
    {
        if(parent[v] == v)
            return v;
        else
            return parent[v] = find_set(parent[v]);
    }
    
    void DSU::unit_sets(long a, long b)
    {
        a = find_set(a);
        b = find_set(b);
        
        if(a==b)
            return;
        
        if(rank[a] > rank[b])
            std::swap(a, b);
        
        parent[a] = b;
        rank[b] = std::max(rank[b], rank[a]+1);
    }
    
    bool DSU::same_set(long a, long b)
    {
        return find_set(a) == find_set(b);
    }
        
}
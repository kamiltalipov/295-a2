//
//  DSU.h
//  Task1
//
//  Created by Taygrim on 17.03.13.
//  Copyright (c) 2013 Taygrim. All rights reserved.
//

#ifndef __Task1__DSU__
#define __Task1__DSU__

#include <vector>

using std::vector;

namespace dsu
{
    class DSU
    {
    public:
        DSU();
        DSU(long n);
        void make_set(long v);
        long find_set(long v);
        void unit_sets(long a, long b);
        bool same_set(long a, long b);
        
    private:
        vector<long> parent;
        vector<long> rank;
    };
}

#endif /* defined(__Task1__DSU__) */

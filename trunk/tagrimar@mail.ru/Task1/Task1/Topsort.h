//
//  Topsort.h
//  Task1
//
//  Created by Taygrim on 15.03.13.
//  Copyright (c) 2013 Taygrim. All rights reserved.
//

#ifndef __Task1__Topsort__
#define __Task1__Topsort__

#include "Graph.h"

namespace topsort_ns
{
    enum color {WHITE, GREY, BLACK};
    extern vector <color> state;
    extern vector <vector <long> > g;
    extern vector <long> sorted;
    extern bool cycle;
    
    void dfs(long v);
    
    vector <long> topsort(const graph::Graph &gr);
}

#endif /* defined(__Task1__Topsort__) */

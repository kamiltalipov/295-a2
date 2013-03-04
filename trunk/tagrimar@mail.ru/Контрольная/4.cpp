//
//  main.cpp
//
//  Created by Taygrim on 04.03.13.
//  Copyright (c) 2013 Taygrim. All rights reserved.
//

#include <iostream>
#include <list>
#include <queue>

using namespace std;

int main(int argc, const char * argv[])
{
    list <int> a(5,100);
    queue <int, list<int> > b(a);

    return 0;
}


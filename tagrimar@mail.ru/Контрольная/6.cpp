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
    list<long> a;
    list<long> b;
    /*...*/
    b.splice(b.end(), a); // O(1)

    return 0;
}


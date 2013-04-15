//
//  main.cpp
//  2
//
//  Created by Taygrim on 15.04.13.
//  Copyright (c) 2013 Taygrim. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

vector <int> side;
vector< vector<bool> > acquaintance;

bool dfs(int v, int t)
{
    side[v] = t;
    for(int i=0; i<acquaintance[v].size(); i++)
        if(acquaintance[v][i] && i!=v)
        {
            if(side[i] == -1)
                if(dfs(i, 1-t) == false)
                    return false;
            
            if(side[i] == side[v])
                return false;
        }
    
    return true;
}

int main()
{
    int n;
    cin>>n;
    
    acquaintance.assign(n, vector<bool>(n,false));
    side.assign(n, -1);
    
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
        {
            int temp;
            cin>>temp;
            acquaintance[i][j] = temp;
        }
    
    for(int i=0; i<n; i++)
        if(side[i] == -1)
            if(dfs(i, 0) == false)
            {
                cout<<"Not possible";
                return 0;
            }
    
    cout<<"Possible";
}


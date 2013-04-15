//
//  main.cpp
//  1
//
//  Created by Taygrim on 15.04.13.
//  Copyright (c) 2013 Taygrim. All rights reserved.
//

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
using namespace std;


map < string, vector<string> > g;
map <string, long> used;

bool dfs(string v)
{
    if(used[v] == 1)
        return false;
    
    used[v]=1;
    
    for(long i=0; i<g[v].size(); i++)
        if(!dfs(g[v][i]))
            return false;
    
    used[v]=2;
    return true;
}

int main()
{
    long n;
    cin>>n;
    
    for(long i=0; i<n; i++)
    {
        string s;
        cin>>s;
        if(!g[s].empty())
        {
            cout<<"NOT CORRECT";
            return 0;
        }
        long k;
        cin>>k;
        string ss;
        for(long j=0; j<k; j++)
        {
            cin>>ss;
            g[s].push_back(ss);
        }
    }
    
    for(map <string, vector<string> > ::iterator i=g.begin();i!=g.end();i++)
    {
        if(!used[i->first])
            if(!dfs(i->first))
            {
                cout<<"NOT CORRECT";
                return 0;
            }
    }
    
    cout<<"CORRECT";
    return 0;
}
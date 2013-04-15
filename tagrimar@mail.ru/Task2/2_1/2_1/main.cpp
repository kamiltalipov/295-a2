//
//  main.cpp
//  2_1
//
//  Created by Taygrim on 14.04.13.
//  Copyright (c) 2013 Taygrim. All rights reserved.
//
//  Ford-Bellman

#include <iostream>
#include <vector>

using namespace std;

int main(int argc, const char * argv[])
{
    int n;
    cin>>n;
    vector<vector<double> > rate(n, vector<double> (n, 0));
    
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin>>rate[i][j];
    
    vector<vector<double> > d(rate.begin(), rate.end());
    
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            d[i][j] = -rate[j][i];
    
    for(int k=0; k<n; k++)
        for (int i=0; i<n-1; ++i)
            for (int j=0; j<n; ++j)
                d[k][j] = min (d[k][j], - (d[k][k] * rate[k][j]));
    
    bool flag = false;
    for(int i=0; i<n; i++)
        if(-d[i][i] > 1)
            flag = true;
    
    if(flag)
        cout<<"YES\n";
    else
        cout<<"NO\n";
}


//
//  main.cpp
//  3
//
//  Created by Taygrim on 15.04.13.
//  Copyright (c) 2013 Taygrim. All rights reserved.
//

#include <iostream>
#include <vector>
#include <set>
#include <stack>

using namespace std;

struct road
{
    int to;
    int len;
    road(int t = 0, int l = 0)
    {
        to = t;
        len = l;
    }
};

bool operator < (const road &a, const road &b)
{
    return a.len < b.len;
}

const int INF = 1000000000;

int main()
{
    int n, m;
    cin>>n>>m;
    
    vector< vector<road> > g(n);
    
    for(int i=0; i<m; i++)
    {
        int a, b, l;
        cin>>a>>b>>l;
        g[a].push_back(road(b,l));
        g[b].push_back(road(a,l));
        
    }
    
    vector<int> d(n, INF);
    d[0] = 0;
    vector<int> prev(n);
    
    set <road> q;
    q.insert(road(0, d[0]));
    
    while(!q.empty())
    {
        int v = q.begin() -> to;
        
        q.erase (q.begin());
        
		for (int i=0; i<g[v].size(); i++)
        {
			if (d[v] + g[v][i].len < d[g[v][i].to])
            {
				q.erase (road (g[v][i].to, d[g[v][i].to]));
				d[g[v][i].to] = d[v] + g[v][i].len;
				prev[g[v][i].to] = v;
				q.insert (road (g[v][i].to, d[g[v][i].to]));
			}
		}
    }
    
    for(int i=1; i<n; i++)
    {
        cout<<i<<" "<<d[i]<<"\n";
        stack<int> way;
        way.push(i);
        while(prev[way.top()])
            way.push(prev[way.top()]);
        
        while(!way.empty())
        {
            cout<<way.top()<<" ";
            way.pop();
        }
        
        cout<<"\n\n";
    }
}


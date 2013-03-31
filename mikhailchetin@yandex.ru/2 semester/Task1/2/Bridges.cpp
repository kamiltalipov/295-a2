#include<iostream>
#include<vector>
#include<stack>
#include<set>
using namespace std;

void dfs(int v,int p, int t,vector<vector<int>> &g, stack<int> &s1, stack<pair<int,int>> &s2,vector<int> &up, vector<int> &tin,vector<int> &color,set<int> &cutvertices,vector<pair<int,int>> &bridges, vector<vector<int>> &comp_edge,vector<vector<pair<int,int>>> &comp_vertice)
{
	s1.push(v);
	up[v]=tin[v]=t++;
	int children=0;
	color[v]=1;
	for(int i=0;i<g[v].size();i++)
	{
		int u=g[v][i];
		if(color[u]==0)
		{
			s2.push(make_pair(u,v));
			dfs(u,v,t,g,s1,s2,up,tin,color,cutvertices,bridges,comp_edge,comp_vertice);
			children++;
			up[v]=min(up[v],up[u]);
			if(up[u]>=tin[v])
			{
				cutvertices.insert(v);
				comp_vertice.resize(comp_vertice.size()+1);
				while(s2.top()!=make_pair(v,u) && s2.top()!=make_pair(u,v))
				{
					comp_vertice[comp_vertice.size()-1].push_back(s2.top());
					s2.pop();
				}
				comp_vertice[comp_vertice.size()-1].push_back(s2.top());
				s2.pop();
			}
			if(up[u]>=tin[u])
			{
				bridges.push_back(make_pair(v,u));
				comp_edge.resize(comp_edge.size()+1);
				while(s1.top()!=u)
				{
					comp_edge[comp_edge.size()-1].push_back(s1.top());
					s1.pop();
				}
				comp_edge[comp_edge.size()-1].push_back(s1.top());
				s1.pop();
			}
		}
		if(color[u]==1 && u!=p)
		{
			up[v]=min(up[v],tin[u]);
			s2.push(make_pair(u,v));
		}
		
	}
	color[v]=2;
	if(v==0 && children<2)
		cutvertices.erase(0);
	if(v==0 && !s1.empty())
	{
		comp_edge.resize(comp_edge.size()+1);
		while(!s1.empty())
		{
			comp_edge[comp_edge.size()-1].push_back(s1.top());
			s1.pop();
		}
	}
}

int main()
{
	int n,m,a,b;
	cin>>n>>m;
	vector<vector<int>> g(n);
	stack<int> s1;
	stack<pair<int,int>> s2;
	vector<int> up(n); 
	vector<int> tin(n);
	vector<int> color(n);
	set<int> cutvertices;
	vector<pair<int,int>> bridges;
	vector<vector<int>> comp_edge;
	vector<vector<pair<int,int>>> comp_vertice;
	for(int i=0;i<m;i++)
	{
		cin>>a>>b;
		g[a-1].push_back(b-1);
		g[b-1].push_back(a-1);
	}
	dfs(0,-1,0,g,s1,s2,up,tin,color,cutvertices,bridges,comp_edge,comp_vertice);

	set<int>::iterator it;
	for(it=cutvertices.begin();it!=cutvertices.end();it++)
		cout<<*it+1<<' ';
	cout<<endl<<endl;


	for(int i=0;i<bridges.size();i++)
		cout<<bridges[i].first+1<<' '<<bridges[i].second+1<<endl;
	cout<<endl;


	for(int i=0;i<comp_vertice.size();i++)
	{
		for(int j=0;j<comp_vertice[i].size();j++)
			cout<<comp_vertice[i][j].first+1<<' '<<comp_vertice[i][j].second+1<<"   ";
		cout<<endl;
	}
	cout<<endl;


	for(int i=0;i<comp_edge.size();i++)
	{
		for(int j=0;j<comp_edge[i].size();j++)
			cout<<comp_edge[i][j]+1<<' ';
		cout<<endl;
	}
	return 0;
}
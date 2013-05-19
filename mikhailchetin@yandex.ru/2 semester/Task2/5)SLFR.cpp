#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;

void dfs(int v, int p, int &l,int &timer,vector<int> &tin,vector<int> &tout, vector<vector<int>> &up,vector<vector<pair<int,int>>> &g) 
{
	tin[v]=++timer;
	up[v][0] = p;
	for (int i=1; i<=l; ++i)
		up[v][i] = up[up[v][i-1]][i-1];
	for (size_t i=0; i<g[v].size(); ++i) {
		int to = g[v][i].first;
		if (to != p)
			dfs (to, v,l,timer,tin,tout,up,g);
	}
	tout[v]=++timer;
}

bool upper (int a, int b, vector<int> &tin, vector<int> &tout) 
{
	return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int lca (int a, int b, int &l,vector<vector<int>> &up,vector<int> &tin, vector<int> &tout) 
{
	if (upper (a, b,tin,tout))  return a;
	if (upper (b, a,tin,tout))  return b;
	for (int i=l; i>=0; --i)
		if (! upper (up[a][i], b,tin,tout))
			a = up[a][i];
	return up[a][0];
}

struct edge
{
	int u;
	int v;
	int weight;
	int distance_u;
	int distance_v;
	edge(int _u,int _v,int _weight,int _distance_u,int _distance_v)
	{
		u=_u;
		v=_v;
		weight=_weight;
		distance_u=_distance_u;
		distance_v=_distance_v;
	}
	bool operator <(const edge &other) const
	{
		return distance_u+weight+distance_v<other.distance_u+other.weight+other.distance_v;
	}
};

int main() 
{

	int n, l,a,b,w,m;
	cin>>n>>m;
	vector<edge> not_tree_edges;
	vector<int> tin, tout;
	int timer;
	vector<int> ancestor(n),weight_ancestor(n),distance(n);
	vector < vector<int> > up;
	
	vector<vector<pair<int,int>>> g(n),escape_edge(n);
	for(int i=0;i<m;i++)
	{
		cin>>a>>b>>w;
		g[a].push_back(make_pair(b,w));//номера вершин с 0
		g[b].push_back(make_pair(a,w));
		escape_edge[a].push_back(make_pair(b,-1));
		escape_edge[b].push_back(make_pair(a,-1));
	}
	for(int i=1;i<n;i++)
		cin>>ancestor[i];

	for(int i=1;i<n;i++)
		for(int j=0;j<g[i].size();j++)
			if(g[i][j].first=ancestor[i])
				weight_ancestor[i]=g[i][j].second;

	for(int i=0;i<n;i++)
		for(int j=0;j<g[i].size();j++)
		{
			int u=i;
			int v=g[i][j].first;
			w=g[i][j].second;
			if(u!=ancestor[v] && v!=ancestor[u])
			{
				while(u!=0)
				{
					distance[i]+=weight_ancestor[u];
					u=ancestor[u];
				}
				while(v!=0)
				{
					distance[g[i][j].first]+=weight_ancestor[v];
					v=ancestor[v];
				}
				not_tree_edges.push_back(edge(i,g[i][j].first,w,distance[i],distance[g[i][j].first]));
			}
		}
	sort(not_tree_edges.begin(),not_tree_edges.end());

	tin.resize (n),  tout.resize (n),  up.resize (n);
	l = 1;
	while ((1<<l) <= n)  ++l;
	for (int i=0; i<n; ++i)  up[i].resize (l+1);
	dfs (0,0,l,timer,tin,tout,up,g);

	for(int i=0;i<not_tree_edges.size();i++)
	{
		int vertex=lca(not_tree_edges[i].u,not_tree_edges[i].v,l,up,tin,tout);
		for(int j=not_tree_edges[i].u;j!=vertex;j=ancestor[j])
			if(escape_edge[j][ancestor[j]].second==-1)
				escape_edge[j][ancestor[j]].second=i;
		for(int j=not_tree_edges[i].v;j!=vertex;j=ancestor[j])
			if(escape_edge[j][ancestor[j]].second==-1)
				escape_edge[j][ancestor[j]].second=i;
	}
}
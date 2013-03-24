#include<vector>
#include<iostream>

using namespace std;

class DSU
{
public:
	vector<int> rank;
	vector<int> parent;
	DSU(int n)
	{
		parent.resize(n);
		rank.resize(n);
		for(int i=0;i<n;i++)
			MakeSet(i);
	}
	void MakeSet(int i)
	{
		rank[i]=1;
		parent[i]=i;
	}
	int GetRoot(int i)
	{
		if(parent[i]==i)
			return i;
		return parent[i]=GetRoot(parent[i]);
	}
	void Unite(int i,int j)
	{
		j=GetRoot(j);
		i=GetRoot(i);
		if(rank[i]>rank[j])
			parent[j]=i;
		else
		{
			parent[i]=j;
			if(rank[i]==rank[j])
				rank[j]++;
		}
	}

};

void dfs(int v,DSU &dsu,vector<int> &ancestor,vector<int> &color,vector<vector<int>> &g,vector<vector<int>> &query)
{
	ancestor[v]=v;
	color[v]=1;
	for(int i=0;i<g[v].size();i++)
	{
		if(!color[g[v][i]])
		{
			dfs(g[v][i],dsu,ancestor,color,g,query);
			dsu.Unite(v,g[v][i]);
			ancestor[dsu.GetRoot(v)]=v;
		}
	}
	color[v]=2;
	for(int i=0;i<query[v].size();i++)
	{
		if(color[query[v][i]]==2)
			cout<<"LCA "<<v+1<<" and "<<query[v][i]+1<<" is "<<ancestor[dsu.GetRoot(query[v][i])]+1<<endl;
	}
}

int main()
{
	int n,m,a,b,k;
	cin>>n>>m;
	vector<vector<int>> g(n),query(n);
	vector<int> ancestor(n),color(n);
	DSU dsu(n);
	for(int i=0;i<m;i++)
	{
		cin>>a>>b;
		g[a-1].push_back(b-1);
		g[b-1].push_back(a-1);
	}
	cin>>k;
	for(int i=0;i<k;i++)
	{
		cin>>a>>b;
		query[a-1].push_back(b-1);
		query[b-1].push_back(a-1);
	}
	dfs(0,dsu,ancestor,color,g,query);
	return 0;
}
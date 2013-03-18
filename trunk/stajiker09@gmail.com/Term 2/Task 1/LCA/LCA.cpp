#include <iostream>
#include <vector>
using namespace std;
class DSU
{
public:
	DSU(int n)
	{
		parent.resize(n);
		size.resize(n);
		ancestor.resize(n);
	}
	void make_set(int v)
	{
		parent[v]=v;
		size[v]=1;
		ancestor[v]=v;
	}
	int find_set(int v)
	{
		if(v==parent[v])
			return v;
		return parent[v]=find_set(parent[v]);
	}
	void union_sets(int a, int b, int new_ancestor)
	{
		a=find_set(a);
		b=find_set(b);
		if(a!=b)
		{
			if(size[a]<size[b])
				swap(a, b);
			parent[b]=a;
			size[a]+=size[b];
			ancestor[a]=new_ancestor;
		}
	}
	vector <int> ancestor;
private:
	vector <int> parent;
	vector <int> size;
};
void dfs(int v, vector < vector <int> > &g, vector <bool> &used, vector < vector <int> > &q, DSU &dsu)
{
	used[v]=true;
	dsu.make_set(v);
	for(int i=0; i<g[v].size(); ++i)
		if(!used[g[v][i]])
		{
			dfs(g[v][i], g, used, q, dsu);
			dsu.union_sets(v, g[v][i], v);
		}
	for(int i=0; i<q[v].size(); ++i)
		if(used[q[v][i]]&&v!=dsu.ancestor[dsu.find_set(q[v][i])])
			printf("LCA %d %d : %d\n", v+1, q[v][i]+1, dsu.ancestor[dsu.find_set(q[v][i])]+1);
}
int main()
{
	int n, m;
	cin>>n;
	vector < vector <int> > g(n);
	vector < vector <int> > q(n);
	vector <bool> used(n);
	DSU dsu(n);
	for(int i=0; i<n-1; ++i)
	{
		int a, b;
		cin>>a>>b;
		g[a-1].push_back(b-1);
		g[b-1].push_back(a-1);
	}
	cin>>m;
	for(int i=0; i<m; ++i)
	{
		int a, b;
		cin>>a>>b;
		q[a-1].push_back(b-1);
		q[b-1].push_back(a-1);
	}
	dfs(0, g, used, q, dsu);
	return 0;
}
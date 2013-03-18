#include <iostream>
#include <vector>
using namespace std;
void dfs_on_g(int v, vector < vector <int> > &g, vector <bool> &used, vector <int> &order)
{
	used[v]=true;
	for(int i=0; i<g[v].size(); ++i)
		if(!used[g[v][i]])
			dfs_on_g(g[v][i], g, used, order);
	order.push_back(v);
}
void dfs_on_gt(int v, vector < vector <int> > &gt, vector <bool> &used, vector < vector <int> > &component)
{
	used[v]=true;
	component[component.size()-1].push_back(v);
	for(int i=0; i<gt[v].size(); ++i)
		if(!used[gt[v][i]])
			dfs_on_gt(gt[v][i], gt, used, component);
}
int main()
{
	int n, m;
	cin>>n>>m;
	vector < vector <int> > g(n), gt(n), component;
	vector <bool> used(n);
	vector <int> order;
	for(int i=0; i<m; ++i)
	{
		int a, b;
		cin>>a>>b;
		g[a-1].push_back(b-1);
		gt[b-1].push_back(a-1);
	}
	for(int i=0; i<n; ++i)
		if(!used[i])
			dfs_on_g(i, g, used, order);
	used.assign(n, false);
	for(int i=0; i<n; ++i)
		if(!used[order[i]])
		{
			component.resize(component.size()+1);
			dfs_on_gt(order[i], gt, used, component);
		}
	for(int i=0; i<component.size(); ++i)
	{
		for(int j=0; j<component[i].size(); ++j)
			printf("%d ", component[i][j]+1);
		printf("\n");
	}
	return 0;
}
#include<iostream>
#include<vector>

using namespace std;

void dfs_g(int v,vector<bool> &used,vector<vector<int>> &g,vector<int> &q)
{
	used[v]=true;
	for(int i=0;i<g[v].size();i++)
		if(!used[g[v][i]])
			dfs_g(g[v][i],used,g,q);
	q.push_back(v);
}

void dfs_gt(int v,vector<bool> &used,vector<vector<int>> &gt,vector<vector<int>> &comp)
{
	used[v]=true;
	for(int i=0;i<gt[v].size();i++)
		if(!used[gt[v][i]])
			dfs_gt(gt[v][i],used,gt,comp);
	comp[comp.size()-1].push_back(v);
}
int main()
{
	int n,m,a,b;
	cin>>n>>m;
	vector<vector<int>> g(n),gt(n),comp;
	vector<bool> used(n);
	vector<int> q;

	for(int i=0;i<m;i++)
	{
		cin>>a>>b;
		g[a-1].push_back(b-1);
		gt[b-1].push_back(a-1);
	}

	for(int i=0;i<n;i++)
		if(!used[i])
			dfs_g(i,used,g,q);

	used.assign(n,false);

	for(int i=n-1;i>=0;i--)
		if(!used[q[i]])
		{
			comp.resize(comp.size()+1);
			dfs_gt(q[i],used,gt,comp);
		}
	for(int i=0;i<comp.size();i++)
	{
		for(int j=0;j<comp[i].size();j++)
			cout<<comp[i][j]+1<<' ';
		cout<<endl;
	}
	return 0;
}
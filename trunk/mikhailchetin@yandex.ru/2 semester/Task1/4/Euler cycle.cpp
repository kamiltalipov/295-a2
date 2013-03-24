#include<iostream>
#include<vector>

using namespace std;

void dfs(int v, vector<vector<int>> &g,vector<int> &cycle)
{
	if(g[v].size())
	{
		int u=g[v][g[v].size()-1];
		g[v].pop_back();
		dfs(u,g,cycle);
	}
	cycle.push_back(v);
}

int main()
{
	int n,m,a,b;
	cin>>n>>m;
	vector<vector<int>> g(n);
	vector<int> degin(n),degout(n),cycle;
	for(int i=0;i<m;i++)
	{
		cin>>a>>b;
		g[a-1].push_back(b-1);
		degin[b-1]++;
		degout[a-1]++;
	}
	for(int i=0;i<n;i++)
		if(degin[i]!=degout[i])
		{
			cout<<"Euler cycle does not exist";
			return 0;
		}
	dfs(0,g,cycle);
	for(int i=cycle.size()-1;i>=0;i--)
		cout<<cycle[i]+1<<' ';
	return 0;
}
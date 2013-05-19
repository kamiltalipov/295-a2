#include<iostream>
#include<vector>
#include<string>
using namespace std;

bool dfs(int v, vector<bool> &used, vector<vector<int>> &g, vector<int> &M) 
{
	if(used[v])
		return false;
	used[v]=true;
	for (int i=0;i<g[v].size();i++) 
	{
		int u=g[v][i];
		if (M[u]==-1 || dfs(M[u],used,g,M)) 
		{
			M[u]=v;
			return true;
		}
	}
	return false;
}
 
int main() 
{
	string s,cube;
	int n,k;
	
	vector<int> M;
	vector<bool> used;
	vector<vector<int>> symbols(256);

	cin>>s;
	k=s.length();
	for(int i=0;i<s.length();i++)
		symbols[s[i]].push_back(i);

	cin>>n;
	vector<vector<int>> g(n);

	for(int i=0;i<n;i++)
	{
		cin>>cube;
		for(int j=0;j<cube.length();j++)
			for(int k=0;k<symbols[cube[j]].size();k++)
				g[i].push_back(symbols[cube[j]][k]);
	}

	M.assign(k,-1);
	for (int i=0;i<n;i++) 
	{
		used.assign(n,false);
		dfs(i,used,g,M);
	}
	for (int i=0; i<k; ++i)
		if (M[i] == -1)
		{
			cout<<"Impossible";
			return 0;
		}
	for (int i=0; i<k; ++i)
		if (M[i] != -1)
			cout<<M[i]+1<<' '<<s[i]<<endl;
}
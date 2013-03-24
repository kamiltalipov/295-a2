#include<iostream>
#include<vector>
#include<stack>

using namespace std;

void dfs(int v, vector<vector<int>> &g, vector<int> &ans,vector<int> &color)
{
	color[v]=1;
	stack<pair<int,int>> s;
	s.push(make_pair(v,0));
	while(!s.empty())
	{
		pair<int,int> u=s.top();
		s.pop();

		color[u.first]=1;
		if(u.second==g[u.first].size())
		{
			color[u.first]=2;
			ans.push_back(u.first);
		}
		else
		{
			s.push(make_pair(u.first,u.second+1));
			if(color[g[u.first][u.second]]==1)
			{
				cout<<"Top sort does not exist";
				return;
			}
			if(color[g[u.first][u.second]]==0)
				s.push(make_pair(g[u.first][u.second],0));
		}
	}
}

int main()
{
	int n,m,a,b;
	cin>>n>>m;
	vector<vector<int>> g(n);
	vector<int> color(n);
	vector<int> ans;
	for(int i=0;i<m;i++)
	{
		cin>>a>>b;
		g[a-1].push_back(b-1);
	}
	for(int i=0;i<n;i++)
		if(color[i]==0)
			dfs(i,g,ans,color);

	if(ans.size()==n)
		for(int i=n-1;i>=0;i--)
			cout<<ans[i]+1<<' ';

	return 0;
}
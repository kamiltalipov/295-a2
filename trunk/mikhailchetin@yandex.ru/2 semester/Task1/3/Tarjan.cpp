#include<iostream>
#include<vector>
#include<stack>
using namespace std;

void dfs(int v, int &t, vector<vector<int>> &g, vector<int> &color,stack<int> &s,vector<bool> &instack,vector<int> &tin,vector<int> &up,vector<vector<int>> &comp)
{
	color[v]=1;
	s.push(v);
	instack[v]=true;
	tin[v]=t;
	t++;
	up[v]=tin[v];
	for(int i=0;i<g[v].size();i++)
		if(color[g[v][i]]==0)
		{
			dfs(g[v][i],t,g,color,s,instack,tin,up,comp);
			up[v]=min(up[v],up[g[v][i]]);
		}
		else
			if(instack[g[v][i]])
				up[v]=min(up[v],tin[g[v][i]]);
	color[v]=2;
	if(up[v]==tin[v])
	{
		comp.resize(comp.size()+1);
		while(s.top()!=v)
		{
			comp[comp.size()-1].push_back(s.top());
			instack[s.top()]=false;
			s.pop();
		}
		comp[comp.size()-1].push_back(v);
		s.pop();
		instack[v]=false;
	}

}

int main()
{
	int a,b,n,m,t=0;
	cin>>n>>m;
	vector<vector<int>> g(n),comp;
	vector<int> color(n),tin(n),up(n);
	vector<bool> instack(n);
	stack<int> s;
	for(int i=0;i<m;i++)
	{
		cin>>a>>b;
		g[a-1].push_back(b-1);
	}
	for(int i=0;i<n;i++)
		if(!color[i])
			dfs(i,t,g,color,s,instack,tin,up,comp);

	for(int i=0;i<comp.size();i++)
	{
		for(int j=0;j<comp[i].size();j++)
			cout<<comp[i][j]+1<<' ';
		cout<<endl;
	}

	return 0;
}
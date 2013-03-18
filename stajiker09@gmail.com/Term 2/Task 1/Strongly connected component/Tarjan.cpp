#include <iostream>
#include <vector>
#include <stack>
using namespace std;
void dfs(int v, vector < vector <int> > &g, vector <bool> &used, vector <bool> &instack, int &timer, vector <int> &tin, vector <int> &tout, vector <int> &up, stack <int> &s)
{
	used[v]=true;
	instack[v]=true;
	tin[v]=timer++;
	up[v]=tin[v];
	s.push(v);
	for(int i=0; i<g[v].size(); ++i)
		if(!used[g[v][i]])
		{
			dfs(g[v][i], g, used, instack, timer, tin, tout, up, s);
			up[v]=min(up[v], up[g[v][i]]);
		}
		else
			if(instack[g[v][i]])
				up[v]=min(up[v], tin[g[v][i]]);
	if(up[v]==tin[v])
	{
		while(s.top()!=v)
		{
			cout<<s.top()+1<<' ';
			instack[s.top()]=false;
			s.pop();
		}
		cout<<v+1<<endl;
		s.pop();
	}
}
int main()
{
	int n, m, timer=0;
	cin>>n>>m;
	vector < vector <int> > g(n);
	vector <bool> used(n), instack(n);
	vector <int> tin(n), tout(n), up(n);
	stack <int> s;
	for(int i=0; i<m; ++i)
	{
		int a, b;
		cin>>a>>b;
		g[a-1].push_back(b-1);
	}
	for(int i=0; i<n; ++i)
		if(!used[i])
			dfs(0, g, used, instack, timer, tin ,tout, up, s);
	return 0;
}
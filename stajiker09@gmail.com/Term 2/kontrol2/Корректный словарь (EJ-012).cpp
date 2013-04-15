#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;
void dfs(int v, vector < vector <int> > &g, vector <int> &color)
{
	if(v<g.size())
	{
		color[v]=1;
		for(int i=0; i<g[v].size(); ++i)
		{
			int to=g[v][i];
			if(color[to]==0)
				dfs(to, g, color);
			if(color[to]==1)
			{
				printf("NOT CORRECT\n");
				exit(0);
			}
		}
	}
	color[v]=2;
}
int main()
{
	int d;
	cin>>d;
	vector < vector <string> > a(d);
	vector <string> s(d);
	for(int i=0; i<d; ++i)
	{
		cin>>s[i];
		int k;
		cin>>k;
		for(int j=0; j<k; ++j)
		{
			string S;
			cin>>S;
			a[i].push_back(S);
		}
	}
	map <string, int> m;
	for(int i=0; i<d; ++i)
		if(m.find(s[i])==m.end())
			m[s[i]]=i;
		else
		{
			printf("NOT CORRECT\n");
			return 0;
		}
	vector < vector <int> > g(d);
	int index=d;
	for(int i=0; i<d; ++i)
		for(int j=0; j<a[i].size(); ++j)
		{
			if(m.find(a[i][j])==m.end())
			{
				m[a[i][j]]=index;
				++index;
			}
			g[i].push_back(m[a[i][j]]);
		}
	vector <int> color(index);
	for(int i=0; i<d; ++i)
		if(color[i]==0)
			dfs(i, g, color);
	printf("CORRECT\n");
	return 0;
}
#include <iostream>
#include <vector>
#include <stack>
using namespace std;
void dfs(vector < vector <int> > &g, vector <int> &top_sort)
{
	stack < pair<int, int> > s;
	vector <int> color(g.size());
	for(int i=0; i<g.size(); ++i)
		if(color[i]==0)
		{
			color[i]=1;
			s.push(make_pair(i, 0));
			while(!s.empty())
			{
				pair<int, int> v=s.top();
				s.pop();
				if(v.second==g[v.first].size())
				{
					color[v.first]=2;
					top_sort.push_back(v.first);
				}
				else
				{
					s.push(make_pair(v.first, v.second+1));
					if(color[g[v.first][v.second]]==1)
					{
						top_sort.resize(0);
						return ;
					}
					if(color[g[v.first][v.second]]==0)
					{
						color[g[v.first][v.second]]=1;
						s.push(make_pair(g[v.first][v.second], 0));
					}
				}
			}
		}
}
int main()
{
	int n, m;
	cin>>n>>m;
	vector < vector <int> > g(n);
	vector <int> top_sort;
	for(int i=0; i<m; ++i)
	{
		int a, b;
		cin>>a>>b;
		g[a-1].push_back(b-1);
	}
	dfs(g, top_sort);
	if(top_sort.size()==0)
		printf("Topological order does not exist");
	else
		for(int i=n-1; i>=0; --i)
			cout<<top_sort[i]+1<<' ';
	return 0;
}
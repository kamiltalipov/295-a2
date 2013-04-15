#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int main()
{
	int n;
	cin>>n;
	vector < vector <bool> > acquaintance(n);
	vector < vector <int> > g(n);
	for(int i=0; i<n; ++i)
	{
		acquaintance[i].resize(n);
		int k;
		for(int j=0; j<n; ++j)
		{
			cin>>k;
			acquaintance[i][j]=k;
			if(acquaintance[i][j]==true&&i!=j)
				g[i].push_back(j);
		}
	}
	vector <int> color(n);
	queue <int> q;
	for(int i=0; i<n; ++i)
		if(color[i]==0)
		{
			q.push(i);
			color[i]=1;
			while(!q.empty())
			{
				int v=q.front();
				q.pop();
				for(int j=0; j<g[v].size(); ++j)
				{
					int to=g[v][j];
					if(color[to]==color[v])
					{
						printf("NO\n");
						return 0;
					}
					if(color[to]==0)
					{
						q.push(to);
						if(color[v]==1)
							color[to]=2;
						else
							color[to]=1;
					}
				}
			}
		}
	printf("YES\n");
	return 0;
}
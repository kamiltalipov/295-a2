#include <iostream>
#include <vector>
using namespace std;
struct edge
{
	int v,u;
	double weight;
};
int main()
{
	int n, m;
	double min_average_weight=INT_MAX;
	cin>>n>>m;
	vector<edge> g(m);
	vector<vector<double>> distance(n+1);
	for(int i=0;i<m;i++)
	{
		int u, v, weight;
		cin>>v>>u>>weight;
		g[i].v=v-1;
		g[i].u=u-1;
		g[i].weight=weight;
	}
	distance[0].assign(n,INT_MAX);
	distance[0][0]=0;
	for(int i=1;i<=n;i++)
	{
		distance[i].assign(n,INT_MAX);
		for(int j=0; j<m; ++j)
			if(distance[i-1][g[j].v]!=INT_MAX)
				distance[i][g[j].u]=min(distance[i][g[j].u], distance[i-1][g[j].v]+g[j].weight);
	}
	for(int i=0; i<n; i++)
		if(distance[n][i]!=INT_MAX)
		{
			double k;
			bool flag=false;
			for(int j=0;j<n;j++)
				if(distance[j][i]!=INT_MAX)
					if(flag)
						k=max(k,(distance[n][i]-distance[j][i])/(n-j));
					else
					{
						k=(distance[n][i]-distance[j][i])/(n-j);
						flag=true;
					}
			min_average_weight=min(min_average_weight, k);
		}
	if(min_average_weight==INT_MAX)
	{
		cout<<"No cycles";
		return 0;
	}
	cout<<min_average_weight;
}
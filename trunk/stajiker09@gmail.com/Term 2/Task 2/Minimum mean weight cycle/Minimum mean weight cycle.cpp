#include <iostream>
#include <vector>
using namespace std;
struct edge
{
	int v, to;
	double cost;
};
int main()
{
	int n, m;
	double min_mean_weight=1e9, eps=1e-9;
	cin>>n>>m;
	vector <edge> edges(m);
	vector < vector <double> > dist(n+1);
	for(int i=0; i<m; ++i)
	{
		int v, to, cost;
		cin>>v>>to>>cost;
		edges[i].v=v-1, edges[i].to=to-1, edges[i].cost=cost;
	}
	dist[0].assign(n, 1e9);
	dist[0][0]=0;
	for(int i=1; i<=n; ++i)
	{
		dist[i].assign(n, 1e9);
		for(int j=0; j<m; ++j)
			if(dist[i-1][edges[j].v]!=1e9)
				dist[i][edges[j].to]=min(dist[i][edges[j].to], dist[i-1][edges[j].v]+edges[j].cost);
	}
	for(int i=0; i<n; ++i)
		if(dist[n][i]!=1e9)
		{
			double k;
			bool check=false;
			for(int j=0; j<n; ++j)
				if(dist[j][i]!=1e9)
					if(check)
						k=max(k, (dist[n][i]-dist[j][i])/(n-j));
					else
					{
						k=(dist[n][i]-dist[j][i])/(n-j);
						check=true;
					}
			min_mean_weight=min(min_mean_weight, k);
		}
	if(min_mean_weight==1e9)
	{
		cout<<"No cycles";
		return 0;
	}
	printf("%.9lf\n", min_mean_weight);
	for(int i=0; i<m; ++i)
		edges[i].cost-=min_mean_weight;
	vector <double> d(n, 1e9);
	d[0]=0;
	vector <int> p(n, -1);
	int v;
	for(int i=0; i<n; ++i)
	{
		v=-1;
		for(int j=0; j<m; ++j)
			if(d[edges[j].v]!=1e9)
				if(d[edges[j].to]+eps>=d[edges[j].v]+edges[j].cost)
				{
					d[edges[j].to]=d[edges[j].v]+edges[j].cost;
					p[edges[j].to]=edges[j].v;
					v=edges[j].to;
				}
	}
	vector <int> zero_cycle;
	for(int current=v; ; current=p[current])
	{
		zero_cycle.push_back(current);
		if(current==v&&zero_cycle.size()>1)
			break;
	}
	for(int i=zero_cycle.size()-1; i>=0; --i)
		cout<<zero_cycle[i]+1<<' ';
	return 0;
}
#include <iostream>
#include <vector>
using namespace std;
int main()
{
	int n;
	cin>>n;
	vector < vector <double> > exchange_rate(n);
	vector <double> dist(n);
	vector <int> parent(n, -1);
	for(int i=0; i<n; ++i)
	{
		exchange_rate[i].resize(n);
		for(int j=0; j<n; ++j)
			cin>>exchange_rate[i][j];
		if(exchange_rate[i][i]>1)
		{
			cout<<"YES\n"<<i+1<<' '<<i+1;
			return 0;
		}
	}
	dist[0]=1;
	for(int i=0; i<n; ++i)
		for(int j=0; j<n; ++j)
			for(int k=0; k<n; ++k)
				if(dist[k]<dist[j]*exchange_rate[k][j])
				{
					dist[k]=dist[j]*exchange_rate[k][j];
					parent[k]=j;
				}
	int v=-1;
	for(int i=0; i<n; ++i)
	{
		for(int j=0; j<n; ++j)
			if(dist[j]<dist[i]*exchange_rate[j][i])
			{
				parent[j]=i;
				v=j;
				break;
			}
		if(v!=-1)
			break;
	}
	if(v==-1)
	{
		cout<<"NO";
		return 0;
	}
	cout<<"YES\n";
	vector <int> cycle;
	for(int current=v; ; current=parent[current])
	{
		cycle.push_back(current);
		if(current==v&&cycle.size()>1)
			break;
	}
	for(int i=cycle.size()-1; i>=0; --i)
		cout<<cycle[i]+1<<' ';
	return 0;
}
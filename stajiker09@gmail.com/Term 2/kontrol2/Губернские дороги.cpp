#include <iostream>
#include <vector>
using namespace std;
int main()
{
	int n, k=0;
	cin>>n;
	vector < vector < pair<int, int> > > g(2*n);
	for(int i=0; i<n; ++i)
	{
		int a, b, d;
		k=max(k, max(a, b));
		cin>>a>>b>>d;
		g[a].push_back(make_pair(b, d));
		g[b].push_back(make_pair(a, d));
	}
	vector <int> d(k+1, numeric_limits<int>::max()), p(k+1);
	int s=0;
	d[s]=0;
	p[s]=-1;
	vector <bool> used(k);
	for(int i=0; i<k; ++i)
	{
		int v=-1;
		for(int j=0; j<k; ++j)
			if (!used[j]&&(v==-1||d[j]<d[v]))
				v=j;
		if(d[v]==numeric_limits<int>::max())
			break;
		used[v]=true;
		for (int j=0; j<g[v].size(); ++j)
		{
			int to=g[v][j].first, len=g[v][j].second;
			if (d[v]+len<d[to])
			{
				d[to]=d[v]+len;
				p[to]=v;
			}
		}
	}
	for(int i=0; i<k+1; ++i)
	{
		cout<<d[i];
		vector <int> path;
		int j=i;
		while(p[j]!=-1)
		{
			path.push_back(j);
			j=p[j];
		}
		path.push_back(s);
		for(int j=path.size()-1; j>=0; --j)
			cout<<' '<<path[j];
		cout<<endl;
	}
	return 0;
}
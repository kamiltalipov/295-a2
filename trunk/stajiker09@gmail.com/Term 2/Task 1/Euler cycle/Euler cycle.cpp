#include <iostream>
#include <vector>
using namespace std;
void FindEulerCycle(int v, vector < vector <int> > &g, vector <int> &index, vector <int> &EulerPath)
{
	if(index[v]<g[v].size())
	{
		++index[v];
		FindEulerCycle(g[v][index[v]-1], g, index, EulerPath);
	}
	EulerPath.push_back(v);
}
int main()
{
	int n, m;
	cin>>n>>m;
	vector < vector <int> > g(n);
	vector <int> tin(n), tout(n), EulerCycle, index(n);
	for(int i=0; i<m; ++i)
	{
		int a, b;
		cin>>a>>b;
		g[a-1].push_back(b-1);
		++tin[b-1];
		++tout[a-1];
	}
	for(int i=0; i<n; ++i)
		if(tin[i]!=tout[i])
		{
			printf("Euler cycle does not exist");
			return 0;
		}
	FindEulerCycle(0, g, index, EulerCycle);
	for(int i=EulerCycle.size()-1; i>=0; --i)
		printf("%d ", EulerCycle[i]+1);
	return 0;
}
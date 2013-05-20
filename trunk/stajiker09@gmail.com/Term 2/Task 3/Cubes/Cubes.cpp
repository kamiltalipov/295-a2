#include <iostream>
#include <vector>
#include <string>
using namespace std;
bool try_kuhn(int v, vector <bool> &used, vector < vector <int> > &g, vector <int> &mt)
{
	if(used[v])
		return false;
	used[v]=true;
	for(int i=0; i<g[v].size(); ++i)
	{
		int to=g[v][i];
		if(mt[to]==-1||try_kuhn(mt[to], used, g, mt))
		{
			mt[to]=v;
			return true;
		}
	}
	return false;
}
int main()
{
	string s, cube;
	vector <int> symbols[256];
	cin>>s;
	int n, len=s.length();
	for(int i=0; i<len; ++i)
		symbols[s[i]].push_back(i);
	cin>>n;
	vector < vector <int> > g(n);
	for(int i=0; i<n; ++i)
	{
		cin>>cube;
		for(int j=0; j<cube.length(); ++j)
			for(int k=0; k<symbols[cube[j]].size(); ++k)
				g[i].push_back(symbols[cube[j]][k]);
	}
	vector <int> mt;
	vector <bool> used;
	mt.assign(len, -1);
	for(int i=0; i<n; ++i)
	{
		used.assign(n, false);
		try_kuhn(i, used, g, mt);
	}
	for(int i=0; i<len; ++i)
		if(mt[i]==-1)
		{
			cout<<"Impossible";
			return 0;
		}
	for(int i=0; i<len; ++i)
		cout<<mt[i]+1<<' '<<s[i]<<endl;
	return 0;
}
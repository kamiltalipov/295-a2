#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector< vector < int > > gr, rgr;
vector < int > out;
vector < bool > marks;

void dfs1(int v)
{
	marks[v] = true;
	for (int i = 0; i < gr[v].size(); ++i)
		if ( !marks[ gr[v][i] ] )
			dfs1(gr[v][i]);
	out.push_back(v);
}

void dfs2(int v)
{
	marks[v] = true;
	out.push_back(v);
	for (int i = 0; i < rgr[v].size(); ++i)
		if ( !marks[ rgr[v][i] ] )
			dfs2(rgr[v][i]);
}

int main()
{
	int n, m;
	cin >> n >> m;
	gr.resize(n), rgr.resize(n), marks.resize(n);
	for (int i = 0,a, b; i < m; ++i)
	{
		cin >> a >> b;
		gr[ a - 1 ].push_back( b - 1 );
		rgr[ b - 1 ].push_back( a - 1 );
	}
	for (int i = 0; i < n; ++i)
		if ( !marks[i] )
			dfs1(i);
	vector < int > order(out.rbegin(), out.rend());
	fill(marks.begin(), marks.end(), false);
	out.clear();
	out.reserve(n);
	for (int i = 0; i < n; ++i)
		if ( marks[order[i]] )
		{
			dfs2(order[i]);
			for (int j = 0; j < out.size(); ++j)
				cout << out[j] << " ";
			cout << endl;
			out.clear();
		}
	return 0;
}
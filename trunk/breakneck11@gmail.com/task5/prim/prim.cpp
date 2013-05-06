#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

typedef pair < double, double > dpoint;

inline double cost(const point& a, const dpoint& b)
{ return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)); }

void dfs(const vector < vector < int > >& gr,
	const int v, vector < int >& res, const int p = -1)
{
	res.push_back(v);
	for (int i = 0; i < gr[v].size(); ++i)
		if (gr[v][i] != p)
			dfs(gr, gr[v][i], v);
}
int main()
{
	vector < dpoint > gr;
	int n;
	cin >> n;
	gr.resize(n);
	for (int i = 0; i < n; ++i)
		cin >> gr[i].first >> gr[i].second;
	vector < double > ds(n, 2e9);
	ds[0] = 0;
	vector < int > ps(n, -1);
	vector < bool > marked;
	vector < pair < int, int > > edges;
	for (int i = 0; i < n - 1; ++i)
	{
		int cv = -1;
		for (int j = 0; j < n; ++j)
			if (!marked[j] && (cv == -1 || ds[cv] > ds[j]))
				cv = j;
		marked[cv] = true;
		if (ps[cv] != -1)
			edges.push_back( make_pair(ps[cv], cv) );
		for (int j = 0; j < n; ++j)
			if (!marked[j] && ds[j] > cost(gr[j], gr[cv]))
			{
				ds[j] = cost(gr[j], gr[cv]);
				ps[j] = cv;
			}
	}
	vector < vector < int > > mgr(gr.size());
	for (int i = 0; i < edges.size(); ++i)
	{
		mgr[ edges[i].first ].push_back( edges[i].second );
		mgr[ edges[i].second ].push_back( edges[i].first );
	}
	vector < int > res;
	int mv = -1;
	double mc = -1.;
	for (int i = 0; i < n; ++i)
	{
		res.clear();
		dfs(mgr, i, res);
		double cc = cost(gr[0], gr[res.size() - 1]);
		for (int j = 0; j < res.size() - 1; ++j)
			cc += cost(gr[j], gr[j + 1]);
		if (mc > cc || mc < 0)
		{
			mc = cc;
			mv = j;
		}
	}
	dfs(mgr, mv, res);
	cout << mc << endl;
	for (int i = 0; i < res.size(); ++i)
		cout << res[i] + 1 << " ";
	return 0;
}

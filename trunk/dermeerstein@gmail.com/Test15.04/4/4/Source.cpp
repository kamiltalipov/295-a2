#include <iostream>
#include <vector>
#include <set>

using namespace std;

const int INF = 10e+9;

int main()
{
	vector<vector<pair<int, int>> > graph;
	vector<int> dist, p;
	vector<bool> vis;
	int n, m, a, b, w;
	cin >> n >> m;
	graph.resize(n);
	dist.resize(n, INF);
	p.resize(n);
	vis.resize(n, 0);
	dist[0] = 0;
	for (int i = 0; i < m; ++i)
	{
		cin >> a >> b >> w;
		graph[a].push_back(make_pair(b, w));
		graph[b].push_back(make_pair(a, w));
	}
	while (true)
	{
		int min_ind = -1;
		for (int i = 0; i < n; ++i)
		{
			if ((min_ind == - 1 || dist[i] < dist[min_ind]) && !vis[i])
			{
				min_ind = i;
			}
		}
		if (min_ind == -1)
			break;
		for (int i = 0; i < graph[min_ind].size(); ++i)
		{
			if (graph[min_ind][i].second < dist[graph[min_ind][i].first] && !vis[graph[min_ind][i].first])
			{
				dist[graph[min_ind][i].first] = graph[min_ind][i].second;
				p[graph[min_ind][i].first] = min_ind;
			}
		}
		vis[min_ind] = 1;
	}
	set<pair<int, int> > ans;
	int v;
	for (int i = 1; i < n; ++i)
	{
		v = i;
		while (v != 0)
		{
			ans.insert(make_pair(min(p[v], v), max(p[v], v)));
			v = p[v];
		}
	}
	for (set<pair<int, int> >::iterator it = ans.begin(); it != ans.end(); ++it)
	{
		cout << (*it).first << " " << (*it).second << endl;
	}
	return 0;
}
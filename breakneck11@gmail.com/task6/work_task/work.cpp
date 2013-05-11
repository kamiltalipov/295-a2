#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

int n, m;

struct edge
{
	int from, to, cost;
	edge(int from, int to, int cost) : from(from), to(to), cost(cost) {}
};
vector < list < edge > > gr;
vector < list < edge >::iterator > prev;
vector < int > pots;
inline int cost(const edge& e) { return e.cost + pots[e.from] - pots[e.to]; }
inline bool used(const edge& e) { return e.cost > 0 ; }

inline void re_Dejkstra()
{
	vector < int > ds(n + m);
	vector < bool > marked(n + m), reachable(n + m);
	for (int i = 0; i < n + m; ++i)
		prev[i] = gr[i].end();
	for (int i = 0; i < n + m; ++i)
		if (find_if(gr[i].begin(), gr[i].end(), used) == gr[i].end())
			reachable[i] = true;
	while (true)
	{
		int mv = -1;
		for (int i = 0; i < n + m; ++i)
			if (reachable[i] && !marked[i] && (mv == -1 || ds[mv] > ds[i]))
				mv = i;
		if (mv == -1)
			break;
		marked[mv] = true;
		list < edge >::iterator it = gr[mv].begin();
		for (; it != gr[mv].end(); ++it)
			if (ds[it->to] > ds[mv] + cost(*it))
			{
				reachable[it->to] = true;
				prev[it->to] = it;
				ds[it->to] = ds[mv] + cost(*it);
			}
	}
	pots.assign(ds.begin(), ds.end());

}

int main()
{
	int k;
	cin >> n >> m >> k;
	bool swaped = n > m;
	if (swaped)
		swap(n, m);
	gr.resize(n + m);
	vector < bool > right_touched(m);
	for (int i = 0; i < k; ++i)
	{
		int from, to, cost;
		cin >> from >> to >> cost;
		to += n;
		if (swaped)
			swap(from, to);
		gr[from - 1].push_back(edge(from - 1, to - 1, cost));
		if (!right_touched[to - 1])
			pots[to - 1] = cost;
		else
			pots[to - 1] = min(pots[to - 1], cost);
	}
	right_touched.clear();
	while (true)
	{
		re_Dejkstra();
		int mv = -1;
		for (int i = n; i < n + m; ++i)
			if (prev[i] != gr[i].end() && (mv == -1 || pots[i] < pots[mv]))
				mv = i;
		if (mv == -1)
			break;
		list < edge >::iterator it = prev[mv];
		while (it->from != it->to)
		{
			edge ne = *it;
			swap(ne.from, ne.to);
			ne.cost = - ne.cost;
			gr[it->to].push_back(ne);
			gr[it->from].erase(it);
			it = prev[ ne.to ];
		}
	}
	//Output
	return 0;
}

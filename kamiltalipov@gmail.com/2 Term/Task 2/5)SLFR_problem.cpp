#include <iostream>
using std :: cin;
using std :: cout;
#include <vector>
using std :: vector;
#include <map>
using std :: map;
#include <utility>
using std :: pair;
using std :: make_pair;
#include <algorithm>
using std :: sort;

#include "DSU.h"

enum Color
{
    WHITE,
    GRAY,
    BLACK
};

typedef pair<size_t, size_t> Edge;
typedef pair<size_t, Edge> CostEdge;

const size_t INF = 1000000000;
const size_t NOT_SET = -1;

void dfs (const vector<vector<pair<size_t, size_t> > >& g, const size_t v,
          const vector<vector<size_t> >& query,
          map<pair<size_t, size_t>, size_t>& ans,
          vector<Color>& colors,
          DSU& dsu)
{
    if (colors[v] != WHITE)
        return;
    colors[v] = GRAY;

    for (size_t i = 0; i < g[v].size (); ++i)
    {
        if (colors[g[v][i].first] == WHITE)
        {
            dfs (g, g[v][i].first, query, ans, colors, dsu);
            dsu.union_sets (v, g[v][i].first);
        }
    }

    colors[v] = BLACK;

    for (size_t i = 0; i < query[v].size (); ++i)
    {
        if (colors[query[v][i]] == BLACK && ans.find (make_pair (query[v][i], v)) == ans.end ())
            ans[make_pair (v, query[v][i])] = dsu.get_ancestor (query[v][i]);
    }
}

void getLCA (const vector<vector<pair<size_t, size_t> > >& g, const size_t v,
             const vector<vector<size_t> >& query,
             map<pair<size_t, size_t>, size_t>& ans)
{
    vector<Color> colors (g.size (), WHITE);
    DSU dsu (g.size ());
    dfs (g, v, query, ans, colors, dsu);
}

void dfs (const vector<vector<pair<size_t, size_t> > >& g, const size_t v,
          vector<size_t>& len, vector<size_t>& prev, vector<bool>& used)
{
    if (used[v])
        return;
    used[v] = true;

    for (size_t i = 0; i < g[v].size (); ++i)
        if (!used[g[v][i].first])
        {
            len[g[v][i].first] = len[v] + g[v][i].second;
            prev[g[v][i].first] = v;
            dfs (g, v, len, prev, used);
        }
}

void getLen (const vector<vector<pair<size_t, size_t> > >& spt, const size_t center_v,
             vector<size_t>& len, vector<size_t>& prev)
{
    len[center_v] = 0;
    vector<bool> used (spt.size (), false);
    dfs (spt, center_v, len, prev, used);
}

class my_comp
{
public:
    my_comp (vector<size_t>& _len)
        :
        len (_len)
    {
    }

    bool operator () (const CostEdge& e1, const CostEdge& e2) const
    {
        return getCost (e1) < getCost (e2);
    }

private:
    vector<size_t>& len;

    size_t getCost (const CostEdge& e) const
    {
        return len[e.second.first] + e.first + len[e.second.second];
    }
};

void setEscapePath (vector<size_t>& escape_path, 
                    const size_t cur_v, const size_t end_v, const size_t set_v,
                    const vector<size_t>& prev)
{
    if (cur_v == end_v)
        return;

    if (escape_path[cur_v] != NOT_SET)
    {
        escape_path[cur_v] = set_v;
        setEscapePath (escape_path, prev[cur_v], end_v, cur_v, prev);
    }
}

void findEspacePath (const vector<vector<pair<size_t, size_t> > >& spt,
                     vector<CostEdge>& g,
                     const size_t center_v,
                     vector<size_t>& prev,
                     vector<size_t>& escape_path)
{
    vector<size_t> len (spt.size (), INF);
    getLen (spt, center_v, len, prev);
    sort (g.begin (), g.end (), my_comp (len));
    
    vector<vector<size_t> > query (spt.size (), vector<size_t> (spt.size ()));
    for (size_t i = 0; i < spt.size (); ++i)
        for (size_t j = 0; j < spt.size (); ++j)
            query[i][j] = j;
    map<pair<size_t, size_t>, size_t> lca;
    getLCA (spt, center_v, query, lca);

    for (size_t i = 0; i < g.size (); ++i)
    {
        setEscapePath (escape_path, g[i].second.first, lca[g[i].second], g[i].second.second, prev);
        setEscapePath (escape_path, g[i].second.second, lca[g[i].second], g[i].second.first, prev);
    }
}

int main ()
{
	size_t all_v = 0;
	cin >> all_v;
	vector<vector<pair<size_t, size_t> > > spt (all_v);
	for (size_t i = 0; i < all_v - 1; ++i)
	{
		size_t v, u, cost;
		cin >> v >> u >> cost; 
		spt[v].push_back (make_pair (u, cost));
		spt[u].push_back (make_pair (v, cost));
	}

	size_t all_non_mst_e = 0;
	cin >> all_non_mst_e;
	vector<CostEdge> g (all_non_mst_e);
	for (size_t i = 0; i < all_non_mst_e; ++i)
		cin >> g[i].second.first >> g[i].second.first >> g[i].first;

	size_t center_v = 0;
	cin >> center_v;
	
    vector<size_t> prev (all_v, -1), escape_path (all_v, -1);
    findEspacePath (spt, g, center_v, prev, escape_path);

	return 0;
}
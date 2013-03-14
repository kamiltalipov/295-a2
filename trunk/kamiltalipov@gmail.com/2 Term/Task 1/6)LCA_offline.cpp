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
//#include <cstdio>

#include "DSU.h"

enum Color
{
    WHITE,
    GRAY,
    BLACK
};

void dfs (const vector<vector<size_t> >& g, const int v,
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
        if (colors[g[v][i]] == WHITE)
        {
            dfs (g, g[v][i], query, ans, colors, dsu);
            dsu.union_sets (v, g[v][i]);
        }
    }

    colors[v] = BLACK;

    for (size_t i = 0; i < query[v].size (); ++i)
    {
        if (colors[query[v][i]] == BLACK && ans.find (make_pair (query[v][i], v)) == ans.end ())
			ans[make_pair (v, query[v][i])] = dsu.get_ancestor (query[v][i]);
    }
}

void getLCA (const vector<vector<size_t> >& g, const vector<vector<size_t> >& query,
             map<pair<size_t, size_t>, size_t>& ans)
{
    vector<Color> colors (g.size (), WHITE);
    DSU dsu (g.size ());
    dfs (g, 0, query, ans, colors, dsu);
}

int main ()
{
    //freopen ("input.txt", "r", stdin);

    size_t all_v = 0;
    cin >> all_v;
    vector<vector<size_t> > g (all_v, vector<size_t> ());
    for (size_t v = 0; v < all_v; ++v)
    {
        size_t v_v = 0;
        cin >> v_v;
        g[v].resize (v_v);
        for (size_t i = 0; i < v_v; ++i)
            cin >> g[v][i];
    }

	size_t all_query = 0;
	cin >> all_query;
    vector<vector<size_t> > query (all_v);
    for (size_t i = 0; i < all_query; ++i)
    {
        size_t v1, v2;
		cin >> v1 >> v2;
		query[v1].push_back (v2);
		if (v1 != v2)
			query[v2].push_back (v1);
	}

    map<pair<size_t, size_t>, size_t> ans;
    getLCA (g, query, ans);
    for (size_t v = 0; v < all_v; ++v)
    {
       for (size_t w = 0; w < query[v].size (); ++w)
       {
           map<pair<size_t, size_t>, size_t> :: const_iterator it = ans.find (make_pair (v, query[v][w]));
           cout << "For pair vertex: " << v << " and " << query[v][w] << " - LCA is ";
		   if (it != ans.end ())
			   cout << it->second << '\n';
		   else if ((it = ans.find (make_pair (query[v][w], v))) != ans.end ())
			   cout << it->second << '\n';
		   else
			   cout << "NONE\n";
       }
    }

    return 0;
}

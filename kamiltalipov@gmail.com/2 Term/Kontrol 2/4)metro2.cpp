#include <iostream>
using std :: cin;
using std :: cout;
#include <vector>
using std :: vector;
#include <utility>
using std :: pair;
using std :: make_pair;
#include <stack>
using std :: stack;
#include <algorithm>
using std :: sort;
#include <queue>
using std :: priority_queue;

#include "DSU.h"

typedef pair<size_t, size_t> Edge;
typedef pair<int, Edge> CostEdge;

int findMST (vector<CostEdge>& g, size_t all_v, vector<Edge>& mst)
{
    DSU dsu (all_v);
    sort (g.begin (), g.end ());
    int total_cost = 0;
    for (size_t i = 0; i < g.size (); ++i)
    {
        size_t v = g[i].second.first,
                u = g[i].second.second;
        if (dsu.find_set (v) != dsu.find_set (u))
        {
            mst.push_back (g[i].second);
            total_cost += g[i].first;
            dsu.union_sets (v, u);
        }
    }

    return total_cost;
}

int main ()
{
    size_t all_v, all_e;
    cin >> all_v >> all_e;
    vector<CostEdge> g (all_e);
    for (size_t i = 0; i < all_e; ++i)
        cin >> g[i].second.first >> g[i].second.second >> g[i].first;

    vector<Edge> mst (all_v);
    cout << "Total cost: " << findMST (g, all_v, mst) << '\n';
    cout << "All edges: " << mst.size () << '\n';
    cout << "Edges:\n";
    for (size_t i = 0; i < mst.size; ++i)
        cout << mst[i].first << ' ' << mst[i].second << '\n';

    return 0;
}

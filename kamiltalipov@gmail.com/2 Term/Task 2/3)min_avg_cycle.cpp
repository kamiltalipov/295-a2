#include <iostream>
using std :: cin;
using std :: cout;
#include <vector>
using std :: vector;
#include <algorithm>
using std :: max;
#include <cassert>

bool haveCycle (const vector<vector<int> >& g, int edge_diff, vector<size_t>& cycle)
{
    const size_t start_v = 0;
    const int INF = 1000000000;
    const int NOT_SET = -1;

    cycle.clear ();

    vector<int> distance (g.size (), INF);
    vector<size_t> prev (g.size (), NOT_SET);
    distance[start_v] = 0;
	for (size_t i = 0; i < g.size (); ++i)
    {
        for (size_t v = 0; v < g.size (); ++v)
            for (size_t u = 0; u < g.size (); ++u)
            {
                if (distance[u] > distance[v] + g[v][u] - edge_diff)
                {
                    distance[u] = distance[v] + g[v][u] - edge_diff;
                    prev[u] = v;
                }
            }
    }

    cout << "Distances\n";
    for (size_t i = 0 ; i < distance.size (); ++i)
        cout << distance[i] << ' ';
    cout << '\n';

    vector<bool> in_cycle (g.size (), false);
    for (size_t i  = 0; i < g.size (); ++i)
        if (distance[i] < 0)
        {
            cycle.push_back (i);
            in_cycle[i] = true;
            size_t cur_v = prev[i];
            while (cur_v != i && !in_cycle[cur_v])
            {
                cycle.push_back (cur_v);
                in_cycle[cur_v] = true;
                cur_v = prev[cur_v];
            }

            break;
        }

    return !cycle.empty ();
}

void findMinAVGCycle (const vector<vector<int> >& g, vector<size_t>& res)
{
    int max_edge = g[0][0];
    for (size_t v = 0; v < g.size (); ++v)
        for (size_t u = 0; u < g.size (); ++u)
            max_edge = max (max_edge, g[v][u]);

    int left = 0, right = max_edge;
    while (right - left > 0)
    {
        size_t mid = (left + right) / 2;
        if (!haveCycle (g, mid, res))
            left = mid + 1;
        else
            right = mid;
    }
    if (!haveCycle (g, left, res))
        res.clear ();
}

int main ()
{
    size_t all_v = 0;
    cin >> all_v;
    vector<vector<int> > g (all_v, vector<int> (all_v, 0));
    for (size_t v = 0; v < all_v; ++v)
    {
        for (size_t u = 0; u < all_v; ++u)
            cin >> g[v][u];
    }

    vector<size_t> cycle;
    findMinAVGCycle (g, cycle);
    if (cycle.empty ())
    {
        cout << "There isn't any cycle!\n";
    }
    else
    {
        cout << "Cycle len = " << cycle.size () << '\n';
        for (size_t i = 0; i < cycle.size (); ++i)
            cout << cycle[i] << ' ';
    }

    return 0;
}

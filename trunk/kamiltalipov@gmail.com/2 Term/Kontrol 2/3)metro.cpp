#include <iostream>
using std :: cin;
using std :: cout;
#include <vector>
using std :: vector;
#include <utility>
using std :: pair;
using std :: make_pair;
#include <queue>
using std :: priority_queue;
#include <algorithm>
using std :: reverse;

const int INF = 2000000000;

void getDistance (const vector<vector<pair <size_t, size_t> > >& g,
                 int start_v, int finish_v, vector<size_t>& res)
{
    vector<int> distance (g.size (), INF);
    distance[start_v] = 0;
    priority_queue<pair<int, int> > q;
    q.push (make_pair (0, start_v));
    vector<size_t> path (g.size ());
    while (!q.empty ())
    {
        int v = q.top ().second;
        int cur_d = -q.top ().first;
        q.pop ();
        if (cur_d > distance[v])
            continue;

        for (size_t i = 0; i < g[v].size (); ++i)
        {
            size_t to = g[v][i].first,
                    cost = g[v][i].second;
            if (distance[v] + cost < distance[to])
            {
                distance[to] = distance[v] + cost;
                path[to] = v;
                q.push (make_pair (-distance[to], to));
            }
        }
    }

    if (distance[finish_v] != INF)
    {
        int cur_v = finish_v;
        do
        {
            res.push_back (cur_v);
            cur_v = path[cur_v];
        }
        while (cur_v != start_v);
        reverse (res.begin (), res.end ());
    }
}

int main ()
{
    int all_lines, all_v = 0;
    cin >> all_lines;
    for (int i = 0; i < all_lines; ++i)
    {
        int stations;
        cin >> stations;
        all_v += stations;
    }

    vector<vector<pair <size_t, size_t> > > g (all_v);
    int all_transfer;
    cin >> all_transfer;
    for (int i = 0; i < all_transfer; ++i)
    {
        size_t from, to, time;
        cin >> from >> to >> time;
        g[from].push_back (make_pair (to, time));
        g[to].push_back (make_pair (from, time));
    }
    int start_v, finish_v;
    cin >> start_v >> finish_v;

    vector<size_t> path;
    getDistance (g, start_v, finish_v, path);
    cout << "Path:\n";
    if (path.empty ())
        cout << "No path\n";
    else
    {
        for (size_t i = 0; i < path.size ();++i)
            cout << path[i] << ' ';
    }

    return 0;
}

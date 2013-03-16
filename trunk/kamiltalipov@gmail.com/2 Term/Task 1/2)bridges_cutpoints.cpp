#include <iostream>
using std :: cin;
using std :: cout;
using std :: ostream;
#include <vector>
using std :: vector;
#include <utility>
using std :: pair;
using std :: make_pair;
#include <stack>
using std :: stack;
#include <string>
using std :: string;
#include <algorithm>
using std :: min;

void dfs (const vector<vector<size_t> >& g, const size_t v,
          vector<int>& tin, vector<int>& fup, vector<bool>& used,
          vector<int>& enter, vector<int>& ret,
          int& time_glob, int& time_component,
          stack<size_t> st_vertex, stack<pair<size_t, size_t> >& st_edge,
          vector<size_t>& cut_points, vector<pair<size_t, size_t> >& bridges,
          vector<vector<pair<size_t, size_t> > >& vertex_component, vector<vector<size_t> >& edge_component,
          size_t parent = -1)
{
    if (used[v])
        return;
    used[v] = true;
    st_vertex.push (v);
    tin[v] = fup[v] = time_glob;
    ++time_glob;
    enter[v] = ret[v] = time_component;
    ++time_component;

    int all_children = 0;
    for (size_t w = 0; w < g[v].size (); ++w)
    {
        if (g[v][w] == parent)
            continue;
        if (used[g[v][w]])
        {
            fup[v] = min (fup[v], tin[g[v][w]]);
            ret[v] = min (ret[v], enter[g[v][w]]);
            if (enter[g[v][w]] < enter [v])
                st_edge.push (make_pair (v, g[v][w]));
        }
        else
        {
            st_edge.push (make_pair (v, g[v][w]));
            dfs (g, g[v][w], tin, fup, used, enter, ret, time_glob, time_component, st_vertex, st_edge,
                 cut_points, bridges, vertex_component, edge_component, v);
            fup[v] = min (fup[v], fup[g[v][w]]);
            ret[v] = min (ret[v], ret[g[v][w]]);
            if (fup[g[v][w]] > tin[v])
                bridges.push_back (make_pair (v, g[v][w]));
            if (fup[g[v][w]] >= tin[v] && parent != -1)
                cut_points.push_back (v);
            if (ret[g[v][w]] >= enter[v])
            {
                vertex_component.push_back (vector<pair<size_t, size_t> > ());

                pair<size_t, size_t> e, end_e = make_pair (v, g[v][w]);
                do
                {
                    e = st_edge.top ();
                    st_edge.pop ();
                    vertex_component[vertex_component.size () - 1].push_back (e);
                }
                while (e != end_e);
            }
            if (fup[g[v][w]] > tin[v])
            {
                edge_component.push_back (vector<size_t> ());

                size_t x;
                do
                {
                    x = st_vertex.top ();
                    st_vertex.pop ();
                    edge_component[edge_component.size () - 1].push_back (x);

                } while (x != g[v][w]);
            }
            ++all_children;
        }
    }

    if (parent == -1 && all_children > 1)
        cut_points.push_back (v);
}

void find (const vector<vector<size_t> >& g,
           vector<size_t>& cut_points, vector<pair<size_t, size_t> >& bridges,
           vector<vector<pair<size_t, size_t> > >& vertex_component, vector<vector<size_t > >& edge_component)
{
    int time_glob = 0, time_component;
    vector<int> tin (g.size ()),
                fup (g.size ()),
                enter (g.size ()),
                ret (g.size ());
    vector<bool> used (g.size (), false);
    stack<size_t> st_vertex;
    stack<pair<size_t, size_t> > st_edge;
    for (size_t v = 0; v < g.size (); ++v)
        if (!used[v])
        {
            time_component = 0;
            dfs (g, v, tin, fup, used, enter, ret, time_glob, time_component, st_vertex, st_edge,
                 cut_points, bridges, vertex_component, edge_component);
        }
}

template <typename T1, typename T2>
ostream& operator << (ostream& output, const pair<T1, T2>& p)
{
    output << p.first << ' ' << p.second;
    return output;
}

template <typename T>
void printVector (const vector<T>& v, const string& sizeTitleBegin, const string& sizeTitleEnd)
{
    cout << sizeTitleBegin << v.size () << sizeTitleEnd;
    for (typename vector<T> :: const_iterator i = v.begin (); i != v.end (); ++i)
        cout << *i;
}

template <typename T>
void print2Vector (const vector<vector<T> >& v, const string& sizeTitleBegin, const string& sizeTitleEnd,
                   const string& vectorTextBegin, const string& vectorTextEnd)
{
    cout << sizeTitleBegin << v.size () << sizeTitleEnd;
    for (typename vector<vector<T> > :: const_iterator i = v.begin (); i != v.end (); ++i)
    {
        cout << vectorTextBegin << (i - v.begin ()) + 1 << vectorTextEnd;
        for (typename vector<T> :: const_iterator j = i->begin (); j != i->end (); ++j)
        {
            cout << *j << '\n';
        }
        cout << '\n';
    }
}

int main ()
{
    int all_v = 0;
    cin >> all_v;
    vector<vector<size_t> > g (all_v, vector<size_t> ());
    for (int v = 0; v < all_v; ++v)
    {
        size_t v_v = 0;
        cin >> v_v;
        g[v].resize (v_v);
        for (size_t w = 0; w < v_v; ++w)
            cin >> g[v][w];
    }

    vector<size_t> cut_points;
    vector<pair<size_t, size_t> > bridges;
    vector<vector<pair<size_t, size_t> > > vertex_component;
    vector<vector<size_t > > edge_component;
    find (g, cut_points, bridges, vertex_component, edge_component);
    printVector (cut_points, "Cur points - all cutpoints = ", ":\n");
    printVector (bridges, "Bridges - all bridges = ", ":\n");
    print2Vector (vertex_component, "Vertex component - all components = ", ":\n",
                  "Vertex component #", ":\n");
    print2Vector (edge_component, "Edge component - all components = ", ":\n",
                  "Edge component #", ":\n");

    return 0;
}

#include <iostream>
using std :: cin;
using std :: cout;
#include <vector>
using std :: vector;
#include <stack>
using std :: stack;
#include <algorithm>
using std :: min;

void printComponents (const vector<vector<size_t> > c)
{
    cout << "All components = " << c.size () << '\n';
    for (size_t v = 0; v < c.size (); ++v)
    {
        cout << "Component #" << v + 1 << ":\n";
        for (size_t w = 0; w < c[v].size (); ++w)
            cout << c[v][w] << ' ';
        cout << '\n';
    }
}

void getOrder (const vector<vector<size_t> >& g, const int v,
               vector<bool>& used, vector<size_t>& order)
{
    used[v] = true;
    for (size_t w = 0; w < g[v].size (); ++w)
        if (!used[g[v][w]])
            getOrder (g, g[v][w], used, order);
    order.push_back (v);
}

void getComponent (const vector<vector<size_t> >& gt, const int v,
                   vector<bool>& used, vector<size_t>& component)
{
    used[v] = true;
    component.push_back (v);
    for (size_t w = 0; w < gt[v].size (); ++w)
        if (!used[gt[v][w]])
            getComponent (gt, gt[v][w], used, component);
}

void findAllComponents1 (const vector<vector<size_t> >& g,
                         const vector<vector<size_t> >& gt,
                         vector<vector<size_t> >& res)
{
    vector<size_t> order;
    vector<bool> used (g.size (), false);
    for (size_t v = 0; v < g.size (); ++v)
        if (!used[v])
            getOrder (g, v, used, order);

    used.assign (g.size (), false);
    for (size_t v = 0; v < g.size (); ++v)
    {
        size_t w = order[g.size () - 1 - v];
        if (!used[v])
        {
            res.push_back (vector<size_t> ());
            getComponent (gt, w, used, res[res.size () - 1]);
        }
    }
}

void strongConnect (const vector<vector<size_t> >& g, const size_t v,
                    stack<size_t>& st, vector<bool>& stContain,
                    vector<int>& tin, vector<int>& lowlink, int& time,
                    vector<vector<size_t> >& res)
{
    tin[v] = time;
    lowlink[v] = time;
    ++time;
    st.push (v);
    stContain[v] = true;

    for (size_t w = 0; w < g[v].size (); ++w)
    {
        if (tin[g[v][w]] < 0)
        {
            strongConnect (g, g[v][w], st, stContain, tin, lowlink, time, res);
            lowlink[v] = min (lowlink[v], lowlink[g[v][w]]);
        }
        else if (stContain[g[v][w]])
            lowlink[v] = min (lowlink[v], lowlink[g[v][w]]);
    }

    if (lowlink[v] == tin[v])
    {
        res.push_back (vector<size_t> ());

        size_t w;
        do
        {
            w = st.top ();
            st.pop ();
            stContain[w] = false;

            res[res.size () - 1].push_back (w);
        } while (w != v);
    }
}

void findAllComponents2 (const vector<vector<size_t> >& g,
                         vector<vector<size_t> >& res)
{
    stack<size_t> st;
    vector<bool> stContain (g.size (), false);
    vector<int> tin (g.size (), -1);
    vector<int> lowlink (g.size ());
    int time = 0;

    for (size_t v = 0; v < g.size (); ++v)
        if (tin[v] < 0)
            strongConnect (g, v, st, stContain, tin, lowlink, time, res);
}

int main ()
{
    size_t all_v = 0;
    cin >> all_v;
    vector<vector<size_t> > g (all_v, vector<size_t> ());
    vector<vector<size_t> > gt (all_v, vector<size_t> ());
    for (size_t v = 0; v < all_v; ++v)
    {
        size_t v_v = 0;
        cin >> v_v;
        for (size_t i = 0; i < v_v; ++i)
        {
            size_t cur_v;
            cin >> cur_v;
            g[v].push_back (cur_v);
            gt[cur_v].push_back (v);
        }
    }

    vector<vector<size_t> > components;
    findAllComponents1 (g, gt, components); // Kosaraju
    printComponents (components);
    components.clear ();
    findAllComponents2 (g, components); //Tarjan
    cout << "\n==========================\n";
    printComponents (components);

    return 0;
}

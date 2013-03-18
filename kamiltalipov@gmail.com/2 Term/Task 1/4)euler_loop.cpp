#include <iostream>
using std :: cin;
using std :: cout;
#include <vector>
using std :: vector;
#include <stack>
using std :: stack;
#include <algorithm>
using std :: min;

bool haveEulerLoop (const vector<vector<size_t> >& g)
{
    vector<size_t> deg (g.size ());
    for (size_t v = 0; v < g.size (); ++v)
    {
        deg[v] -= g[v].size ();
        for (size_t w = 0; w < g[v].size (); ++w)
            ++deg[g[v][w]];
    }

    for (size_t v = 0; v < g.size (); ++v)
        if (deg[v])
            return false;

    return true;
}

void findEulerLoop (const vector<vector<size_t> >& g, vector<size_t>& loop)
{
    loop.clear ();

    if (!haveEulerLoop (g))
        return;

    vector<size_t> lookedEdge (g.size (), 0);

    stack<size_t> st;
    size_t start_v = 0;
    while (g[start_v].empty ())
        ++start_v;
    st.push (start_v);
    while (!st.empty ())
    {
        size_t v = st.top ();
        if (lookedEdge[v] == g[v].size ())
        {
            loop.push_back (v);
            st.pop ();
        }
        else
        {
            st.push (g[v][lookedEdge[v]]);
            ++lookedEdge[v];
        }
    }

    size_t all_edge = 0;
    for (size_t v = 0; v < g.size (); ++v)
        all_edge += g[v].size ();
    if (loop.size () - 1 != all_edge)
        loop.clear ();
}

int main ()
{
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

    vector<size_t> loop;
    findEulerLoop (g, loop);
    if (loop.empty ())
    {
        cout << "There is no Euler loop!\n";
    }
    else
    {
        for (size_t i = 0; i < loop.size (); ++i)
            cout << loop[i] << ' ';
    }

    return 0;
}

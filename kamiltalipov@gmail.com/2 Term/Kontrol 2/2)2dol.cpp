#include <iostream>
using std :: cin;
using std :: cout;
#include <vector>
using std :: vector;
#include <queue>
using std :: queue;


inline int notComponent (int comp)
{
    if (comp == 1)
        return 2;
    return 1;
}

bool bfs (const vector<vector<int> >& g,
          size_t start_v, vector<int>& component)
{
    if (component[start_v] != -1)
        return true;

    component[start_v] = 1;
    queue<size_t> q;
    q.push (start_v);
    while (!q.empty ())
    {
        size_t v = q.front ();
        q.pop ();
        for (size_t i = 0; i < g[v].size (); ++i)
            if (g[v][i])
            {
                if (component[i] == -1)
                {
                    q.push (i);
                    component[i] = notComponent (component[v]);
                }
                else if (component[i] != notComponent (component[v]))
                    return false;
            }
    }
    return true;
}

bool is_2dol (const vector<vector<int> >& g)
{
    vector<int> component (g.size (), -1);
    for (size_t i = 0; i < g.size (); ++i)
        if (component[i] == -1)
        {
            if (bfs (g, i, component) == false)
                return false;
        }

    return true;
}

int main ()
{
    size_t n;
    cin >> n;
    vector<vector<int> > g (n, vector<int> (n, 0));
    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < n; ++j)
            cin >> g[i][j];

    if (is_2dol (g))
        cout << "YES\n";
    else
        cout << "NO\n";

    return 0;
}

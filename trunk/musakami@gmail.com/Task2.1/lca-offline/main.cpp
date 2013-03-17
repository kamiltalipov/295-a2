#include <iostream>
#include <vector>

using namespace std;

class Dcu
{
    vector<int> anc;
    vector<int> size;
public:
    Dcu(int n)
    {
        anc.resize(n);
        size.resize(n);
        for (int i = 0; i < n; i++)
        {
            anc[i] = i;
            size[i] = 1;
        }

    }

    int root(int v)
    {
        if (anc[v] == v)
            return v;
        return anc[v] = root(anc[v]);
    }

    void join(int v, int u)
    {
        int rv = root(v);
        int ru = root(u);
        if (rv != ru)
        {
            if (size[rv] < size[ru])
                swap(rv, ru);
            anc[ru] = rv;
            size[rv] += size[ru];
        }
    }

    bool check(int v, int u)
    {
        return root(v) == root(u);
    }
};

void dfs(int v, vector<int> &color, vector<vector<int> > &query, vector<vector<int> > &graph, Dcu &dcu, vector<int> &join_point)
{
    color[v] = 1;
    for (int i = 0; i < graph[v].size(); i++)
    {
        int u = graph[v][i];
        if (color[u] == 0)
        {
            dfs(u, color, query, graph, dcu, join_point);
            dcu.join(v, u);
            join_point[dcu.root(v)] = v;
        }
    }

    for (int i = 0; i < query[v].size(); i++)
    {
        int u = query[v][i];
        if (color[u] == 2)
            cout << "(" << v << ", " << u << "): " << join_point[dcu.root(u)] << endl;
    }
    color[v] = 2;
}


int main()
{
    int n;
    cin >> n;
    vector<vector<int> > graph(n);
    for (int i = 0; i < n; i++)
    {
        int k;
        cin >> k;
        for (int j = 0; j < k; j++)
        {
            int to;
            cin >> to;
            graph[i].push_back(to);
        }
    }

    int m;
    cin >> m;
    vector<vector<int> > query(n);
    for (int i = 0; i < m; i++)
    {
        int k1, k2;
        cin >> k1 >> k2;
        query[k1].push_back(k2);
        query[k2].push_back(k1);
    }

    vector<int> color(n, 0);
    Dcu dcu(n);
    vector<int> join_point(n);
    dfs(0, color, query, graph, dcu, join_point);
    return 0;
}

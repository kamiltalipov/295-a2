#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge
{
    int from, to, weight;

    Edge(int from, int to, int weight):
        from(from), to(to), weight(weight) {}

    bool operator <(const Edge &other) const
    {
        return weight < other.weight;
    }
};

class dcu
{
    vector<int> anc;
    vector<int> size;
public:
    dcu(int n)
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

int main()
{
    int n, m;
	cin >> n >> m;
    vector<Edge> graph;
    for (int i = 0; i < m; i++)
    {
        int from, to, weight;
        cin >> from >> to >> weight;
        graph.push_back(Edge(from - 1, to - 1, weight));
    }
    vector<bool> use(m, false);
    dcu group(n);
    sort(graph.begin(), graph.end());
    for (int i = 0; i < graph.size(); i++)
    {
        if (!group.check(graph[i].from, graph[i].to))
        {
            group.join(graph[i].from, graph[i].to);
            use[i] = true;
        }
    }
    for (int i = 0; i < graph.size(); i++)
    {
        if (!use[i])
            cout << graph[i].from << " " << graph[i].to << endl;
    }
    return 0;
}

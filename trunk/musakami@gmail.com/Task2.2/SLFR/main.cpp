#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

/*
INPUT FORMAT
1st vertex considered root
--Short Paths Tree
n - Number of vericies
p2 d2 - ancestor for the 2nd vertex and distance from root
p3 d3 - ancestor for the 3rd vertex and distance from root
...(n - 1) line
m - number of non-tree edges
from to weight - (m lines)
k - number vertex with broken connection
*/

using namespace std;

struct Edge
{
    int from, to;
    long long weight;

    Edge(int from, int to, double weight):
        from(from), to(to), weight(weight) {};

};

struct Comparer
{
    vector<int> *dist;

    Comparer(vector<int> *dist)
    {
        this -> dist = dist;
    }

    bool operator ()(const Edge &a, const Edge &b)
    {
        return (*dist)[a.from] + a.weight + (*dist)[a.to] < (*dist)[b.from] + b.weight + (*dist)[b.to];
    }
};

class Dcu
{
    vector<int> anc;
    vector<int> size;
    vector<int> grouptoken;
public:
    Dcu(int n)
    {
        anc.resize(n);
        size.resize(n);
        grouptoken.resize(n);
        for (int i = 0; i < n; i++)
        {
            anc[i] = i;
            size[i] = 1;
            grouptoken[i] = i;
        }
    }

    virtual int choose(int a, int b)
    {
        return a;
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
            grouptoken[rv] = choose(grouptoken[rv], grouptoken[ru]);
        }
    }

    bool check(int v, int u)
    {
        return root(v) == root(u);
    }

    int GetToken(int a)
    {
        return grouptoken[root(a)];
    }
};

class GraphDcu:public Dcu
{
    vector<int> height;

public:

    GraphDcu(int n, vector< pair<int, int> > height):Dcu(n)
    {
        this -> height.resize(n);
        for (int i = 0; i < height.size(); i++)
        {
            this -> height[height[i].second] = height[i].first;
        }
    }

    virtual int choose(int a, int b)
    {
        if (height[a] < height[b])
            return a;
        else
            return b;
    }
};


void dfs(int v, vector<vector<Edge> > &graph, vector<int> &left, vector< pair<int, int> > &height, int h)
{
    height.push_back(make_pair(h, v));
    left[v] = height.size() - 1;
    for (int i = 0; i < graph[v].size(); i++)
    {
        int u = graph[v][i].to;
        dfs(u, graph, left, height, h + 1);
        height.push_back(make_pair(h, v));
    }
}

template<class T>
class SparseTable
{
    vector< vector<int> > table;
    vector<int> fastlog;
    int height;
    int length;
public:
    vector<T> data;

    SparseTable(vector<T> data)
    {
        height = 0;
        length = data.size();
        for (; 1 << height <= length; height++);
        for (int i = 0; i < length; i++)
            this -> data.push_back(data[i]);
        table.resize(height);
        for (int i = 0; i < height; i++)
            table[i].resize(length);
        for (int i = 0; i < length; i++)
            table[0][i] = i;
        for (int i = 1; i < height; i++)
            for (int j = 0; j + (1 << i) <= length; j++)
                table[i][j] = (data[table[i - 1][j]] < data[table[i - 1][j + (1 << (i - 1))]]) ? table[i - 1][j] : table[i - 1][j + (1 << (i - 1))];
        fastlog.resize(length + 1);
        int power = 0;
        for (int i = 0; i <= length; i++)
        {
            if ((1 << (power + 1)) <= i)
                power++;
            fastlog[i] = power;
        }
    }

    int min(int left, int right)
    {
        if (left > right)
            swap(left, right);
        int h = fastlog[right - left + 1];
        if (data[table[h][left]] < data[table[h][right + 1 - (1 << h)]])
            return table[h][left];
        return table[h][right + 1 - (1 << h)];
    }
};

int lca(int a, int b, SparseTable< pair<int, int> > &st, vector<int> &left)
{
    return st.data[st.min(left[a], left[b])].second;
}

int main()
{
    ifstream cin("input.txt");
    ofstream cout("output.txt");
    int n;
    cin >> n;
    vector<int> prev(n, - 1);
    vector<int> dist(n);
    vector<int> reroute(n, -1);
    vector< vector<Edge> > graph(n);
    for (int i = 1; i < n; i++)
    {
        int ancestor, weight;
        cin >> ancestor >>  weight;
        prev[i] = ancestor - 1;
        dist[i] = weight;
        graph[prev[i]].push_back(Edge(prev[i], i, weight));
    }
    dist[0] = 0;
    prev[0] = -1;
    int m;
    cin >> m;
    vector<Edge> edges;
    for (int i = 0; i < m; i++)
    {
        int from, to;
        long long weight;
        cin >> from >> to >> weight;
        edges.push_back(Edge(from - 1, to - 1, weight));
    }
    Comparer comparer(&dist);
    sort(edges.begin(), edges.end(), comparer);
    vector<int> left(n);
    vector< pair<int, int> > height;
    dfs(0, graph, left, height, 0);
    SparseTable<pair<int, int> > st(height);
    GraphDcu dcu(n, height);
    for (int i = 0; i < m; i++)
    {
        int u = edges[i].from;
        int v = edges[i].to;
        int p = lca(u, v, st, left);
        int current = u;
        while(height[left[current]].first > height[left[p]].first)
        {
            current = dcu.GetToken(current);
            if (height[left[current]].first > height[left[p]].first)
            {
                reroute[current] = i;
                dcu.join(current, prev[current]);
                current = prev[current];
            }
        }
        current = v;
        while(height[left[current]].first > height[left[p]].first)
        {
            current = dcu.GetToken(current);
            if (height[left[current]].first > height[left[p]].first)
            {
                reroute[current] = i;
                dcu.join(current, prev[current]);
                current = prev[current];
            }
        }
    }
    /*for (int i = 0; i < n; i++)
    {
        if (reroute[i] != -1)
            cout << i + 1 << ":" << edges[reroute[i]].from + 1 << " " << edges[reroute[i]].to + 1 << endl;
        else
            cout << i + 1 << ":No reroute" << endl;
    }*/
    int k;
    cin >> k;
    k--;
    if (reroute[k] == -1)
    {
        cout << "No reroute";
        return 0;
    }
    int u = edges[reroute[k]].from;
    int v = edges[reroute[k]].to;
    if (lca(v, k, st, left) == k)
        swap(u, v);
    int last = v;
    int current = u;
    while (last != k)
    {
        int anc = prev[current];
        prev[current] = last;
        last = current;
        current = anc;
    }
    for (int i = 0; i < n; i++)
        cout << i + 1 << ": " << prev[i] + 1 << endl;
    return 0;
}

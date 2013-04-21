#include <iostream>
#include <vector>
#include <cstdlib>
#include <math.h>

using namespace std;

#define INF (1e9)

struct Edge
{
    int from, to, weight;

    Edge(int from = 0, int to = 0, int weight = 0):
        from(from), to(to), weight(weight) {}

    bool operator <(const Edge &other)const
    {
        return weight < other.weight;
    }
};

class Graph
{
    vector< vector< Edge > > graph;
    bool nonoriented;

public:
    Graph(bool nonoriented = false)
    {
        this -> nonoriented = nonoriented;
    };

    Graph(int n, bool nonoriented = false)
    {
        graph.resize(n);
        this -> nonoriented = nonoriented;
    }

    int size()
    {
        return graph.size();
    }

    int AddVertex()
    {
        graph.push_back(vector<Edge>());
        return graph.size() - 1;
    }

    void AddEdge(int from, int to)
    {
        graph[from].push_back(Edge(from, to));
        if (nonoriented)
            graph[to].push_back(Edge(to, from));
    }

    const vector<Edge>& operator [](int i) const
    {
        return graph[i];
    }
};

struct Vector
{
    double x;
    double y;

    Vector (double x = 0, double y = 0):
        x(x), y(y) {}

    Vector operator -(const Vector &other) const
    {
        return Vector(x - other.x, y - other.y);
    }

    Vector operator +(const Vector &other) const
    {
        return Vector(x + other.x, y + other.y);
    }

    Vector operator -() const
    {
        return Vector(-x, -y);
    }

    double length()
    {
        return sqrt(x * x + y * y);
    }
};

class Route
{
    vector<int> route;
    double length;
    int last;
    Graph *graph;
    vector<Vector> *points;
    vector<bool> used;

    void dfs(int v)
    {
        used[v] = true;
        if (last != -1)
            length += ((*points)[last] - (*points)[v]).length();
        last = v;
        route.push_back(v);
        for (int i = 0; i < (*graph)[v].size(); i++)
        {
            int u = (*graph)[v][i].to;
            if (!used[u])
                dfs(u);
        }
    }
public:
    Route(Graph *graph, vector<Vector> *points)
    {
        this -> graph = graph;
        this -> points = points;
        length = 0;
        last = -1;
        used.resize(graph -> size(), false);
        dfs(0);
        route.push_back(0);
        length += ((*points)[last] - (*points)[0]).length();
    }

    void print()
    {
        cout << length << endl;
        for (int i = 0; i < route.size(); i++)
            cout << route[i] + 1 << " ";
    }
};

int main()
{
    int n = 100, m = 100;
    double s1 = 100;
    double s2 = 10;
    srand(42);
    Graph g;
    vector<Vector> points;
    for (int i = 0; i < n; i++)
    {
        double x;
        double y;
        double s;
        do
        {
            x = (rand() - RAND_MAX / 2) / (double)RAND_MAX;
            y = (rand() - RAND_MAX / 2) / (double)RAND_MAX;
            s = x * x + y * y;
        } while (s == 0 || s > 1);
        s = sqrt(-2 * log(s) / s);
        x = s1 * x * s;
        y = s1 * y * s;
        for (int j = 0; j < m; j++)
        {
            double x2;
            double y2;
            do
            {
                x2 = (rand() - RAND_MAX / 2) / (double)RAND_MAX;
                y2 = (rand() - RAND_MAX / 2) / (double)RAND_MAX;
                s = x2 * x2 + y2 * y2;
            } while (s == 0 || s > 1);
            s = sqrt(-2 * log(s) / s);
            x2 = x + s2 * x2 * s;
            y2 = y + s2 * y2 * s;
            points.push_back(Vector(x2, y2));
        }
    }
    Graph graph(points.size(), true);
    vector<double> dist(n, INF);
    vector<int> used(n, false);
    vector<int> prev(n, -1);
    dist[0] = 0;
    for (int i = 0; i < n; i++)
    {
        int next = -1;
        for (int i = 0; i < n; i++)
            if (!used[i] && (next == -1 || dist[next] > dist[i]))
                next = i;
        used[next] = true;
        for (int i = 0; i < n; i++)
            if (!used[i])
            {
                double l = (points[i] - points[next]).length();
                if (l < dist[i])
                {
                    dist[i] = l;
                    prev[i] = next;
                }
            }
        if (prev[next] != -1)
            graph.AddEdge(prev[next], next);
    }
    Route route(&graph, &points);
    route.print();
    return 0;
}

#include <iostream>
#include <vector>

using namespace std;

#define INF (1LL << 62) - 1
#define double long double

struct Edge
{
    int from, to;
    double weight;

    Edge(int from, int to, double weight):
        from(from), to(to), weight(weight) {};

};

int main()
{
    int n, m;
    cin >> n >> m;
    vector<Edge> graph;
    for (int i = 0; i < m; i++)
    {
        int from, to;
        double weight;
        cin >> from >> to >> weight;
        graph.push_back(Edge(from - 1, to - 1, weight));
    }
    double right = 10;
    double left = -right;
    int best = -1;
    double bestw = 1e9;
    vector<double> dist(n, 1e9);
    vector<int> prev(n, -1);
    vector<double> pedge(n, 0);
    vector<int> ans;
    while (right > left + 0.001)
    {
        double current = (left + right) / 2;
        dist.resize(n, 1e9);
        prev.resize(n, -1);
        pedge.resize(n, 0);
        dist[0] = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (dist[graph[j].to] > dist[graph[j].from] + graph[j].weight - current)
                {
                    dist[graph[j].to] = dist[graph[j].from] + graph[j].weight - current;
                    prev[graph[j].to] = graph[j].from;
                    pedge[graph[j].to] = graph[j].weight;
                }
        int start = -1;
        for (int j = 0; j < m; j++)
            if (dist[graph[j].to] > dist[graph[j].from] + graph[j].weight - current)
            {
                dist[graph[j].to] = dist[graph[j].from] + graph[j].weight - current;
                prev[graph[j].to] = graph[j].from;
                pedge[graph[j].to] = graph[j].weight;
                start = graph[j].to;
            }
        if (start == -1)
        {
            left = current;
        }
        else
        {
            right = current;
            for (int i = 0; i < n; i++)
                start = prev[start];
            best = start;
            bestw = pedge[start];
            ans.clear();
            ans.push_back(start);
            int v = prev[start];
            while (v != start)
            {
                ans.push_back(v);
                bestw += pedge[v];
                v = prev[v];
            }
        }
    }
    if (best == -1)
    {
        cout << "No loops";
    }
    else
    {
        cout << bestw / ans.size() << endl;
        for (int i = ans.size() - 1; i >= 0; i--)
            cout << ans[i] + 1 << " ";
        cout << best + 1;
    }
    return 0;
}

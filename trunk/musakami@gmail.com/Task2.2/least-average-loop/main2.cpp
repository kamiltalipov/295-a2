#include <iostream>
#include <vector>

using namespace std;

#define INF (1LL << 62) - 1

struct Edge
{
    int from, to;
    long long weight;

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
        long long weight;
        cin >> from >> to >> weight;
        graph.push_back(Edge(from - 1, to - 1, weight));
    }

    vector< vector<long long> > dist(n);
    vector< vector<int> > prev(n);
    for (int i = 0; i < n; i++)
    {
        dist[i].resize(n + 1, INF);
        prev[i].resize(n + 1, -1);
    }
    dist[0][0] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < m; j++)
            if (dist[graph[j].from][i - 1] + graph[j].weight < dist[graph[j].to][i])
            {
                dist[graph[j].to][i] = dist[graph[j].from][i - 1] + graph[j].weight;
                prev[graph[j].to][i] = graph[j].from;
            }

    long double best;
    int bestv = -1;
    int length;
    for (int i = 0; i < n; i++)
    {
        long double current = (long double)(dist[i][n] - dist[i][0]) / n;
        int clength = n;
        for (int j = 1; j < n; j++)
        {
            if ((long double)(dist[i][n] - dist[i][j]) / (n - j) > current)
            {
                current = (long double)(dist[i][n] - dist[i][j]) / (n - j);
                clength = n - j;
            }

        }
        if (i == 0 || current < best)
        {
            best = current;
            bestv = i;
            length = clength;
        }
    }
    if (prev[bestv][n] == -1)
        cout << "No loop";
    else
    {
        cout << best << endl;
        for (int i = 0; i < length; i++)
        {
            cout << bestv + 1 << " ";
            bestv = prev[bestv][n - i];
        }
        cout << bestv + 1;
    }
    return 0;
}

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <stack>

using namespace std;

#define CAP (1 << 30) - 1

struct Edge
{
    int from, to, weight;

    Edge(int from, int to, int weight):
        from(from), to(to), weight(weight) {}
};


int main()
{
    int n;
    cin >> n;
    vector<int> cnt(n);
    for (int i = 0; i < n; i++)
        cin >> cnt[i];
    for (int i = 1; i < n; i++)
        cnt[i] = cnt[i] + cnt[i - 1];
    vector<vector<Edge> > graph(cnt[n - 1]);
    vector<int> prev(cnt[n - 1], -1), dist(cnt[n - 1], CAP);
    vector<bool> used(cnt[n - 1]);
    for (int i = 0; i < n; i++)
        cnt[i]--;
    int k;
    cin >> k;
    for (int i = 0; i < k; i++)
    {
        int from, to, weight;
        cin >> from >> to >> weight;
        from--;
        to--;
        graph[from].push_back(Edge(from, to, weight));
        graph[to].push_back(Edge(to, from, weight));
    }
    int start, finish;
    cin >> start >> finish;
    priority_queue<pair<int, int>, vector< pair<int, int> >, greater< pair<int, int> > > heap;
    heap.push(make_pair(0, start - 1));
    dist[start - 1] = 0;
    while (!heap.empty())
    {
        pair<int, int> top = heap.top();
        int v = top.second;
        heap.pop();
        if (used[v])
            continue;
        used[v] = true;
        int group = lower_bound(cnt.begin(), cnt.end(), v) - cnt.begin();
        int right = cnt[group];
        int left = 0;
        if (group != 0)
            left = cnt[group - 1] + 1;
        for (int i = left; i <= right; i++)
            if (dist[i] > dist[v])
            {
                dist[i] = dist[v];
                prev[i] = v;
                heap.push(make_pair(dist[i], i));
            }
        for (int i = 0; i < graph[v].size(); i++)
        {
            int u = graph[v][i].to;
            int w = graph[v][i].weight;
            if (dist[u] > dist[v] +  w)
            {
                dist[u] = dist[v] + w;
                prev[u] = v;
                heap.push(make_pair(dist[u], u));
            }
        }
    }
    if (dist[finish - 1] == CAP)
    {
        cout << "No way";
        return 0;
    }
    cout << dist[finish - 1] << endl;
    stack<int> ans;
    int c = finish - 1;
    while (c != -1)
    {
        ans.push(c);
        c = prev[c];
    }
    while (!ans.empty())
    {
        cout << ans.top() + 1;
        ans.pop();
        if (!ans.empty())
            cout << " -> ";
    }
    return 0;
}

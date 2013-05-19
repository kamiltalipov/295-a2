#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector< vector<int> > graph(n);
    for (int i = 0; i < n; i++)
        graph[i].resize(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> graph[i][j];
    vector<int> potent(2 * n, 0);
    vector<int> back(n, -1);
    vector<int> forward(n, -1);
    vector<int> dist(2 * n, (1 << 31) -1);
    vector<int> prev(2 * n, -1);
    vector<bool> used(2 * n, false);
    for (int k = 0; k < n; k++)
    {
        int f1 = potent[0];
        int f2 = potent[1];
        int f3 = potent[2];
        int f4 = potent[3];
        for (int i = 0; i < 2 * n; i++)
        {
            dist[i] = (1 << 31) - 1;
            prev[i] = -1;
        }
        for (int i = 0; i < n; i++)
            if (forward[i] == -1)
                dist[i] = 0;
        for (int i = 0; i < 2 * n; i++)
            used[i] = false;
        for (int i = 0; i < 2 * n; i++)
        {
            int mindist = (1 << 31) - 1;
            int minv = 0;
            for (int j = 0; j < 2 * n; j++)
                if (!used[j] && dist[j] < mindist)
                {
                    minv = j;
                    mindist = dist[j];
                }
            used[minv] = true;
            if (minv >= n)
            {
                int second = minv - n;
                int first = back[second];
                if (first != -1)
                   if (dist[first] > dist[minv] - graph[first][second] + potent[minv] - potent[first])
                   {
                        dist[first] = dist[minv] - graph[first][second] + potent[minv] - potent[first];
                        prev[first] = minv;
                   }
            }
            else
            for (int j = 0; j < n; j++)
                if (dist[n + j] > dist[minv] + graph[minv][j] + potent[minv] - potent[n + j])
                {
                    dist[n + j] = dist[minv] + graph[minv][j] + potent[minv] - potent[n + j];
                    prev[n + j] = minv;
                }
        }
        for (int i = 0; i < 2 * n; i++)
            if (dist[i] != -1)
                potent[i] = dist[i] + potent[i];
        int mindist = (1 << 31) - 1;
        int minv = -1;
        for (int i = 0; i < n; i++)
            if (back[i] == -1 && potent[n + i] < mindist)
            {
                mindist = potent[n + i];
                minv = n + i;
            }
        int current = minv;
        while (current != -1 && prev[current] != -1)
        {
            int p = prev[current];
            back[current - n] = prev[current];
            forward[prev[current]] = current - n;
            current = prev[prev[current]];
        }
    }
    for (int i = 0; i < n; i++)
    {
        cout << i << ": " << forward[i] << endl;
    }
    return 0;
}

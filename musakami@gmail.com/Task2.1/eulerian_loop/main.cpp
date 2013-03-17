#include "graph.h"

#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n;
    cin >> n;
    Graph g(n);
    int m;
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        int k1, k2;
        cin >> k1 >> k2;
        g.AddEdge(k1, k2);
    }

    vector<int> loop;
    g.eulerian_loop(loop);
    for (int i = 0; i < loop.size(); i++)
    {
        cout << loop[i] << " ";
    }
    return 0;
}

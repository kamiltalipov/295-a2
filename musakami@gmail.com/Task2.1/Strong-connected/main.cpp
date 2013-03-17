#include "graph.h"

#include <iostream>

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

    vector<vector<int> > strong_components;
    g.find_strong_tarjan(strong_components);
    for (int i = 0; i < strong_components.size(); i++)
    {
        cout << i + 1 << ": ";
        for (int j = 0; j < strong_components[i].size(); j++)
            cout << strong_components[i][j] << " ";
        cout << endl;
    }
    return 0;
}

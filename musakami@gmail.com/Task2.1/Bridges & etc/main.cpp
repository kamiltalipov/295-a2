#include "graph.h"

#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;
    Graph g(n, true);
    int m;
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        int k1, k2;
        cin >> k1 >> k2;
        g.AddEdge(k1, k2);
    }
    vector<Edge> bridges;
    vector< vector<int> > edgeblocks;
    vector<int> cutvertex;
    vector< vector<Edge> > vertblocks;
    g.dfs_all_find(bridges, edgeblocks, cutvertex, vertblocks);
    cout << "Cut vertexes" << endl;
    for (int i = 0; i < cutvertex.size(); i++)
        cout << cutvertex[i] << " ";
    cout << endl;
    cout << "Vertex biconected blocks" << endl;
    for (int i = 0; i < vertblocks.size(); i++)
    {
        cout << i + 1 << ": ";
        for (int j = 0; j < vertblocks[i].size(); j++)
            cout << "(" << vertblocks[i][j].from << ", " << vertblocks[i][j].to << ") ";
        cout << endl;
    }
    cout << "Bridges" << endl;
    for (int i = 0; i < bridges.size(); i++)
        cout << "(" << bridges[i].from << ", " << bridges[i].to << ") ";
    cout << endl;
    cout << "Edge biconected blocks" << endl;
    for (int i = 0; i < edgeblocks.size(); i++)
    {
        cout << i + 1 << ": ";
        for (int j = 0; j < edgeblocks[i].size(); j++)
            cout << edgeblocks[i][j] << " ";
        cout << endl;
    }
    return 0;
}

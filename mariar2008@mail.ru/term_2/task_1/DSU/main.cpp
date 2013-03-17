#include <iostream>
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

class DSU{
public:
    vector<int> parent;
    vector<int> rank;
    DSU(int V){
        parent.resize(V + 1);
        rank.resize(V + 1);
        for (int i = 1; i < V; i++){
            parent[i] = i;
            rank[i] = 0;
        }
    }
    void Add(int x){
        if (parent.size() < x + 1)
            parent.resize(x + 1);
        parent[x] = x;
    }
    int FindRoot(int x){
        int i = x;
        while (parent[i] != i)
            i = parent[i];
        int root = i;
        i = x;
        while (i != x){
            int j = parent[i];
            parent[i] = root;
            i = j;
        }
        return root;
    }
    void Union(int x, int y){
        int rootx = FindRoot(x);
        int rooty = FindRoot(y);
        if (rank[rootx] > rank[rooty])
            parent[rootx] = rooty;
        else
            parent[rooty] = rootx;
        if (rank[rootx] == rank[rooty])
            ++rank[rooty];
    }
};

void Solve(){
    int V, E;
    cin >> V >> E;
    DSU myDSU(V);
    for (int i = 0; i < E; i++){
        int value, u, v;
        cin >> value >> u >> v;
        if (value == 0){
            if (myDSU.FindRoot(u) == myDSU.FindRoot(v))
                cout << u << " и " << v << " связаны \n";
            else
                cout << u << " и " << v << " не связвны \n";
        }
        else
            myDSU.Union(u, v);
    }
}

int main()
{
    Solve();
    return 0;
}

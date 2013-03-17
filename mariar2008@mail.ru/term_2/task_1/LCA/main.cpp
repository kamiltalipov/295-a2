#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>

#define WHITE 0
#define GREY 1
#define BLACK 2
using namespace std;

class Graph{
public:
    class DSU{
    public:
        vector<int> parent;
        vector<int> rank;
        vector<int> root;
        void InitDSU(int n){
            parent.resize(n + 1);
            rank.resize(n + 1);
            root.resize(n + 1);
        }
        int FindRoot(int x){
            if (parent[x] == x)
                return x;
            parent[x] = FindRoot(parent[x]);
            return parent[x];
        }
        void Union(int x, int y, int CurrentRoot){
            int rootx = FindRoot(x);
            int rooty = FindRoot(y);
            if (rank[rootx] > rank[rooty]){
                parent[rooty] = rootx;
                root[rootx] = CurrentRoot;
            }
            else{
                parent[rootx] = rooty;
                root[rooty] = CurrentRoot;
            }
            if (rank[rootx] = rank[rooty])
                rank[rooty]++;
        }
    };
    vector<vector<int> > child;
    vector<vector<int > > request;
    vector<int> used;
    //vector<myType> answer;
    DSU myDSU;

    void ReadGraph(){
        int V;
        cin >> V;
        child.resize(V + 1);
        myDSU.InitDSU(V);
        request.resize(V + 1);
        used.resize(V + 1, WHITE);
        for (int i = 0; i < V - 1; i++){
            int u, v;
            cin >> u >> v;
            child[u].push_back(v);
        }
    }
    void ReadRequest(){
        int Num;
        cin >> Num;
        for (int i = 0; i < Num; i++){
            int u, v;
            cin >> u >> v;
            request[u].push_back(v);
            request[v].push_back(u);
        }
    }
    void dfs(int v){
        used[v] = GREY;
        myDSU.parent[v] = v; myDSU.root[v] = v;
        for (int i = 0; i < child[v].size(); i++){
            int u = child[v][i];
            if (used[u] == WHITE){
                dfs(u);
                myDSU.Union(v, u, v);
            }
        }
        for (int i = 0; i < request[v].size(); i++){
            if (used[request[v][i]] != WHITE){
                cout << v << " " << request[v][i] << " " << " " << myDSU.root[myDSU.FindRoot(request[v][i])] << "\n";
            }
        }
    }

};

int main()
{
    Graph G;
    G.ReadGraph();
    G.ReadRequest();
   // cout << "OLOLO" << "\n";
    G.dfs(1);
    //G.WriteAnswer();
    return 0;
}

#include <iostream>
#include <stdio.h>
#include <vector>
#include <stack>

using namespace std;

class graph{
public:
    void ReadGraph(){
        int V, E;
        cin >> V >> E;
        child.resize(V + 1);
        degin.resize(V + 1, 0);
        degout.resize(V + 1, 0);
	    link.resize(V + 1, 0);
	    used.resize(V + 1, false);
        for (int i = 0; i < E; i++){
            int u, v;
            cin >> u >> v;
            degin[v]++;
            degout[u]++;
            (child[u]).push_back(v);
        }
    }

    void FindEulerCircle(){
        for (int i = 1; i < child.size(); i++){
            if (degin[i] != degout[i]){
                cout << "NO";
                return;
            }
        }
        dfs(1);
        for (int i = 1; i < child.size(); i++){
            if (!used[i]){
                cout << "NO";
                return;
            }
        }
        WriteCircle();
    }

    void WriteCircle(){
        cout << "Yes \n";
        for (int i = 0; i < Vert.size(); i++)
            cout << Vert[i] << " ";
        cout << "\n";
    }

    void dfs(int v){
        used[v] = true;
        Vert.push_back(v);
        while (link[v] < child[v].size()){
            int u = child[v][link[v]];
            link[v]++;
            dfs(u);
        }
    }

    vector< vector<int> > child;
    vector<int> link;
    vector<int> degin, degout;
    vector<int> Vert;
    vector <bool> used;
};


int main()
{
    graph myGraph;
    myGraph.ReadGraph();
    myGraph.FindEulerCircle();
    return 0;
}

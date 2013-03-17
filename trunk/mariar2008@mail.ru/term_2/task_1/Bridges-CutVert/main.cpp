#include <iostream>
#include <stdio.h>
#include <vector>
#include <stack>

#define WHITE 0
#define GREY 1
#define BLACK 2

using namespace std;
class graph{
public:
    graph(){CurrentTime = 0; NumOne = 1; NumTwo = 0;}
    void ReadGraph(){
        CurrentTime = 0;
        int V, E;
        cin >> V >> E;
        child.resize(V + 1);
        tin.resize(V + 1);
        tout.resize(V + 1);
        up.resize(V + 1);
	    used.resize(V + 1, 0);
        for (int i = 0; i < E; i++){
            int u, v;
            cin >> u >> v;
            (child[u]).push_back(v);
            (child[v]).push_back(u);
        }
    }
    void Find(){
        for (int i = 1; i < child.size(); i++){
            used[i] = WHITE;
        }
        for (int i = 1; i < child.size(); i++)
            if (used[i] == WHITE){
                dfs(i, 0, i);
                if (!Vert.empty())
                    PopVert(i);
                if (!Edge.empty()){
             //       cout << "OLOLO \n";
                    PopEdge();
                }
            }
       /* for (int i = 1; i < child.size(); i++){
            cout << i << " tin " << tin[i] << " up " << up[i] << "\n";
        }*/
        WriteCompVert();
        WriteBridges();
        WriteCutVert();
    }
    void WriteCompVert(){

        for (int i = 0; i < CompVert.size(); i++){
            vector<bool> mentioned(child.size(), false);
            cout << "Компонента вершинной двусвязности №" << i + 1 << "\n";
            for (int j = 0; j < CompVert[i].size(); j++){
               // cout << CompVert[i][j] << " ";
                if (!mentioned[CompVert[i][j]]){
                    cout << CompVert[i][j] << " ";
                    mentioned[CompVert[i][j]] = true;
                }
            }
            cout << "\n";
        }
    }
    void WriteCutVert(){
        vector<bool> mentioned(child.size(), false);
        int CutVertNum = 0;
        for (int i = 0; i < CutVert.size(); i++){
            if (!mentioned[CutVert[i]]){
                CutVertNum++;
                mentioned[CutVert[i]] = true;
            }
        }
        cout << "Количество точек сочленения " << CutVertNum << "\n";
        for (int i = 1; i < child.size(); i++){
            if (mentioned[i])
                cout << i << "\n";
        }
    }
    void AddBridge(int v, int u){
        pair<int, int> CurrentBridge;
        CurrentBridge.first = v;
        CurrentBridge.second = u;
        Bridges.push_back(CurrentBridge);
    }
    void AddCutVert(int v){
        CutVert.push_back(v);
    }
    void WriteBridges(){
        cout << "Количество мостов " << Bridges.size() << "\n";
        for (int i = 0; i < Bridges.size(); i++){
            cout << (Bridges[i]).first << " " << (Bridges[i]).second << "\n";
        }
    }
    void PopVert(int v){
        cout << "Компонента реберной двусвязности №" << NumOne << "\n";
        NumOne++;
        while (Vert.top() != v){
            cout << Vert.top() << " ";
            Vert.pop();
        }
        cout << Vert.top() << "\n";
        Vert.pop();
    }
    void PopEdge(pair<int, int> w){
        CompVert.resize(CompVert.size() + 1);
        int last = CompVert.size() - 1;
        while (Edge.top() != w){
            pair<int, int> TopElement = Edge.top();
            CompVert[last].push_back(TopElement.first);
            CompVert[last].push_back(TopElement.second);
            Edge.pop();
        }
        pair<int, int> TopElement = Edge.top();
        CompVert[last].push_back(TopElement.first);
        CompVert[last].push_back(TopElement.second);
        Edge.pop();
    }
    void PopEdge(){
        CompVert.resize(CompVert.size() + 1);
        int last = CompVert.size() - 1;
        //cout << last << "\n";
        while (!Edge.empty()){
            pair<int, int> TopElement = Edge.top();
           // cout << TopElement.first << " " << TopElement.second << "\n";
            CompVert[last].push_back(TopElement.first);
            CompVert[last].push_back(TopElement.second);
            Edge.pop();
        }
    }
    void dfs(int v, int parent, int root){
        used[v] = GREY;
        CurrentTime++;
        tin[v] = CurrentTime;
        up[v] = tin[v];
        int ChildNum = 0;
        Vert.push(v);
        vector<int> BoolVert;
        for (int i = 0; i < child[v].size(); i++){
            int u = child[v][i];
            pair<int, int> w;
            w.first = v;
            w.second = u;
            if (used[u] == WHITE){
                BoolVert.push_back(u);
                Edge.push(w);
                ChildNum++;
                dfs(u, v, root);
                up[v] = min(up[v], up[u]);
                if (tin[u] <= up[u]){
                    AddBridge(v, u);
                    PopVert(u);
                }
                if (up[u] >= tin[v] && v != root){
                    AddCutVert(v);
                    PopEdge(w);
                }
            }
            else
                if (u != parent)
                    up[v] = min(up[v], tin[u]);
        }
        //cout << v << " " << root << " " << ChildNum << "\n";
        if (v == root && ChildNum > 1){
            AddCutVert(v);

            for (int i = BoolVert.size() - 1; i >= 0; i--){
                pair<int, int> w;
                w.first = v;
                w.second = BoolVert[i];
                PopEdge(w);
            }
        }
        //cout << v << " " << tin[v] << " " << up[v] << "\n";
        used[v] = BLACK;
    }
    vector< vector<int> > child;
    vector<int> used;
    vector<int> tin, tout, up;
    vector<int> CutVert;
    vector< pair<int, int> > Bridges;
    int CurrentTime;
    stack <int> Vert;
    stack < pair<int, int> > Edge;
    int NumOne, NumTwo;
    vector< vector<int> > CompVert;
};
int main()
{
    graph myGraph;
    myGraph.ReadGraph();
    myGraph.Find();
    return 0;
}

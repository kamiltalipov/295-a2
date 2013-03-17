#include <iostream>
#include <stdio.h>
#include <vector>
#include <stack>
#define WHITE 0
#define GREY 1
#define BLACK 2

using namespace std;

class Graph{
public:
    void InitUsed(){
        for (int i = 1; i < used.size(); i++)
            used[i] = WHITE;
    }
    void dfsKosaraju(bool flag, int v){
        used[v] = GREY;
        int n;
        if (!flag){
            n = Tchild[v].size();
            cout << v << " ";
        }
        else
            n = child[v].size();
        for (int i = 0; i < n; i++){
            int u;
            if (flag)
                u = child[v][i];
            else
                u = Tchild[v][i];
            if (used[u] == WHITE)
                dfsKosaraju(flag, u);
        }
        if (flag)
            Vert.push_back(v);
    }
    void PopStack(int v){
        cout << "Компонента сильной связности \n";
        while (VertStack.top() != v){
            cout << VertStack.top() << " ";
            IsInStack[VertStack.top()] = false;
            VertStack.pop();
        }
        cout << VertStack.top() << "\n";
        VertStack.pop();
    }
    void dfsTarjan(int v){
        CurrentTime++;
        used[v] = GREY;
        VertStack.push(v);
        IsInStack[v] = true;
        tin[v] = CurrentTime;
        up[v] = tin[v];
        for (int i = 0; i < child[v].size(); i++){
            int u = child[v][i];
            if (used[u] == WHITE){
                dfsTarjan(u);
                up[v] = min(up[v], up[u]);
            }
            else
                if (IsInStack[u])
                    up[v] = min(up[v], tin[u]);
        }
        used[v] = BLACK;
        if (tin[v] == up[v])
            PopStack(v);
    }
    vector<vector<int> > child;
    vector<vector<int> > Tchild;
    vector<int> used;

    vector<int> Vert;

    vector<int> tin, up;
    vector<int> parent;
    stack<int> VertStack;
    vector<bool> IsInStack;
    int CurrentTime;
    void Read(){
        int V, E;
        cin >> V >> E;
        child.resize(V + 1);
        Tchild.resize(V + 1);
        used.resize(V + 1);

        tin.resize(V + 1);
        parent.resize(V + 1);
        up.resize(V + 1);
        IsInStack.resize(V + 1, false);
        for (int i = 0; i < E; i++){
            int u, v;
            cin >> u >> v;
            child[u].push_back(v);
            Tchild[v].push_back(u);
        }
    }

    void KosarajuAlgorithm(){
        InitUsed();
        for (int i = 1; i < child.size(); i++ ){
            if (used[i] == WHITE)
                dfsKosaraju(true, i);
        }
        InitUsed();
        int j = 0;
        for (int i = Vert.size() - 1; i >= 0; i--){
            if (used[Vert[i]] == WHITE){
                j++;
                cout << "Компонента сильной связности №" << j << "\n";
                dfsKosaraju(false, Vert[i]);
                cout << "\n";
            }
        }
    }

    void TarjanAlgorithm(){
        InitUsed();
        CurrentTime = 0;
        for (int i = 1; i < used.size(); i++){
            if (used[i] == WHITE)
                dfsTarjan(i);
        }
    }
};

int main()
{
    Graph myG;
    myG.Read();
    myG.KosarajuAlgorithm();
    myG.TarjanAlgorithm();
    return 0;
}

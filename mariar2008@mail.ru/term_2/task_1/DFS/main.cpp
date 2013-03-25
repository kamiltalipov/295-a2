#include <iostream>
#include <stdio.h>
#include <vector>
#include <stack>

#define WHITE 0
#define GREY 1
#define BLACK 2

using namespace std;
//DFS
class graph{
public:
    void ReadGraph(){
        int V, E;
        cin >> V >> E;
        child.resize(V + 1);
        degin.resize(V + 1, 0);
	    used.resize(V + 1, 0);
        for (int i = 0; i < E; i++){
            int u, v;
            cin >> u >> v;
            degin[v]++;
            (child[u]).push_back(v);
        }
    }
    void TopSort(){
		HaveCircle = false;
        used.resize(child.size());
        for (int i = 1; i < child.size(); i++)
            if ((used[i] == WHITE) && (degin[i] == 0)){
                pair<int, int> StackElement;
                StackElement.first = i;
                StackElement.second = 0;
                VertStack.push(StackElement);
				//cout << "Add " << i << "\n";
                used[i] = GREY;
                dfs();
            }
    }
    void dfs(){
        while (!VertStack.empty()){
            pair<int, int> CurStackElement = VertStack.top();
            int v = CurStackElement.first;
			//cout << "Top " << v << "\n";
            VertStack.pop();
            int i;
            for (i = CurStackElement.second; i < child[v].size(); ++i){

                int u = child[v][i];
				if (used[u] == GREY){
					HaveCircle = true;
				}
                if (used[u] == WHITE){
                    used[u] = GREY;
                    pair<int, int> StackElement;
                    StackElement.first = v;
                    StackElement.second = i + 1;
                    VertStack.push(StackElement);

                    StackElement.first = u;
                    StackElement.second = 0;
                    VertStack.push(StackElement);
					//cout << "Push " << u << "\n";

					break;
                }
            }
			if (i == child[v].size()){
            	VertTopSortReverse.push_back(v);
            	used[v] = BLACK;
			}
        }

    }
    void WriteVertSort(){
		if (HaveCircle){
			cout << "No";
			return;
		}
		for (int i = child.size() - 1; i > 0; i--){
			if (used[i] == WHITE){
				cout << "No";
				return;
			}
		}

		cout << "Yes" << "\n";
        for (int i = VertTopSortReverse.size() - 1; i >= 0; i--)
           	cout << VertTopSortReverse[i] << " ";

		//cout << "\n";
    }
    vector< vector<int> > child;
    vector<int> used;
    vector<int> VertTopSortReverse;
    stack<pair<int, int> > VertStack;
    vector<int> degin;
	bool HaveCircle;
};

int main(){
//    freopen("input.txt","r",stdin);
//    freopen("output.txt","w",stdout);


    graph MyGraph;
    MyGraph.ReadGraph();
    MyGraph.TopSort();
    MyGraph.WriteVertSort();
    return 0;
}

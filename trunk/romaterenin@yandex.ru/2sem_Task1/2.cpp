#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>
using namespace std;

int n; // количество вершин
vector< vector <int> > g;
vector <bool> used;
vector<int> comp;
vector <int> timer_in, fup;
int dfs_timer;
 
void dfs (int v, int p = -1) {
	used[v] = true;
	timer_in[v] = fup[v] = dfs_timer++;
	int children = 0;
	for (size_t i=0; i<g[v].size(); i++) {
		int to = g[v][i];
		if (to == p)  continue;
		if (used[to])
			fup[v] = min (fup[v], timer_in[to]);
		else {
			dfs (to, v);
			fup[v] = min (fup[v], fup[to]);
			if (fup[to] > timer_in[v])
				cout<<v+1<<" to "<<to+1<<" - is bridge"<<endl;
			if (fup[to] >= timer_in[v] && p != -1)
				cout<<v+1<<" is cutroint"<<endl;
			children++;
		}
	}
	if (p == -1 && children > 1)
		cout<<v+1<<" is cutroint"<<endl;
}
 
void find_bridges_and_cutroint() { // поиск мостов
	dfs_timer = 0;
	for (int i=0; i<n; i++)
		used[i] = false;
	for (int i=0; i<n; i++)
		if (!used[i])
			dfs (i);
}

int main(){
	//freopen("TextFile2.txt", "r", stdin);
	int m; // количество ребер
	cin>>n>>m;
	g.resize(n);
	for(int i=0;i<m;i++){
		int v1,v2;
		cin>>v1>>v2;
		g[v1-1].push_back(v2-1);
		g[v2-1].push_back(v1-1);
	}
	used.resize(n,0);
	comp.resize(n);
	timer_in.resize(n);
	fup.resize(n);
	find_bridges_and_cutroint();
	cout<<endl;
	return 0;
}
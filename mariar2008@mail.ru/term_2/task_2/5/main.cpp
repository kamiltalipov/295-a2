#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <math.h>
#include <vector>

#define INF 1000000
using namespace std;

struct my_struct{
	my_struct(int a, int b, int c){
		v = a; u = b; cost = c;
	}
	int v, u, cost;
};

bool func(my_struct a, my_struct b){
	return (a.cost < b.cost);
}

class graph{
public:
	graph(int n){
		size = n;
		h = 0;
		int step = 1;
		while (step <= n){
			++h;
			step *= 2;
		}
		edge.resize(n + 1);
		ans.resize(n + 1);
		parent.resize(n + 1);
		d.resize(n + 1, INF);
		tree.resize(n + 1);
		up.resize(n + 1);
		for (int i = 0; i < n; ++i)
			up[i].resize(h + 1);
		tin.resize(n + 1);
		tout.resize(n + 1);
	}
	
	void Solve(){
		Read();
		Dijkstra();
		GetNewCost();
		GetAnswer();
	}
private:
	int size, h, my_time;
	vector<vector<pair<int, int> > > edge;
	vector<int> ans, tin, tout;
	vector<int> parent;
	vector<my_struct> arc;
	vector<int> d;
	vector<vector<int> > tree;
	vector<vector<int> > up;
	
	vector<int> dsu_parent;
	
	int GetRoot(int v){
		if (dsu_parent[v] == v)
			return v;
		dsu_parent[v] = GetRoot(dsu_parent[v]);
		return dsu_parent[v];
	}
	
	void Union(int v, int u){
		int root_v = GetRoot(v), root_u = GetRoot(u);
		if (Upper(root_v, root_u))
			dsu_parent[root_u] = root_v;
		else
			dsu_parent[root_v] = root_u;
	}
	
	void Read(){
		int m, v, u, cost; 
		cin >> m;
		for (int i = 0; i < m; ++i){
			cin >> v >> u >> cost;
			pair<int, int> cur_arc(u, cost);
			edge[v].push_back(cur_arc);
			cur_arc.first = v;
			edge[u].push_back(cur_arc);
		}
	}
	void Dijkstra(){
		vector<bool> used(size + 1, false);
		d[0] = 0;
		for (int i = 1; i < size; ++i){
			int cur_min = INF, k = -1;
			for (int j = 0; j < size; ++j)
				if (!used[j] && d[j] < cur_min){
					cur_min = d[j]; k = j;
				}
			if (k == -1)
				break;
			used[k] = true;
			for (int j = 0; j < edge[k].size(); ++j){
				int u = edge[k][j].first, cost = edge[k][j].second;
				if (!used[u] && d[u] > d[k] + cost){
					d[u] = d[k] + cost;
					parent[u] = k;
				}
			}
		}
	}
	void GetNewCost(){
		for (int i = 0; i < size; ++i)
			for (int j = 0; j < edge[i].size(); ++j){
				int v = i, u = edge[i][j].first, cost = edge[i][j].second;
				if (parent[v] != u && parent[u] != v){
					my_struct cur_arc(v, u, cost + d[v] + d[u]);
					arc.push_back(cur_arc);
				}
			}
		sort(arc.begin(), arc.end(), func);
	}
	void dfs(int v){
		++my_time;
		tin[v] = my_time;
		for (int i = 0; i < tree[v].size(); ++i)
			dfs(tree[v][i]);
		++my_time;
		tout[v] = my_time;
	}
	bool Upper(int v, int u){
		if (tin[v] <= tin[u] && tout[v] >= tout[u])
			return true;
		else
			return false;
	}
	int lca(int v, int u){
		if (Upper(v, u)) return v;
		if (Upper(u, v)) return u;
		int w = v;
		for (int i = h; i >= 0; --i)
			if (!Upper(up[w][i], u))
				w = up[w][i];
				
		return parent[w];
	}
	void GetAnswer(){
		for (int i = 1; i < size; ++i)
			tree[parent[i]].push_back(i);
		
		my_time = 0;
		dfs(0);
		
		
		for (int i = 0; i < size; ++i){
			up[i][0] = parent[i];
			for (int j = 1; j <= h; ++j){
				up[i][j] = up[up[i][j - 1]][j - 1];
			}
		}
		cout << endl;
		vector<bool> used(size + 1, false);
		dsu_parent.resize(size + 1);
		for (int i = 0; i <= size; ++i)
			dsu_parent[i] = i;
			
		for (int i = 0; i < arc.size(); ++i){
			int v = arc[i].v, u = arc[i].u;	
			int w = lca(v, u);
			int j = v;
			int j0 = v;
			while (!Upper(j, w)){
				//cout << j << endl;
				Union(j0, j);
				if (!used[j]){
					used[j] = true;
					cout << j << " -- " << v << " " << u << endl;
				}
				j0 = j;
				int cpar = GetRoot(j);
				//cout << "cpar = " << cpar << endl;
				j = parent[cpar];
			}
			//cout << "ololo" << endl;
			j = u;
			j0 = u;
			while (!Upper(j, w)){
				//cout << j << endl;
				Union(j, j0);
				if (!used[j]){
					used[j] = true;
					cout << j << " -- " << v << " " << u << endl;
				}
				j0 = j;
				int cpar = GetRoot(j);
				//cout << "cpar = " << cpar << endl;
				j = parent[cpar];
			}
		}
	}
};

int main(){
	int n;
	cin >> n;
	graph my_graph(n);
	my_graph.Solve();
	return 0;
}

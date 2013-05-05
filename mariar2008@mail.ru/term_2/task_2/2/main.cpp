#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

void Read(int n, vector<vector<double> > &matrix){
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j){
			double num;
			cin >> num;
			matrix[i].push_back(num);
		}
}

void FordBellman(vector<vector<double> > &matrix){
	int n = matrix.size();
	vector<double> d(n, 0);
	vector<int> parent(n, -1);
	d[0] = 1;
	for (int k = 0; k < n - 1; ++k){
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < n; ++j){
				if (i != j)
					if (d[i] < d[j]*matrix[i][j]){
						d[i] = d[j]*matrix[i][j];
						parent[i] = j;
					}
			}
		}
	}
	vector<double> current = d;
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < n; ++j){
			if (i != j)
				if (d[i] < d[j]*matrix[i][j]){
					d[i] = d[j]*matrix[i][j];
					parent[i] = j;
				}
		}
	}
	
	int node = -1;
	for (int i = 0; i < n; ++i){
		if (current[i] != d[i]){
			node = i;
			break;
		}
	}
	if (node == -1){
		cout << "NO" << endl;
		return;
	}
	
	vector<bool> used(n, false);
	while (node != -1){
		if (used[node])
			break;
		used[node] = true;
		node = parent[node];
	}
	if (node == -1){
		cout << "NO" << endl;
		return;
	}
	for (int i = 0; i < n; ++i)
		used[i] = false;
	int curnum = 1;
	while (!used[node]){
		used[node] = true;
		cout << curnum << " of " << node << endl;
		curnum *= matrix[parent[node]][node];
		node = parent[node];
	}
	cout << curnum << " of " << node << endl;
}
void getpath(int v, int u, vector<int> &path, vector<vector<int> > &parent){
	//cout << v << ' ' << u << endl;
	if (parent[v][u] == -1 || parent[v][u] == u || parent[v][u] == v){
		if (v != u)
		path.push_back(v);
	}
	else{
		getpath(v, parent[v][u], path, parent);
		getpath(parent[v][u], u, path, parent);
	}
}
void Floyd(int n, vector<vector<double> > &matrix){
	vector<vector<double> > d = matrix;
	vector<vector<int> > parent(n);
	for (int i = 0; i < n; ++i)
		parent[i].resize(n, -1);
	for (int k = 0; k < n; ++k)
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				if (d[i][k]*d[k][j] > d[i][j]){
					d[i][j] = d[i][k]*d[k][j];
					parent[i][j] = k;
				}
	vector<int> path;
	bool flag = false;
	for (int i = 0; i < n; ++i)
		if (d[i][i] > 1){
			flag = true;
			getpath(i, i, path, parent);
		}
	if (!flag)
		cout << "NO";
	else{
		cout << 1 << " of " << path[0] << endl;
		int cur = 1;
		for (int i = 1; i < path.size(); ++i)
			if (path[i - 1] != path[i]){
				cur = cur*matrix[path[i]][path[i - 1]];
				cout << cur << " of " << path[i] << endl;
			}
		cur = cur*matrix[path[0]][path[path.size() - 1]];
		cout << cur << " of " << path[0] << endl;
	}	
}
int main(){
	int n;
	cin >> n;
	vector<vector<double> > matrix(n);
	Read(n, matrix);
	//FordBellman(matrix);
	Floyd(n, matrix);
}

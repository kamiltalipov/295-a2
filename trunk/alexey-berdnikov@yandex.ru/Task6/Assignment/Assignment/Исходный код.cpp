//#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <iostream>
#include <string>
#include <climits>

using namespace std;

enum colour { WHITE, BLACK };

void Dijkstra(const vector<vector<int>>& weight, const vector<int>& potentials, const vector<size_t>& pairs,
	vector<int>& distance, vector<size_t>& prev)
{
	size_t n = weight.size();
	vector<bool> visited(2*n);

	prev.clear();
	prev.resize(2*n,-1);
	distance.clear();
	distance.resize(2*n,INT_MAX);
	for (size_t i = 0; i<n; ++i)
		if (pairs[i]==-1)
			distance[i] = 0;
	for (;;) {
		size_t i_min = 0;
		for (size_t i = 1; i < 2*n; ++i)
			if (visited[i_min] || !visited[i]&&distance[i]<distance[i_min]) i_min = i;
		if (visited[i_min] || distance[i_min]==INT_MAX) return;
		if (i_min<n) {
			for (size_t i = 0; i<n; ++i) {
				if (i != pairs[i_min]) {
					int new_dist = distance[i_min]+weight[i_min][i]+potentials[i_min]-potentials[n+i];
					if (new_dist<distance[n+i]) {
						distance[n+i] = new_dist;
						prev[n+i] = i_min;
					}
				}
			}
		}
		else {
			size_t i = pairs[i_min];
			if (i != -1) {
				int new_dist = distance[i_min]-weight[i][i_min-n]+potentials[i_min]-potentials[i];
				if (new_dist<distance[i]) {
					distance[i] = new_dist;
					prev[i] = i_min;
				}
			}
		}
		visited[i_min] = true;
	}
}

int main()
{
//	freopen("input.txt","r",stdin);
	size_t n;
	cin >> n;

	vector<vector<int>> weight(n);
	for (size_t i = 0; i<n; ++i) {
		weight[i].resize(n);
		for (size_t j = 0; j<n; ++j) cin >> weight[i][j];
	}

	vector<int> potentials(2*n);
	vector<size_t> pairs(2*n,-1);
	vector<int> distance;
	vector<size_t> prev;
	for (;;) {
		Dijkstra(weight,potentials,pairs,distance,prev);
		for (size_t i = 0; i < 2*n; ++i)
			potentials[i] = distance[i]+potentials[i];
		size_t i_min = n;
		for (size_t i = n+1; i < 2*n; ++i)
			if (pairs[i_min]!=-1 || pairs[i]==-1&&distance[i]<distance[i_min]) i_min = i;
		if (pairs[i_min]!=-1) break;
		size_t i = i_min;
		for (;;) {
			pairs[i] = prev[i];
			pairs[prev[i]] = i;
			i = prev[i];
			if (prev[i]==-1) break;
			i = prev[i];
		}
	}
	int result = 0;
	for (size_t i = 0; i<n; ++i) result += weight[i][pairs[i]-n];
	cout << result;
	return 0;
}
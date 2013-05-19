#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void find_cycle(const vector<size_t>& previous, size_t i, vector<size_t>& list)
{
	vector<bool> visited(previous.size());
	for (; !visited[i]; i = previous[i]) visited[i] = true;
	list.push_back(i);
	for (size_t j = previous[i]; j!=i; j = previous[j]) list.push_back(j);
	list.push_back(i);
	reverse(list.begin(),list.end());
}

bool Floyd_Warshall(vector<vector<double>> table, vector<size_t>& list)
{
	list.clear();

	size_t n = table.size();
	vector<vector<size_t>> previous(n);
	for (size_t i = 0; i<n; ++i)
		previous[i].resize(n,i);
	for (size_t k = 0; k<n; ++k) {
		for (size_t i = 0; i<n; ++i) {
			for (size_t j = 0; j<n; ++j) {
				double new_distance = table[i][k]*table[k][j];
				if (new_distance>table[i][j]) {
					table[i][j] = new_distance;
					previous[j][i] = previous[k][i];
				}
				if (i==j && new_distance>1) {
					find_cycle(previous[i],i,list);
					return true;
				}
			}
		}
	}
	return false;
}

bool Bellman_Ford(const vector<vector<double>>& table, vector<size_t>& list)
{
	list.clear();

	size_t n = table.size();
	vector<double> distance(n,0);
	distance[0] = 1;
	vector<size_t> previous(n);
	for (size_t k = 1; k<n; ++k) {
		for (size_t i = 0; i<n; ++i) {
			for (size_t j = 0; j<n; ++j) {
				double new_distance = distance[j]*table[i][j];
				if (distance[i] < new_distance) {
					distance[i] = new_distance;
					previous[i] = j;
				}
			}
		}
	}
	
	for (size_t i = 0; i<n; ++i) {
		for (size_t j = 0; j<n; ++j) {
			if (distance[i] < distance[j]*table[i][j]) {
				previous[i] = j;
				find_cycle(previous,i,list);
				return true;
			}
		}
	}
	return false;
}

int main()
{
	size_t n;
	cin >> n;
	vector<vector<double>> table(n);
	for (size_t i = 0; i<n; ++i) {
		table[i].resize(n);
		for (size_t j = 0; j<n; ++j) cin >> table[i][j];
	}

	vector<size_t> list;
	if (Bellman_Ford(table,list)) {
		cout << "Yes\n";
		for (size_t i = 0; i < list.size(); ++i)
			cout << list[i]+2 << ' ';
	}
	else
		cout << "No";
	return 0;
}
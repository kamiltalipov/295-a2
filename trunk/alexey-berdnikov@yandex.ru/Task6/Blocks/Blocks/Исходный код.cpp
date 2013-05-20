#include <vector>
#include <iostream>
#include <string>

using namespace std;

enum colour { WHITE, BLACK };

bool DFS_visit(const vector<vector<size_t>>& arcs, size_t v, vector<size_t>& pairs, vector<colour>& colours)
{
	colours[v] = BLACK;
	if (v<arcs.size()) {
		for (size_t i = 0; i < arcs[v].size(); ++i) {
			size_t u = arcs[v][i];
			if (u != pairs[v] && colours[u]==WHITE) {
				if (DFS_visit(arcs,u,pairs,colours)) {
					pairs[v] = u;
					pairs[u] = v;
					return true;
				}
			}
		}
		return false;
	}
	size_t u = pairs[v];
	return u==-1 || DFS_visit(arcs,u,pairs,colours);
}

bool find_flow(const vector<vector<size_t>>& arcs, size_t m, vector<size_t>& pairs)
{
	size_t n = arcs.size();
	vector<colour> colours(n+m);
	for (size_t i = 0; i<n; ++i)
		if (colours[i]==WHITE && pairs[i]==-1 && DFS_visit(arcs,i,pairs,colours)) return true;
	return false;
}

size_t max_flow(const vector<vector<size_t>>& arcs, size_t m, vector<size_t>& result)
{
	size_t answer = 0;
	size_t n = arcs.size();
	vector<size_t> pairs(n+m,-1);
	while (find_flow(arcs,m,pairs)) ++answer;
	result = vector<size_t>(pairs.begin()+n,pairs.end());
	return answer;
}

int main()
{
	size_t n;
	cin >> n;

	string word;
	cin >> word;
	size_t m = word.length();

	vector<string> blocks(n);
	for (size_t i = 0; i<n; ++i)
		cin >> blocks[i];

	vector<vector<size_t>> arcs(n);
	for (size_t i = 0; i<n; ++i)
			for (size_t k = 0; k<m; ++k)
				if (blocks[i].find(word[k]) != string::npos)
					arcs[i].push_back(n+k);

	vector<size_t> pairs;
	if (max_flow(arcs,m,pairs)==m) {
		cout << "YES\n";
		for (size_t i = 0; i<m; ++i)
			cout << pairs[i]+1 << " ";
	}
	else
		cout << "NO";
	return 0;
}
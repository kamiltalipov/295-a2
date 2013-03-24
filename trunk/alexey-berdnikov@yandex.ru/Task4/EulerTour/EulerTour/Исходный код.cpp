#include <cassert>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool find_Euler_tour(const vector<vector<unsigned>>& arcs, vector<unsigned>& list)
{
	unsigned n = arcs.size();
	vector<unsigned> index(n);
	vector<unsigned> stack(1);
	
	list.clear();
	while (stack[0] < n && !arcs[stack[0]].size()) ++stack[0];
	if (stack[0] == n) return true;

	vector<unsigned> balance(n);
	for (unsigned v = stack[0]; v < n; ++v) balance[v] = arcs[v].size();

	while (!stack.empty()) {
		unsigned v = stack.back();
		if (index[v] == arcs[v].size()) {
			stack.pop_back();
			list.push_back(v);
		}
		else {
			unsigned w = arcs[v][index[v]++];

			stack.push_back(w);
			--balance[w];
		}
	}

	for (unsigned v = 0; v < n; ++v) {
		if (balance[v]) {
			list.clear();
			return false;
		}
	}
	return true;
}

void check()
{
	unsigned n;
	cin >> n;

	vector<vector<unsigned>> arcs(n);
	for (unsigned i = 0; i < n; ++i) {
		unsigned k;
		cin >> k;
		
		arcs[i].resize(k);
		for (unsigned j = 0; j < k; ++j) {
			cin >> arcs[i][j];
			--arcs[i][j];
		}
	}

	vector<unsigned> list;
	bool success = find_Euler_tour(arcs,list);
	if (success)
		for (unsigned i = 0; i < n; ++i) cout << list[i]+1 << ' ';
	else
		cout << "Doesn't exist";
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	check();
	_CrtDumpMemoryLeaks();
	return 0;
}
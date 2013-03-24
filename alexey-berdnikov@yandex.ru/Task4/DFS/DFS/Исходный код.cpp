#include <cassert>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void DFS(const vector<vector<unsigned>>& arcs, unsigned i, vector<char>& colour, vector<unsigned>& list)
{
	assert(!colour[i]);

	vector<pair<unsigned, unsigned>> stack(1,make_pair(i,0));
	while (!stack.empty()) {
		unsigned i = stack.back().first;
		unsigned& j = stack.back().second;

		if (j != arcs[i].size()) {
			colour[i] = 1;
			unsigned v = arcs[i][j];
			if (colour[v] == 1) {
				cout << "Impossible";
				exit(0);
			}
			++j;
			if (!colour[v]) stack.push_back(make_pair(v,0));
		}
		else {
			colour[i] = 2;
			list.push_back(i);
			stack.pop_back();
		}
	}
}

void topological_sort(const vector<vector<unsigned>>& arcs, vector<unsigned>& list)
{
	unsigned n = arcs.size();
	vector<char> colour(n);

	list.clear();
	for (unsigned i = 0; i < n; ++i)
		if (!colour[i]) DFS(arcs,i,colour,list);
	reverse(list.begin(),list.end());
}

void check()
{
	unsigned n;
	cin >> n;

	vector<vector<unsigned>> arcs(n);
	for (unsigned i = 0; i < n; ++i) {
		int k;
		cin >> k;
		
		arcs[i].resize(k);
		for (unsigned j = 0; j < k; ++j) {
			cin >> arcs[i][j];
			--arcs[i][j];
		}
	}

	vector<unsigned> list;
	topological_sort(arcs,list);
	for (unsigned i = 0; i < n; ++i) cout << list[i]+1 << ' ';
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	check();
	_CrtDumpMemoryLeaks();
	return 0;
}
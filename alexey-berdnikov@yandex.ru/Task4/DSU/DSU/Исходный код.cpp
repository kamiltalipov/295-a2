#include <vector>
#include <iostream>
#include <cassert>

using namespace std;

class DSU {
	vector<unsigned> parent, rank;
	
public:
	DSU(unsigned n =0) : parent(n), rank(n)
	{
		for (unsigned i = 0; i < n; ++i) parent[i] = i;
	}
	unsigned make_set()
	{
		unsigned number = parent.size();
		
		parent.push_back(number);
		rank.push_back(0);
		return number;
	}
	unsigned link(unsigned x, unsigned y)
	{
		if (rank[x=find_set(x)] > rank[y=find_set(y)]) {
			parent[y] = x;
			return x;
		}
		parent[x] = y;
		if (rank[x] == rank[y]) ++rank[y];
		return y;
	}
	unsigned find_set(unsigned x)
	{
		return x==parent[x] ? x : parent[x]=find_set(parent[x]);
	}
};

int main()
{
	unsigned n;
	cin >> n;

	DSU graph(n);
	for (;;) {
		unsigned query;
		cin >> query;

		assert(query<=2);
		if (!query) return 0;

		unsigned u, v;
		cin >> u >> v;
		if (query == 1)
			graph.link(u-1,v-1);
		else
			cout << (graph.find_set(u-1)==graph.find_set(v-1)?"Yes":"No") << endl;
	}
}
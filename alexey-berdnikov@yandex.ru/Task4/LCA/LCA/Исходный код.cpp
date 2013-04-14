#include <iostream>
#include <vector>
using namespace std;

enum colour { WHITE, BLACK };

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

void DFS_visit(const vector<vector<unsigned>>& children, const vector<pair<unsigned, unsigned>>& pairs,
	const unsigned u, DSU& components, vector<unsigned>& ancestor, vector<colour>& colours, const vector<vector<unsigned>>& pairs_list,
	vector<unsigned>& result)
{
	ancestor[u] = u;
	for (unsigned i = 0; i < children[u].size(); ++i) {
		unsigned v = children[u][i];

		DFS_visit(children,pairs,v,components,ancestor,colours,pairs_list,result);
		components.link(u,v);
		ancestor[components.find_set(u)] = u;
	}
	colours[u] = BLACK;
	for (unsigned i = 0; i < pairs_list[u].size(); ++i) {
		unsigned k = pairs_list[u][i];
		result[k] = ancestor[components.find_set(u==pairs[k].first?pairs[k].second:pairs[k].first)];
	}
}

void LCA(const vector<vector<unsigned>>& children, const vector<pair<unsigned, unsigned>>& pairs,
	vector<unsigned>& result)
{
	unsigned n = children.size();
	DSU components(n);
	vector<unsigned> ancestor(n);
	vector<colour> colours(n);
	vector<vector<unsigned>> pairs_list(n);
	for (unsigned i = 0; i < pairs.size(); ++i) {
		unsigned u = pairs[i].first;
		unsigned v = pairs[i].second;
		pairs_list[u].push_back(i);
		pairs_list[v].push_back(i);
	}

	DFS_visit(children,pairs,0,components,ancestor,colours,pairs_list,result);
}

int main()
{
	unsigned n;
	cin >> n;

	vector<vector<unsigned>> children(n);
	for (unsigned i = 1; i < n; ++i) {
		unsigned u, v;
		cin >> u >> v;
		children[u-1].push_back(v-1);
	}

	unsigned m;
	cin >> m;

	vector<pair<unsigned, unsigned>> pairs(m);
	for (unsigned i = 0; i < m; ++i) {
		unsigned u, v;
		cin >> u >> v;
		pairs[i] = make_pair(u-1,v-1);
	}

	vector<unsigned> result(m);
	LCA(children,pairs,result);

	for (unsigned i = 0; i < m; ++i)
		cout << result[i]+1 << ' ';
	return 0;
}
#ifndef _DSU_H_
#define _DSU_H_

#include <vector>
using std :: vector;
#include <algorithm>
using std :: swap;

class DSU
{
public:
	DSU (size_t n)
		:
		forest (n)
	{
		for (size_t i = 0; i < n; ++i)
			forest[i] = DSU_node (i, i);
	}

	int find_set (int v);
	int get_ancestor (int v);
	void union_sets (int a, int b);

protected:
	struct DSU_node
	{
		int parent;
		unsigned int rank;
		int ancestor;

		DSU_node (int _parent = 0, int _ancestor = 0, unsigned int _rank = 0)
			:
			parent (_parent),
			rank (_rank),
			ancestor (_ancestor)
		{
		}
	};

	vector<DSU_node> forest;
};

int DSU :: find_set (int v)
{
	if (v == forest[v].parent)
		return v;
	return forest[v].parent = find_set (forest[v].parent);
}

int DSU :: get_ancestor (int v)
{
	return forest[find_set (v)].ancestor;
}

void DSU :: union_sets (int a, int b)
{
	a = find_set (a);
	b = find_set (b);
	const int new_ancestor = forest[a].ancestor;
	if (a != b)
	{
		if (forest[a].rank < forest[b].rank)
			swap (a, b);
		forest[b].parent = a;
		forest[a].ancestor = new_ancestor;
		if (forest[a].rank == forest[b].rank)
			++forest[a].rank;
	}
}

#endif // _DSU_H_

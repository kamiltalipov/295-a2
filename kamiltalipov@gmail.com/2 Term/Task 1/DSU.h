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
			forest[i] = DSU_node (i);
	}

	void make_set (int v);
	int find_set (int v);
	void union_sets (int a, int b);

protected:
	struct DSU_node
	{
		int parent;
		unsigned int rank;

		DSU_node (int _parent = 0, unsigned int _rank = 0)
			:
			parent (_parent),
			rank (_rank)
		{
		}
	};

	vector<DSU_node> forest;
};


void DSU :: make_set (int v)
{
	forest[v] = DSU_node (v);
}

int DSU :: find_set (int v)
{
	if (v == forest[v].parent)
		return v;
	return forest[v].parent = find_set (forest[v].parent);
}

void DSU :: union_sets (int a, int b)
{
	a = find_set (a);
	b = find_set (b);
	if (a != b)
	{
		if (forest[a].rank < forest[b].rank)
			swap (a, b);
		forest[b].parent = a;
		if (forest[a].rank == forest[b].rank)
			++forest[a].rank;
	}
}

#endif // _DSU_H_

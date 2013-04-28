#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class DSU
{
private:
	vector < int > st, acc, size;
public:
	DSU(int n) : st(vector < int > (n)), acc(vector < int >(n)), size(vector < int > (n, 1))
	{
		for (int i = 0; i < n; ++i)
			st[i] = acc[i] = n;
	}
	inline int get_acc(int v) { return acc[get_set(v)]; }
	inline void set_acc(int v, int accv) { acc[v] = accv; }
	inline int get_set(int v) { return st[v] == v ? v : st[v] = get_set(st[v]); }
	inline void unite(int a, int b, int ac)
	{
		a = get_set(a), b = get_set(b);
		if (size[a] < size[b])
			swap(a, b);
		size[a] += size[b];
		st[b] = a;
	}
};

struct node {
	int parent, weight;
	vector < int > chlds;
};

vector < node > tree;
vector < pair < int, pair < int, int > > > ntedges;
vector < int > base4tree, first4lcs, seg_tree;
vector < int > ans;

void dfs(int v)
{
	first4lcs[v] = base4tree.size();
	base4tree.push_back(v);
	for (int i = 0; i < tree[v].chlds.size(); ++i)
	{
		dfs(tree[v].chlds[i]);
		base4tree.push_back(v);
	}
}

inline int lch(int v) { return (v << 1) + 1; }
inline int rch(int v) { return (v << 1) + 2; }
int build_seg_tree(int v, int tl, int tr)
{
	if (tl + 1 == tr)
		return seg_tree[v] = base4tree[tl];
	const int tm = (tl + tr) >> 1;
	return seg_tree[v] = min(build_seg_tree(lch(v), tl, tm), build_seg_tree(rch(v), tm, tr));
}

int get_min(int v, int tl, int tr, int l, int r)
{
	if (tl == l && tr == r)
		return seg_tree[v];
	const int tm = (tl + tr) >> 1;
	if (l >= tm)
		return get_min(rch(v), tm, tr, l, r);
	if (r <= tm)
		return get_min(lch(v), tl, tm, l, r);
	return min(get_min(lch(v), tl, tm, l, tm), get_min(rch(v), tm, tr, tm, r));
}

inline int lcs(int a, int b)
{
	a = first4lcs[a], b = first4lcs[b];
	if (a > b)
		swap(a, b);
	return get_min(0, 0, seg_tree.size(), a, b + 1);
}

int mark(const int v, const int top, const int value, DSU &dsu)
{
	int cv = v, united = 0;
	while (dsu.get_acc(cv) != dsu.get_acc(cv))
	{
		ans[cv] = value;
		for (int i = 0; i < tree[cv].chlds.size(); ++i)
			if (ans[tree[cv].chlds[i]] != -1)
			{
				dsu.unite(cv, tree[cv].chlds[i], dsu.get_acc(cv));
				++united;
			}
		if (ans[tree[cv].parent] != -1)
		{
			dsu.unite(cv, tree[cv].parent, dsu.get_acc(tree[cv].parent));
			++united;
		}
		else
			dsu.set_acc(cv, tree[cv].parent);
		cv = dsu.get_acc(cv);
	}
	return united;
}

int main()
{
	int n, m;
	tree = vector < node >(n);
	ans.assign(n, -1);
	DSU dsu(n - 1);	
	const int NO_PARENT = -1;
	tree[0].parent = NO_PARENT;
	//Graph must be specialy described,
	//because I'm too lazy to rewrite LCS
	for (int i = 1; i < n; ++i)
	{
		int p, w;
		cin >> p >> w;
		tree[i].parent = p;
		tree[i].weight = w;
		tree[p].chlds.push_back(i);
	}
	first4lcs.resize(n);
	dfs(0);
	seg_tree.resize(n * 4);
	build_seg_tree(0, 0, base4tree.size());
	for (int i = 0; i < m; ++i)
	sort(ntedges.begin(), ntedges.end());
	int united = 0;
	ntedges.resize(m);
	for (int i = 0; i < m; ++i)
		cin >> ntedges[i].second.first >> ntedges[i].second.second >> ntedges[i].first;
	for (int i = 0; i < m && united < n - 1; ++i)
	{
		int a = ntedges[i].second.first, b = ntedges[i].second.second;
		int vlca = lcs(a, b);
		united += mark(a, vlca, i, dsu);
		united += mark(b, vlca, i, dsu);
	}
	//Output:
	for (int i = 1; i < n; ++i)
		cout << ans[i] << " ";
	return 0;
}

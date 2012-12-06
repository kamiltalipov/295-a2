#include <iostream>
#include <vector>
#include <limits.h>
#include <assert.h>
using namespace std;

class SegmentTree
{
	const unsigned int n;
	struct seg
	{
		int mn, add;
		static const int INF = INT_MAX;
		seg(int mn = INF, int add = 0) : mn(mn), add(add) {}
	};
	vector < seg > tree;
	int lch(int v) { return (v << 1) + 1; }
	int rch(int v) { return (v << 1) + 2; }
	int build(const vector < int > &arr, int v, int tl, int tr);
	void update(int v, int tl, int tr, int l, int r, int val);
	int get_min(int v, int tl, int tr, int l, int r, int add = 0);
public:
	SegmentTree(const vector < int >& arr) : n(arr.size()) { tree.resize(n << 2); build(arr, 0, 0, n); }
	unsigned int Size() { return n; }
	void Update(int val, int l, int r) { assert(l >= 0 && r >= l && r <= n); update(0, 0, n, l, r, val); }
	int GetMin(int l, int r) { assert(l >= 0 && r >= l && r <= n); return get_min(0, 0, n, l, r); }
};

int SegmentTree::build(const vector < int > &arr, int v, int tl, int tr)
{
	if (tl + 1 == tr)
		return (tree[v] = seg(arr[tl], 0)), arr[tl];
	const int tm = (tl + tr) >> 1;
	build(arr, lch(v), tl, tm), build(arr, rch(v), tm, tr);
	tree[v] = seg(min(tree[lch(v)].mn, tree[rch(v)].mn), 0);
	return tree[v].mn;
}

void SegmentTree::update(int v, int tl, int tr, int l, int r, int val)
{
	if (tl == l && tr == r)
		return void(tree[v].add += val);
	const int tm = (tl + tr) >> 1;
	if (l < tm)
		update(lch(v), tl, tm, l, min(tm, r), val);
	if (tm < r)
		update(rch(v), tm, tr, max(l, tm), r, val);
	tree[v].mn = min(tree[lch(v)].mn, tree[rch(v)].mn);
}

int SegmentTree::get_min(int v, int tl, int tr, int l, int r, int add)
{
	if (tl == l && tr == r)
		return tree[v].mn + tree[v].add + add;
	const int tm = (tl + tr) >> 1;
	int a = INT_MAX, b = INT_MAX;
	if (l < tm)
		a = get_min(lch(v), tl, tm, l, min(tm, r), add + tree[v].add);
	if (tm < r)
		b = get_min(rch(v), tm, tr, max(tm, l), r, add + tree[v].add);
	return min(a, b);
}

int main()
{
	vector < int > arr(5);
	SegmentTree st(arr);
	st.Update(-1, 2, 5);
	cout << st.GetMin(0, 2) << " " << st.GetMin(0, 3) << " " << st.GetMin(0, 4) << endl;
	system("pause");
	return 0;
}
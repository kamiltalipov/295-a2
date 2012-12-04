#include <iostream>
#include <assert.h>
using namespace std;

class DecartTree
{
	typedef int T;
	struct TreeNode;
	typedef TreeNode* pnode;
	struct TreeNode
	{
		static bool eq(const T& a, const T& b) { return !((a < b) || (b < a)); }
		static int mrand() { return (rand() << 15) | rand(); }
		static unsigned int nsize(pnode p) { return p ? p->size : 0; }
		T val;
		unsigned int y, size;
		pnode L, R, parent;
		pnode find(const T& fv) const;
		void update()
		{
			if (L) L->parent = this;
			if (R) R->parent = this;
			size = 1 + (L ? L->size : 0) + (R ? R->size : 0);
		}
		~TreeNode() { delete L; delete R; }
		TreeNode(const T& val, unsigned int y = mrand(), pnode par = NULL, pnode L = NULL, pnode R = NULL) :
			val(val), y(y), L(L), R(R), parent(par) { update(); }
		const T& nth(unsigned int n);
	} *root;
	DecartTree(const pnode& p) : root(p) { if (root) root->parent = NULL; }
	static pnode merge(pnode l, pnode r);
	static void split(pnode t, pnode& l, pnode& r, const T& sv);
public:
	DecartTree(T val) : root(new TreeNode(val)) {}
	~DecartTree() { delete root; }
	static DecartTree Merge(const DecartTree& l, const DecartTree& r) { return DecartTree(merge(l.root, r.root)); }
	static DecartTree Split(DecartTree root, DecartTree& l, DecartTree& r, const T& sv)
	{
		pnode pl, pr;
		split(root.root, pl, pr, sv);
		l = DecartTree(pl), r = DecartTree(pr);
	}
	void Add(const T& nv);
	bool Contain(const T& vl) const { return root && TreeNode::eq(vl, root->find(vl)->val); }
	void Remove(const T& vl);
	unsigned int Size() const { return TreeNode::nsize(root); }
	const T& nth_element(unsigned int n) { assert(n >= 0 && n < Size()); return root->nth(n); }
};

DecartTree::pnode DecartTree::TreeNode::find(const T& fv) const
{
	if (fv < val)
		return L ? L->find(fv) : const_cast < pnode > (this);
	else if (val < fv)
		return R ? R->find(fv) : const_cast < pnode > (this);
	else
		return const_cast < pnode > (this);
}

DecartTree::pnode DecartTree::merge(DecartTree::pnode l, DecartTree::pnode r)
{
	if (!l || !r)
		return l ? l : r;
	if (l->y > r->y)
	{
		l->R = merge(l->R, r);
		l->update();
		l->parent = NULL;
		return l;
	}
	else
	{
		r->L = merge(l, r->L);
		r->update();
		r->parent = NULL;
		return r;
	}
}

void DecartTree::split(DecartTree::pnode t, pnode& l, pnode& r, const T& sv)
{
	if (!t) return void(l = r = NULL);
	if (sv < t->val)
	{
		split(t->L, l, t->L, sv);
		r = t;
	}
	else
	{
		split(t->R, t->R, r, sv);
		l = t;
	}
	if (l) l->parent = NULL, l->update();
	if (r) r->parent = NULL, r->update();
}

void DecartTree::Add(const T& nv)
{
	if (!root) return void(root = new TreeNode(nv));
	unsigned int rang = TreeNode::mrand();
	if (rang >= root->y) // >= important, see q->y < rang
	{
		pnode t = new TreeNode(nv, rang);
		split(root, t->L, t->R, nv);
		t->update();
		root = t;
		return;
	}
	pnode q = root->find(nv);
	if (TreeNode::eq(q->val, nv)) return;
	while (q->y < rang)
		q = q->parent;
	if (nv < q->val)
	{
		pnode t = new TreeNode(nv, rang, q);
		split(q->L, t->L, t->R, nv);
		t->update();
		q->L = t;
	}
	else
	{
		pnode t = new TreeNode(nv, rang, q);
		split(q->R, t->L, t->R, nv);
		t->update();
		q->R = t;
	}
	while (q)
		q->update(), q = q->parent;
}

void DecartTree::Remove(const T& vl)
{
	if (!root) return;
	pnode p = root->find(vl);
	if (!TreeNode::eq(vl, p->val)) return;
	if (p == root)
		return void(root = merge(root->L, root->R));
	pnode q = p->parent;
	if (q->L == p)
		q->L = merge(p->L, p->R);
	else
		q->R = merge(p->L, p->R);
	while (q)
		q->update(), q = q->parent;
	p->L = p->R = NULL;
	delete p;
}

const DecartTree::T& DecartTree::TreeNode::nth(unsigned int n)
{
	if (nsize(L) == n)
		return val;
	if (nsize(L) > n)
		return L->nth(n);
	return R->nth(n - nsize(L) + 1);
}

int main()
{
	srand(7);
	DecartTree a(0);
	a.Remove(0);
	cout << a.Contain(0) << " " << a.Contain(1) << " " << a.Contain(-1) << " " << a.Size() << endl;
	a.Add(1);
	a.Add(10), a.Add(11);
	cout << a.Contain(0) << " " << a.Contain(1) << " " << a.Contain(-1) << " " << a.Size() << endl;
	a.Add(-2);
	cout << a.Contain(0) << " " << a.Contain(1) << " " << a.Contain(-1) << " " << a.Size() << endl;
	a.Remove(0);
	cout << a.Contain(0) << " " << a.Contain(1) << " " << a.Contain(-1) << " " << a.Size() << endl;
	a.Remove(1);
	cout << a.Contain(0) << " " << a.Contain(1) << " " << a.Contain(-1) << " " << a.Size() << endl;
	char c;
	cin >> c;
	return 0;
}
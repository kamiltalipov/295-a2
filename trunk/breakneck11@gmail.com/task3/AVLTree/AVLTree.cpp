#include <iostream>
using namespace std;

class BSTNode
{
protected:
	double val;
	BSTNode *L, *R, *parent;
	BSTNode* find(const double& fv)
	{
		if (!(val < fv) && !(fv < val))
			return this;
		if (fv < val)
			return L ? L->find(fv) : this;
		else
			return R ? R->find(fv) : this;
	}
	BSTNode(const double& val, BSTNode* L = NULL, BSTNode* R = NULL, BSTNode* parent = NULL) :
		val(val), L(L), R(R), parent(parent) {}
	virtual ~BSTNode() { delete L; delete R; }
};

class AVLTree
{
	class AVLNode;
	typedef AVLNode* pnode;
	class AVLNode : public BSTNode
	{
		unsigned int height;
		static pnode cast(BSTNode* p) { return static_cast < pnode > (p); }
		static unsigned int heightof(pnode p) { return p ? p->height : 0; }
		static unsigned int heightof(BSTNode* p) { return heightof(static_cast < pnode > (p)); }
		static void update(pnode p)
		{
			if (!p) return;
			p->height = 1 + max(heightof(p->L), heightof(p->R));
			if (p->L)
				cast(p->L)->parent = p;
			if (p->R)
				cast(p->R)->parent = p;
		}
		static int balanceof(pnode p) { return p ? heightof(p->L) - heightof(p->R) : 0; }
		static pnode rotale_right(pnode p);
		static pnode rotale_left(pnode p);
		static int balanceof(BSTNode* p) { return balanceof(cast(p)); }
		static pnode balance(pnode p);
		static pnode findmin(pnode p) { return p->L ? findmin(cast(p->L)) : p; }
		static pnode remove_min(pnode p) { return p->L ? cast(p->L = balance(remove_min(cast(p->L)))) : cast(p->R); }
	public:
		AVLNode(const double& val, pnode L = NULL, pnode R = NULL, pnode parent = NULL)
			: BSTNode(val, L, R, parent), height(1) {}
		static pnode add(pnode p, const double& val);
		static pnode remove(pnode p, const double& val);
		static pnode remove(BSTNode* p, const double& val) { return remove(cast(p), val); }
		static bool contain(pnode p, const double& val);
	} *root;
public:
	AVLTree(const double& val) : root(new AVLNode(val)) {}
	void Add(const double& val) { root = AVLNode::add(root, val); }
	void Remove(const double& val) { root = AVLNode::remove(root, val); }
	bool Contain(const double& val) { return AVLNode::contain(root, val); }
};

AVLTree::pnode AVLTree::AVLNode::rotale_right(pnode p)
{
	if (!p) return NULL;
	pnode q = cast(p->L);
	p->L = q->R;
	q->R = p;
	update(p);
	update(q);
	return q;
}

AVLTree::pnode AVLTree::AVLNode::rotale_left(AVLTree::pnode p)
{
	if (!p) return NULL;
	pnode q = cast(p->R);
	p->R = q->L;
	q->L = p;
	update(p);
	update(q);
	return q;
}

AVLTree::pnode AVLTree::AVLNode::balance(AVLTree::pnode p)
{
	update(p);
	if (!p) return NULL;
	if (balanceof(p) == 2)
	{
		if (balanceof(p->L) < 0)
			p->L = rotale_left(cast(p->L));
		p = rotale_right(cast(p));
	}
	else if (balanceof(p) == -2)
	{
		if (balanceof(p->R) > 0)
			p->R = rotale_right(cast(p->R));
		p = rotale_left(cast(p));
	}
	return p;
}

AVLTree::pnode AVLTree::AVLNode::add(AVLTree::pnode p, const double& val)
{
	if (!p)
		return new AVLNode(val);
	if (!(val < p->val) && !(p->val < val))
		return p;
	if (val < p->val)
		p->L = add(cast(p->L), val);
	else
		p->R = add(cast(p->R), val);
	balance(p);
	return p;
}

AVLTree::pnode AVLTree::AVLNode::remove(AVLTree::pnode p, const double& val)
{
	if (!p)
		return NULL;
	if (val < p->val)
	{
		p->L = remove(p->L, val);
		return balance(p);
	}
	if (p->val < val)
	{
		p->R = remove(p->R, val);
		return balance(p);
	}
	pnode res;
	if (!p->R)
		res = cast(p->L);
	else
	{
		res = findmin(cast(p->R));
		res->L = p->L, res->R = remove_min(cast(p->R));
		p->L = p->R = NULL;
		delete p;
	}
	return balance(res);
}

bool AVLTree::AVLNode::contain(AVLTree::pnode p, const double& val)
{
	if (!p)
		return false;
	if (val < p->val)
		return contain(cast(p->L), val);
	if (p->val < val)
		return contain(cast(p->R), val);
	return true;
}

int main()
{
	AVLTree t(.0);
	t.Add(1.);
	t.Add(-1.);
	cout << t.Contain(-1) << " " << t.Contain(0) << " " << t.Contain(1) << endl;
	t.Remove(1);
	cout << t.Contain(-1) << " " << t.Contain(0) << " " << t.Contain(1) << endl;
	t.Remove(0);
	cout << t.Contain(-1) << " " << t.Contain(0) << " " << t.Contain(1) << endl;
	t.Add(1);
	cout << t.Contain(-1) << " " << t.Contain(0) << " " << t.Contain(1) << endl;
	system("pause");
	return 0;
}
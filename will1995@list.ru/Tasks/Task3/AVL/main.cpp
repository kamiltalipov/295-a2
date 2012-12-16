#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

class Tree
{
public:
	struct Node;
	typedef unsigned int unint;
	struct Node
	{
		int val, depth;
		Node *l, *r, *par;

		void update()
		{
			if (this)
			{
				int ls, rs = 0;
				if (this->l)
				{
					ls = this->l->depth;
					this->l->par = this;
				}
				if (this->r)
				{
					rs = this->r->depth;
					this->r->par = this;
				}
				this->depth = 1 + max(ls, rs);
			}
		}

		Node (int val, Node *l, Node *r, Node* par): val(val), depth(1), l(l), r(r), par(par) { update(); };

		~Node()
		{
			delete (l);
			delete (r);
		}
	}; 
	Node *root;

	Tree ( int x ): root(new Node (x, NULL, NULL, NULL)) {};

	Node* Add( Node* v, int x );
	bool Find( int x );
	void Remove ( int x );
	//void Print();

private:
	Node *rotate_right( Node *p );
	Node *rotate_left( Node *p );
	int count_balance( Node *v ) 
	{
		if (v)
		{
			int b, l, r = 0;
			l = (v->l) ? v->l->depth : 0;
			r = (v->r) ? v->r->depth : 0;
			return l - r; 
		}
	}

	Node* balance( Node *p );
	Node* min( Node *v ) 
	{
		if ( v->l )
			return min( v->l );
		else
			return v;
	}

	Node *rem_min( Node *v );
};

bool Tree::Find ( int x )
{
	Node *tmp = root;
	while (tmp)
	{
		if ( x == tmp->val )
			return true;
		else
			if (x < tmp->val)
				tmp = tmp ->l;
			else
				tmp = tmp->r;
	}
	return false;
}

Tree::Node* Tree::rotate_right(Tree::Node *v)
{
	if (!v)
		return NULL;

	Node *p = v->par;

	bool flag;
	if (p)
		if (p->l == v)
			flag = true;
		else
			flag = false;
	p->update();

	Node *tmp = v->l;
	v->l = tmp->r;
	tmp->r = v;
	v->update();
	tmp->update();

	if (p)
	{
		if (flag)
			p->l = tmp;
		else
			p->r = tmp;
		p->update();
		return p;
	}
	else
	{
		tmp->par = (Node*)0;
		return tmp;
	}
}

Tree::Node* Tree::rotate_left(Tree::Node *v)
{
	if (!v)
		return NULL;

	Node *p = v->par;

	bool flag;
	if (p)
		if (p->l == v)
			flag = true;
		else
			flag = false;
	p->update();

	Node *tmp = v->r;
	v->r = tmp->l;
	tmp->l = v;
	v->update();
	tmp->update();

	if (p)
	{
		if (flag)
			p->l = tmp;
		else
			p->r = tmp;
		p->update();
		return p;
	}
	else
	{
		tmp->par = (Node*)0;
		return tmp;
	}
}

Tree::Node* Tree::balance(Tree::Node* v)
{
	v->update();
	int b = count_balance(v);
	if (b == 2)
	{
		if ( count_balance(v->l) < 0)
			v->l = rotate_left(v->l);
		v = rotate_right(v);
	}
	else if (b == -2)
	{
		if ( count_balance(v->r) < 0)
			v->r = rotate_right(v->r);
		v = rotate_left(v);
	}
	return v;
}

Tree::Node* Tree::Add(Tree::Node* v, int x)
{
	if ( !v )
		return new Node(x, NULL, NULL, NULL);
	if ( v->val > x )
		v->l = Add(v->l, x);
	else
		v->r = Add(v->r, x);
	return balance(v);
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int n, x;
	cin >> n;
	cin >> x;
	Tree tr(x);
	for(int i = 1; i < n; i++)
	{
		cin >> x;
		if (!tr.Find(x))
		{
			tr.Add(tr.root, x);
			while (tr.root->par)
				tr.root = tr.root->par;
		}
	}

	return 0;
}
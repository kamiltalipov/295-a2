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
		int depth;
		int val;
		Node *l, *r, *par;

		void update()
		{
			//if (this)
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
	Node* Find( int x );
	bool Remove ( int x );
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


Tree::Node* Tree::Find (  int x )
{
	Node *tmp = root;
	while (tmp)
	{
		if ( x == tmp->val )
			return tmp;
		else
			if (x < tmp->val)
				tmp = tmp ->l;
			else
				tmp = tmp->r;
	}
	return NULL;
}


 Tree::Node* Tree::rotate_right( Tree::Node *v)
{
	if (!v)
		return NULL;

	Node *p = v->par;

	bool flag;
	if (p)
	{
		if (p->l == v)
			flag = true;
		else
			flag = false;
		p->update();
	}

	Node *tmp = v->l;
	v->l = tmp->r;
	tmp->r = v;
	if (v)
		v->update();

	if (tmp)
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


 Tree::Node* Tree::rotate_left( Tree::Node *v)
{
	if (!v)
		return NULL;

	Node *p = v->par;

	bool flag;
	if (p)
	{
		if (p->l == v)
			flag = true;
		else
			flag = false;
		p->update();
	}

	Node *tmp = v->r;
	v->r = tmp->l;
	tmp->l = v;
	if (v)
		v->update();

	if (tmp)
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


 Tree::Node* Tree::balance( Tree::Node* v)
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


 Tree::Node* Tree::Add( Tree::Node* v, int x)
{
	if ( !v )
		return new Node(x, NULL, NULL, NULL);
	if ( v->val > x )
		v->l = Add(v->l, x);
	else
		v->r = Add(v->r, x);
	return balance(v);
}

 bool Tree::Remove( int x )
 {
	 Node *torem = Find(x);
	 if (!torem)
		 return false;

	 Node *p = torem->par;
	 bool isleft;
	 if (p)
		 if ((p->l) == torem)
			 isleft = true;
		 else
			 isleft = false;

	 Node *repl;
	 if ((!torem->l) && (!torem->r))
		 repl = (Node*)0;
	 else
		 if (!torem->l)
			 repl = torem->r;
		 else
			 if (!torem->r)
				 repl = torem->l;

	 if (!(torem->l && torem->r))
	 {
		 if (p)
		 {
			 if (isleft)
				 p->l = repl;
			 else
				 p->r = repl;
			delete torem;
			p->update();
			balance(p);
		 }
		 else
		 {
			 this->root = repl;
			 delete torem;
		 }
	 }
	 else
	 {
		 int bal = count_balance(torem);
		 Node *tmp;
		 if (bal > 0)
		 {
			 if (!torem->l->r)
			 {
				repl = torem->l;
				repl->r = torem->r;
				tmp = repl;
			 }
			 else
			 {
				 repl = torem->l->r;
				 while (repl->r)
					 repl = repl -> r;
			 
				Node *repl_par = repl->par;
				repl_par->r = repl->l;

				tmp = repl_par;
				repl->l = torem->l;
				repl->r = torem->r;
			 }
		 }
		 else
		 {
			 if (!torem->r->l)
			 {
				 repl = torem->r;
				 repl->l = torem->l;
				 tmp = repl;
			 }
			 else
			 {
				 repl = torem->r->l;
				 while (repl->l)
					 repl = repl -> l;
			 
				Node *repl_par = repl->par;
				repl_par->l = repl->r;

				tmp = repl_par;
				repl->r = torem->r;
				repl->l = torem->l;
			 }
		 }

		 if (p)
		 {
			 if (isleft)
				 p->l = repl;
			 else
				 p->r = repl;
			 delete torem;
		 }
		 else
		 {
			 root = repl;
			 delete torem;
		 }
		 balance(tmp);
	 }
 }

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int n, x;
	cin >> n;
	cin >> x;
	Tree tr(x);
	for(int i = 1; i <  n; i++)
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
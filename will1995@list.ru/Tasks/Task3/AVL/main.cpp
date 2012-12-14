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
			int ls, rs = 0;
			if (l)
			{
				l->par = this;
				ls = l->depth;
			}
			if (r)
			{
				r->par = this;
				rs = r->depth;
			}
			depth = 1 + max(ls, rs);
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

	void Add( int x );
	void Remove ( int x );
	//void Print();

private:
	Node *rotate_right( Node *p );
	Node *rotate_left( Node *p);
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

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	return 0;
}
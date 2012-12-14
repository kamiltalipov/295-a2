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
				depth = 1;
			if (l)
			{
				l->par = this;
				depth += l->depth;
			}
			if (r)
			{
				r->par = this;
				depth += r->depth;
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

	void Add();
	void Remove();
	void Print();

private:
	Node *rotate_right();
	Node *rotate_left();
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

	Node* balance();
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
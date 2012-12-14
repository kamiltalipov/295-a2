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

		Node (int val, Node *l, Node *r, Node* par): val(val), depth(1), l(l), r(r), par(par) {};

		~Node()
		{
			delete (l);
			delete (r);
		}
	};
};

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	return 0;
}
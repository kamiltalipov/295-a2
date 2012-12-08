#include <iostream>
#include <stdio.h>
#include <ctime>
#include <fstream>
#include <vector>

class Treap
{
public:
	struct Node;
	typedef unsigned int unint;
	typedef Node* ptrnode;
	struct Node
	{
		unint key, size;
		int data;
		Node *l, *r, *par;

		bool operator == (ptrnode a)
		{
			return (this->data == a->data) && (this->key == a->key); //I hope they wouldn't have the same keys...
		}

		void update()
		{
			if (l) 
			{
				l->par = this;
				size += l->size;
			};
			if (r) 
			{
				r->par = this;
				size += r->size;
			};
		}

		Node (int x, int y, ptrnode l, ptrnode r,  ptrnode par): data(x), key(y), l(l), r(r), par(par) 
		{
			size = 1;
			update();
		};

		~Node() 
		{ 
			delete (l); 
			delete (r); 
		};
	};
	ptrnode root;

	Treap( int x ): root (new Node(x, (rand() << 15 + rand()), NULL, NULL, NULL)) {};

	void Add( int x );
	void Remove( int x );
	void split( int x, ptrnode nw, ptrnode &l, ptrnode &r );

	int kth ( int k );

	ptrnode merge( ptrnode l, ptrnode r );

	ptrnode Find( int x );
	ptrnode Next( int x );
	ptrnode Prev( int x );

	unint size( Treap &t ) { return t.root->size ;};
};

void Treap::split ( int x, ptrnode t, ptrnode &l, ptrnode &r )
{
	if (!t)
	{
		l = NULL;
		r = NULL;
		exit;
	}

	if (x < t->data)
	{
		split( x, t->l, l, t->l );
		r = t;
	}
	else
	{
		split( x, t->r, t->r, r );
		l = t;
	}
	if (l) { l->update (); };
	if (r) { r->update (); };
}

Treap::ptrnode Treap::merge (ptrnode l, ptrnode r)
{
    if (l == NULL) return r;
    if (r == NULL) return l;
    if (l->key > r->key) {
       l->r = merge(l->r, r);
       return l;
    } else {
       r->l = merge(l, r->l);
       return r;
    }
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	Treap x( 3 );

	fclose(stdin);
	fclose(stdout);
	return 0;
}
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
	//typedef Node* Node*;
	struct Node
	{
		unint key, size;
		int data;
		Node *l, *r, *par;

		bool operator == (Node* a)
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

		Node (int x, int y, Node* l, Node* r,  Node* par): data(x), key(y), l(l), r(r), par(par) 
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
	Node* root;

	Treap( int x ): root (new Node(x, (rand() << 15 + rand()), NULL, NULL, NULL)) {};

	void Add( int x );
	void Remove( int x );
	void split( int x, Node* nw, Node* &l, Node* &r );

	int kth ( int k );

	Node* merge( Node* l, Node* r );

	Node* Find( int x, Node* t );
	Node* Next( int x );
	Node* Prev( int x );

	unint size( Treap &t ) { return t.root->size ;};
};

void Treap::split ( int x, Node* t, Node* &l, Node* &r )
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

Treap::Node* Treap::merge (Node* l, Node* r)
{
    if (l == NULL) 
		return r;

    if (r == NULL) 
		return l;

    if (l->key > r->key) 
	{
		l->r = merge(l->r, r);
		return l;
    } 
	else 
	{
		r->l = merge(l, r->l);
		return r;
    }
}

Treap::Node* Treap::Find( int x, Node* t )
{
	if (t == NULL) 
		return NULL;

	if (x < t->data)
		return Find(x, t->l);

	if (x > t->data)
		return Find(x, t->r);

	return t;
}

void Treap::Add( int x )
{
	if (!root)
	{
		root = new Node( x, rand() << 15 + rand(), NULL, NULL, NULL );
		root->update();
		return;
	}

	unint nk = rand() << 15 + rand();

	if (nk >= root->key)
	{
		Node* tmp = new Node(x, nk, NULL, NULL, NULL);
		split(x, root, tmp->l, tmp->r);
		tmp->update();
		root = tmp;
		return;
	}

	Node* tmp = Find(x, root);
	if (tmp)
	{
		if (nk > tmp->key)
		{

		}
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
#include <iostream>
#include <stdio.h>
#include <ctime>
#include <vector>

using namespace std;

class Treap
{
public:
	struct Node;
	typedef unsigned int unint;
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
			if (this)
			{
				this->size = 1;
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
		return;
	}

	if (x <= t->data)
	{
		split( x, t->l, l, t->l );
		r = t;
	}
	else
	{
		split( x, t->r, t->r, r );
		l = t;
	}
	if (l) { l->par = NULL, l->update (); };
	if (r) { r->par = NULL, r->update (); };
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

Treap::Node* Treap::Next( int x )
{
	Node *tmp = new Node(0, 0, NULL, NULL, NULL);
	tmp = Find( x, root );
	if (tmp)
	{
		if (tmp->r)
		{
			tmp = tmp->r;
			while (tmp->l)
				tmp = tmp->l;
		}
		else
		{
			while (tmp->par && (tmp->par->l != tmp))
				tmp = tmp->par;
			if (tmp->par)
				tmp = tmp->par;
			else
				return NULL;
				//if ((!tmp->par->l) || (tmp->par->l != tmp))
					//return NULL;
		}
	}
	else
		return NULL;
	return tmp;
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

	Node* tmp = Find(x, root);

	if (!tmp)
	{
		Node* l = new Node(0, 0, NULL, NULL, NULL);
		Node* r = new Node(0, 0, NULL, NULL, NULL);
		Node* nw = new Node(0, 0, NULL, NULL, NULL);

		split(x, root, l, r);
		root->update();
		l->update();
		r->update();

		split(x + 1, r, nw, r);
		r->update();
		nw->update();

		if (!nw)
		{
			nw = new Node(x, nk, NULL, NULL, NULL);
		}
		nw = merge(l, nw);
		nw->update();
		root = merge(nw, r);
		root->update();
	}
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n, x;
	cin >> n;
	cin >> x;
	Treap tr(x);
	for(int i = 1; i < n; i++)
	{
		cin >> x;
		tr.Add(x);
	}


	Treap::Node* nx = new Treap::Node(0, 0, NULL, NULL, NULL);
	nx = tr.Next(3);
	if (nx)
		cout << nx->data << endl;
	else
		cout << "-1" << endl;
	fclose(stdin);
	fclose(stdout);
	return 0;
}
#include <iostream>
#include <stdio.h>
#include <ctime>
#include <vector>

using namespace std;

template <class T>

class Treap
{
public:
	struct Node;
	typedef unsigned int unint;
	struct Node
	{
		unint key, size;
		T data;
		Node *l, *r, *par;

		bool operator == (Node* a)
		{
			return (this->data == a->data) && (this->key == a->key); //I hope they wouldn't have the same keys...
		}

		void update()
		{
			//if (this)
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

		Node (T x, int y, Node* l, Node* r,  Node* par): data(x), key(y), l(l), r(r), par(par) 
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
	Node *root;

	Treap( T x ): root (new Node(x, (rand() << 15 + rand()), NULL, NULL, NULL)) {};

	void Add( T x );
	void Remove( T x );
	void split( T x, Node* nw, Node* &l, Node* &r );

	int kth ( int k );

	Node* merge( Node* l, Node* r );

	Node* Find( T x, Node* t );
	Node* Next( T x );
	Node* Prev( T x );

	unint size( Treap &t ) { return t.root->size ;};
};

template <class T>
void Treap<T>::split( T x, Node* t, Node* &l, Node* &r )
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

template <class T>
typename Treap<T>::Node* Treap<T>::merge(typename Treap<T>::Node* l, typename  Treap<T>::Node* r)
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

template <class T>
typename Treap<T>::Node* Treap<T>::Find( T x, typename Node* t )
{
	if (t == NULL) 
		return NULL;

	if (x < t->data)
		return Find(x, t->l);

	if (x > t->data)
		return Find(x, t->r);

	return t;
}

template <class T>
typename Treap<T>::Node* Treap<T>::Next( T x )
{
	Node *tmp;// = new Node(0, 0, NULL, NULL, NULL);
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
		}
	}
	else
		return NULL;
	return tmp;
}

template <class T>
typename Treap<T>::Node* Treap<T>::Prev( T x )
{
	Node *tmp;// = new Node(0, 0, NULL, NULL, NULL);
	tmp = Find( x, root );
	if (tmp)
	{
		if (tmp->l)
		{
			tmp = tmp->l;
			while (tmp->r)
				tmp = tmp->r;
		}
		else
		{
			while (tmp->par && (tmp->par->r != tmp))
				tmp = tmp->par;
			if (tmp->par)
				tmp = tmp->par;
			else
				return NULL;
		}
	}
	else
		return NULL;
	return tmp;
}

template <class T>
void Treap<T>::Add( T x )
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
		Node* l;// = new Node(0, 0, NULL, NULL, NULL);
		Node* r;// = new Node(0, 0, NULL, NULL, NULL);
		Node* nw;// = new Node(0, 0, NULL, NULL, NULL);

		split(x, root, l, r);
		if (root)
			root->update();

		if (l)
			l->update();

		if (r)
			r->update();

		split(x + 1, r, nw, r);
		if (r)
			r->update();

		if (nw)
			nw->update();

		if (!nw)
		{
			nw;// = new Node(x, nk, NULL, NULL, NULL);
		}
		nw = merge(l, nw);
		if (nw)
			nw->update();
		root = merge(nw, r);
		if (root)
			root->update();
	}
}

template <class T>
int Treap<T>::kth ( int k )
{
	Node* fn = this->root;

	while (fn->size != 1)
	{
		if ((fn->l) && (fn->l->size > (k - 1)))
		{
			fn = fn->l;
		}
		else
			if ((fn->r) && (fn->l->size < (k - 1)))
				fn = fn->r;
			else
				return fn->data;
	}
	return fn->data;
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n, x;
	cin >> n;
	cin >> x;
	Treap<int> tr(x);
	for(int i = 1; i < n; i++)
	{
		cin >> x;
		tr.Add(x);
	}


	Treap<int>::Node* nx;// = new Treap<int>::Node(0, 0, NULL, NULL, NULL);
	nx = tr.Prev(1);
	if (nx)
		cout << nx->data << endl;
	else
		cout << "-1" << endl;

	cout << tr.kth(3) << endl;

	/*cin >> n;
	int y = 0;
	char op, prop;
	cin >> op;
	while ( op == '?')
	{
		cin >> x;
		cout << "-1" << endl;
		n--;
		cin >> op;
		y = -1;
	}
	prop = op;
	cin >> x;
	Treap tr( (x + y) % 1000000000 );

	while (n != 0)
	{
		cin >> op >> x;
		if (op == '+')
		{
			if (prop == '?')
				tr.Add((x + y) % 1000000000);
			else
				tr.Add(x);
		}
		else
		{
			Treap::Node* fn = tr.Find(x, tr.root);
			if (!fn)
				fn = tr.Next(x);
			if (fn)
				y = fn->data;
			else
				y = -1;
			cout << y << endl;
		}
		n--;
	}*/

	fclose(stdin);
	fclose(stdout);
	return 0;
}
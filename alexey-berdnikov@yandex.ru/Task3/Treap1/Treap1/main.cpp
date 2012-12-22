#include <iostream>
#include <cmath>
#include <cassert>
using namespace std;

template<class T> class BST_node
{
protected:
	T key;
	BST_node<T>* left, *right, *p;
	
	static T get_key(BST_node<T>* x) { return x->key; }
	static BST_node<T>*& get_left(BST_node<T>* x) { return x->left; }
	static BST_node<T>*& get_right(BST_node<T>* x) { return x->right; }
	static BST_node<T>*& get_p(BST_node<T>* x) { return x->p; }
	void replace(BST_node<T>* other) // Вставляет *other в дерево вместо *this.
	{
		p = other->p;
		if (p)
			if (other == p->left)
				p->left = this;
			else
				p->right = this;
		left = other->left;
		if (left) left->p = this;
		right = other->right;
		if (right) right->p = this;
	}
	BST_node<T>* insert(BST_node<T>* z)
	{
		BST_node<T>* x = this;
		BST_node<T>* y = 0;
		T value = z->key;
		while (x) {
			y = x;
			x = x->key<value ? x->right : x->left;
		}
		z->p = y;
		if (!y) return z;
		if (y->key < value)
			y->right = z;
		else
			y->left = z;
		return z;
	}
	BST_node<T>* erase(BST_node<T>* to_delete, BST_node<T>*& p)
	{
		BST_node<T>* new_root = this;
		BST_node<T>* y = to_delete;
		if (y->left && y->right)
			y = y->next();
		p = y->p;
		BST_node<T>* x = y->left ? y->left : y->right;
		if (x) x->p = p;
		if (y == this)
			new_root = x;
		else {
			if (to_delete == this) new_root = y;
			if (y == p->left)
				p->left = x;
			else
				p->right = x;
		}
		if (y != to_delete) y->replace(to_delete);
		to_delete->p = to_delete->left = to_delete->right = 0;
		return new_root;
	}

public:
	BST_node(const T& value) : key(value), left(0), right(0), p(0) {}
	T value() { return key; }
	const BST_node<T>* find(const T& value) const
	{
		const BST_node* x = this;
		while (x && !(x->key==value))
			x = x->key<value ? x->right : x->left;
		return x;
	}
	BST_node<T>* find(const T& value)
	{
		BST_node* x = this;
		while (x && !(x->key==value))
			x = x->key<value ? x->right : x->left;
		return x;
	}
	BST_node<T>* insert(const T& value) { return insert(new BST_node<T>(value)); }
	BST_node<T>* erase(BST_node* to_delete)
	{
		BST_node<T>* p;
		return erase(to_delete,p);
	}
	const BST_node<T>* next() const
	{
		if (right) {
			const BST_node<T>* x = right;
			while (x->left)
				x = x->left;
			return x;
		}
		const BST_node<T>* x = this;
		const BST_node<T>* y = p;
		while (y && y->right == x) {
			x = y;
			y = y->p;
		}
		return y;
	}
	BST_node<T>* next()
	{
		if (right) {
			BST_node<T>* x = right;
			while (x->left)
				x = x->left;
			return x;
		}
		const BST_node<T>* x = this;
		BST_node<T>* y = p;
		while (y && y->right == x) {
			x = y;
			y = y->p;
		}
		return y;
	}
	const BST_node<T>* prev() const
	{
		if (left) {
			const BST_node<T>* x = left;
			while (x->right)
				x = x->right;
			return x;
		}
		const BST_node<T>* x = this;
		const BST_node<T>* y = p;
		while (y && y->left == x) {
			x = y;
			y = y->p;
		}
		return y;
	}
	BST_node<T>* prev()
	{
		if (left) {
			BST_node<T>* x = left;
			while (x->right)
				x = x->right;
			return x;
		}
		const BST_node<T>* x = this;
		BST_node<T>* y = p;
		while (y && y->left == x) {
			x = y;
			y = y->p;
		}
		return y;
	}
};

template<class T> class treap_node : public BST_node<T>
{
	int y;
	unsigned size;

	static unsigned get_size(BST_node<T>* x) { return x ? static_cast<treap_node<T>*>(x)->size : 0; }
	void recalc()
	{
		if (!this) return;
		size = get_size(left)+get_size(right)+1;
	}

public:
	treap_node(const T& value) : BST_node(value), y(rand()<<15|rand()), size(1) {}
	~treap_node()
	{
		delete static_cast<treap_node<T>*>(left);
		delete static_cast<treap_node<T>*>(right);
	}
	const treap_node<T>* find(const T& value) const { return static_cast<const treap_node<T>*>(BST_node::find(value)); }
	treap_node<T>* find(const T& value) { return static_cast<treap_node<T>*>(BST_node::find(value)); }
	static treap_node<T>* merge(treap_node<T>* left, treap_node<T>* right)
	{
		if (!left) return right;
		if (!right) return left;

		treap_node<T>* root;
		if (left->y >= right->y) {
			root = left;
			treap_node<T>* new_right = merge(static_cast<treap_node<T>*>(get_right(root)),right);
			get_right(root) = new_right;
			if (new_right) get_p(new_right) = root;
		}
		else
		{
			root = right;
			treap_node<T>* new_left = merge(left,static_cast<treap_node<T>*>(get_left(root)));
			get_left(root) = new_left;
			if (new_left) get_p(new_left) = root;
		}
		root->recalc();
		return root;
	}
	void split(const T& x, treap_node<T>*& left_root, treap_node<T>*& right_root)
	{
		if (!this) {
			right_root = left_root = 0;
			return;
		}
		if (x < key) {
			right_root = this;
			treap_node<T>* new_left;
			static_cast<treap_node<T>*>(left)->split(x,left_root,new_left);
			left = new_left;
			if (new_left) get_p(new_left) = this;
		}
		else {
			left_root = this;
			treap_node<T>* new_right;
			static_cast<treap_node<T>*>(right)->split(x,new_right,right_root);
			right = new_right;
			if (new_right) get_p(new_right) = this;
		}
		right_root->recalc();
		left_root->recalc();
	}
	treap_node<T>* insert(const T& value)
	{
		treap_node<T>* left_root, *right_root;
		split(value,left_root,right_root);
		return merge(merge(left_root,new treap_node(value)),right_root);
	}
	treap_node<T>* erase(const T& to_delete)
	{
		BST_node<T>* x = this;
		T split_key;
		while(x)
			if (BST_node::get_key(x) < to_delete) {
				split_key = max(split_key,BST_node::get_key(x));
				x = get_right(x);
			}
			else
				x = get_left(x);
		treap_node<T>* left_root, *middle_root, *right_root1, *right_root;
		split(split_key,left_root,right_root1);
		right_root1->split(to_delete,middle_root,right_root);
		delete middle_root;
		return merge(left_root,right_root);
	}
	const treap_node<T>* next() const { return static_cast<const treap_node<T>*>(BST_node::next()); }
	treap_node<T>* next() { return static_cast<treap_node<T>*>(BST_node::next()); }
	const treap_node<T>* prev() const { return static_cast<const treap_node<T>*>(BST_node::prev()); }
	treap_node<T>* prev() { return static_cast<treap_node<T>*>(BST_node::prev()); }
	treap_node<T>* nth_element(unsigned k)
	{
		if (k >= size) return 0;

		if (k < get_size(left))
			return static_cast<treap_node<T>*>(left)->nth_element(k);
		else if (k == get_size(left))
			return this;
		else
			return static_cast<treap_node<T>*>(right)->nth_element(k-get_size(left)-1);
	}
	T get_key()	{ return key; }
};

void check()
{
	treap_node<int>* root = 0;
	root = root->insert(15);
	root = root->insert(6);
	root = root->insert(18);
	root = root->insert(7);
	root = root->insert(13);
	root = root->insert(9);
	root = root->insert(3);
	root = root->insert(4);
	root = root->insert(20);
	root = root->insert(17);
	root = root->insert(2);
	for (treap_node<int>* x = root->find(20); x; x = x->prev())
		cout << x->value() /*<< ' ' << x->y*/ << '\n';
	for (int i = 0; i < 11; ++i) cout << root->nth_element(i)->get_key() << ' ';
	cout << '\n';
	root = root->erase(15);
	root = root->erase(6);
	root = root->erase(18);
	root = root->erase(7);
	root = root->erase(13);
	for (BST_node<int>* x = root->find(2); x; x = x->next())
		cout << x->value()<< ' ';
	root = root->erase(2);
	root = root->erase(9);
	root = root->erase(3);
	root = root->erase(4);
	root = root->erase(20);
	root = root->erase(17);
}

int main()
{
	check();
	_CrtDumpMemoryLeaks();
	return 0;
}
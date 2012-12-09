#include <iostream>
#include <cstdlib>
#include <cassert>
#include <crtdbg.h>
using namespace std;

template <class T> class BSTnode;

template <class T> class BSTnode {
	template <class T> friend class TreapNode;
protected:
	BSTnode* min();
	BSTnode* max();
	BSTnode* parent;
	BSTnode* left;
	BSTnode* right;
	T key;
public:
	T getKey() {
		return key;
	}
	BSTnode* find(T& val);
	BSTnode* next();
	BSTnode* prev();
	BSTnode(T& val) {
		key = val;
		parent = left = right = 0;
	}
	~BSTnode() {
		delete left;
		delete right;
		if (parent != 0) {
			if (this == parent->left) {
				parent->left = 0;
			} else {
				parent->right = 0;
			}
		} 
	}
};

template <class T> BSTnode<T>* BSTnode<T>::find(T& val) {
	BSTnode* curr = this;
	while ((curr != 0) && !(curr->key == val)) {
		if (val < curr->key) {
			curr = curr->left;
		} else {
			curr = curr->right;
		}
	}
	return curr;
}

template <class T> BSTnode<T>* BSTnode<T>::min() {
	BSTnode<T>* curr = this;
	if (curr == 0) return 0;
	while (curr->left != 0) curr = curr->left;
	return curr;
}

template <class T> BSTnode<T>* BSTnode<T>::max() {
	BSTnode<T>* curr = this;
	if (curr == 0) return 0;
	while (curr->right != 0) curr = curr->right;
	return curr;
}

template <class T> BSTnode<T>* BSTnode<T>::next() {
	if (right != 0) {
		return right->min();
	}
	BSTnode<T>* curr1 = this;
	BSTnode<T>* curr2 = parent;
	while ((curr2 != 0) && (curr2->right == curr1)) {
		curr1 = curr2;
		curr2 = curr2->parent;
	}
	return curr2;
}

template <class T> BSTnode<T>* BSTnode<T>::prev() {
	if (left != 0) {
		return left->max();
	}
	BSTnode<T>* curr1 = this;
	BSTnode<T>* curr2 = parent;
	while ((curr2 != 0) && (curr2->left == curr1)) {
		curr1 = curr2;
		curr2 = curr2->parent;
	}
	return curr2;
}

template <class T> class TreapNode;

template <class T> class TreapNode: public BSTnode<T> {
	template <class T> friend class Treap;
private:
	int prior;
	int size;
	static TreapNode<T>* merge(TreapNode<T>* smallKeys, TreapNode<T>* bigKeys);
	static void split(TreapNode* curr, TreapNode<T>*& l, TreapNode<T>*& r,  T val);
	int getSize();
	void update();
public:
	TreapNode(T& val) : BSTnode(val) {
		TreapNode::prior = rand();
		left = right = 0;
		size = 1;
	}
	TreapNode<T>* findVal(T& val) {
		return static_cast<TreapNode<T>*>(find(val));
	}
	TreapNode<T>* Successor() {
		return static_cast<TreapNode<T>*>(next()); 
	}
	TreapNode<T>* Predecessor() {
		return static_cast<TreapNode<T>*>(prev()); 
	}
};

template <class T> int TreapNode<T>::getSize() {
	if (this == 0) return 0;
	return size;
}

template <class T> void TreapNode<T>::update() {
	if (this == 0) return;
	size = static_cast<TreapNode<T>*>(left)->getSize() + static_cast<TreapNode<T>*>(right)->getSize() + 1;
	
}

template <class T> TreapNode<T>* TreapNode<T>::merge(TreapNode<T>* smallKeys, TreapNode<T>* bigKeys) {
	if (smallKeys == 0) return bigKeys;
	if (bigKeys == 0) return smallKeys;
	if (smallKeys->prior > bigKeys->prior) {
		smallKeys->right = merge(static_cast <TreapNode<T>*>(smallKeys->right), bigKeys);
		smallKeys->update();
		smallKeys->right->parent = smallKeys;
		return smallKeys;
	} else {
		bigKeys->left = merge(smallKeys, static_cast <TreapNode<T>*>(bigKeys->left));
		bigKeys->update();
		bigKeys->left->parent = bigKeys;
		return bigKeys;
	}
}

template <class T> void TreapNode<T>::split(TreapNode* curr, TreapNode<T>*& l, TreapNode<T>*& r,  T val) {
	if (curr == 0) {
		l = r = 0;
		return;
	}
	if (val < curr->key) {
		TreapNode<T>* leftCast = static_cast<TreapNode<T>*>(curr->left);
		split(leftCast, l, leftCast, val);
		curr->left = leftCast;
		r = curr;
		r->update();
	} else {
		TreapNode<T>* rightCast = static_cast<TreapNode<T>*>(curr->right);
		split(rightCast, rightCast, r, val);
		curr->right = rightCast;
		l = curr;
		l->update();
	}
	if (curr->left != 0) {
		curr->left->parent = curr;
	} 
	if (curr->right != 0) {
		curr->right->parent = curr;
	} 
}

template <class T> class Treap {
private:
	TreapNode<T>* root;
public:
	Treap(T& val) {
		root = new TreapNode<T>(val);
	}
	~Treap() {
		delete root;
	}
	TreapNode<T>* find(T& val) {
		return root->findVal(val); 
	}
	void insert(T& val);
	void Delete(T& val);
	void iterate();
	T kth_element(int k);
};

template <class T> void Treap<T>::insert(T& val) {
	TreapNode<T>* l = 0;
	TreapNode<T>* r = 0;
	TreapNode<T>* added = new TreapNode<T>(val);
	TreapNode<T>::split(root, l, r, val);
	root = TreapNode<T>::merge(TreapNode<T>::merge(l, added), r);
}

template <class T> void Treap<T>::Delete(T &val) {
	TreapNode<T>* toDel = find(val);
	if (toDel == 0) return;
	else {
		TreapNode<T>* Parent = static_cast<TreapNode<T>*>(toDel->parent);
		TreapNode<T>* l = static_cast<TreapNode<T>*>(toDel->left);
		TreapNode<T>* r = static_cast<TreapNode<T>*>(toDel->right);
		bool isLeft;
		if (Parent != 0) Parent->left == toDel;
		TreapNode<T>* merged = TreapNode<T>::merge(l, r);
		toDel->left = 0;
		toDel->right = 0;
		delete toDel;
		if (merged != 0) merged->parent = Parent;
		if (Parent != 0) {
			if (isLeft) {
				Parent->left = merged;
			} else {
				Parent->right = merged;
			}
		} else {
			root = merged;
		}
	}
}

template <class T> T Treap<T>::kth_element(int k) {
	assert(k <= root->getSize());
	assert(k > 0);
	TreapNode<T>* curr = root;
	while (k != static_cast<TreapNode<T>*>(curr->left)->getSize() + 1) {
		if (k  <= static_cast<TreapNode<T>*>(curr->left)->getSize()) curr = static_cast<TreapNode<T>*>(curr->left);
		else {
			k -= (static_cast<TreapNode<T>*>(curr->left)->getSize() + 1);
			curr = static_cast<TreapNode<T>*>(curr->right);
		}
	}
	return curr->getKey();
}
template <class T> void Treap<T>::iterate() {
	TreapNode<int>* curr = static_cast<TreapNode<int>*>(root->min());
	while (curr != 0) {
		cout << curr->getKey() << " ";
		curr = static_cast<TreapNode<int>*>(curr->next());
	}
}

int main() {
	freopen("input.txt", "r", stdin); 
	srand(1357);
	int n, i;
	int a;
	cin >> n;
	cin >> a;
	Treap<int>* treap =  new Treap<int>(a);
	for (i = 1;i < n;i++) {
		cin >> a;
		treap->insert(a);
	}
	cin >> a;
	cout << treap->kth_element(a) << endl;
	delete treap;
	_CrtDumpMemoryLeaks();
	return 0;
}
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <crtdbg.h>
#include <vector>
#include <algorithm>
using namespace std;

template <class T> class BSTnode;

template <class T> class BSTnode {
	template <class T> friend class AVLnode;
protected:
	BSTnode* getMin();
	BSTnode* getMax();
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

template <class T> BSTnode<T>* BSTnode<T>::getMin() {
	BSTnode<T>* curr = this;
	if (curr == 0) return 0;
	while (curr->left != 0) curr = curr->left;
	return curr;
}

template <class T> BSTnode<T>* BSTnode<T>::getMax() {
	BSTnode<T>* curr = this;
	if (curr == 0) return 0;
	while (curr->right != 0) curr = curr->right;
	return curr;
}

template <class T> BSTnode<T>* BSTnode<T>::next() {
	if (right != 0) {
		return right->getMin();
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
		return left->getMax();
	}
	BSTnode<T>* curr1 = this;
	BSTnode<T>* curr2 = parent;
	while ((curr2 != 0) && (curr2->left == curr1)) {
		curr1 = curr2;
		curr2 = curr2->parent;
	}
	return curr2;
}

template <class T> class AVLnode: public BSTnode<T> {
	template <class T> friend class AVLtree;
private:
	int height;
	int getHeight();
	int balance();
	void updateHeight();
	void updateParent(AVLnode<T>* newParent);
	AVLnode<T>* rotate_right();
	AVLnode<T>* rotate_left();
	AVLnode<T>* fixBalance();
public:
	AVLnode(T& val) : BSTnode(val) {
		height = 1;
	}
	AVLnode<T>* findVal(T& val) {
		return static_cast<AVLnode<T>*>(find(val));
	}
	AVLnode<T>* Successor() {
		return static_cast<AVLnode<T>*>(next()); 
	}
	AVLnode<T>* Predecessor() {
		return static_cast<AVLnode<T>*>(prev()); 
	}
};

template <class T> int AVLnode<T>::getHeight() {
	if (this == 0) return 0;
	return height;
}

template <class T> void AVLnode<T>::updateHeight() {
	if (this == 0) return;
	height = max(static_cast<AVLnode<T>*>(left)->getHeight(),  static_cast<AVLnode<T>*>(right)->getHeight()) + 1;
	
}

template <class T> void AVLnode<T>::updateParent(AVLnode<T>* newParent) {
	if (this == 0) return;
	parent = newParent;
}

template <class T> int AVLnode<T>::balance() {
	if (this == 0) return 0;
	return static_cast<AVLnode<T>*>(right)->getHeight() - static_cast<AVLnode<T>*>(left)->getHeight();
}

template <class T> AVLnode<T>* AVLnode<T>::rotate_right() {
	if (this == 0) return 0;
	AVLnode<T>* leftSon = static_cast<AVLnode<T>*>(left);
	if (leftSon == 0) return this;
	left = leftSon->right;
	leftSon->right = this;
	leftSon->updateParent(static_cast<AVLnode<T>*>(parent));
	parent = leftSon;
	static_cast<AVLnode<T>*>(left)->updateParent(this);
	updateParent(leftSon);
	updateHeight();
	leftSon->updateHeight();
	return leftSon;
}

template <class T> AVLnode<T>* AVLnode<T>::rotate_left() {
	if (this == 0) return 0;
	AVLnode<T>* rightSon = static_cast<AVLnode<T>*>(right);
	if (rightSon == 0) return this;
	right = rightSon->left;
	rightSon->left = this;
	rightSon->updateParent(static_cast<AVLnode<T>*>(parent));
	parent = rightSon;
	static_cast<AVLnode<T>*>(right)->updateParent(this);
	updateParent(rightSon);
	updateHeight();
	rightSon->updateHeight();
	return rightSon;
}

template <class T> AVLnode<T>* AVLnode<T>::fixBalance() {
	updateHeight();
	AVLnode<T>* rsc = static_cast<AVLnode<T>*>(right);
	AVLnode<T>* lsc = static_cast<AVLnode<T>*>(left);
	if (balance() == 2) { //right != 0 for it has a positive height
		if (static_cast<AVLnode<T>*>(right)->balance() < 0) {
			right = static_cast<AVLnode<T>*>(right)->rotate_right();
		}
		return rotate_left();
	}
	if (balance() == -2) {//same for left
 		if (static_cast<AVLnode<T>*>(left)->balance() > 0) {
			left = static_cast<AVLnode<T>*>(left)->rotate_left();
		}
		return rotate_right();
	}
	return this; // balance is ok
}

template <class T> class AVLtree {
private:
	AVLnode<T>* root;
	AVLnode<T>* recursiveInsert(AVLnode<T>* curr, T& val);
public:
	void iterate();
	AVLtree<T>(T& val) {
		root = new AVLnode<T>(val);
	}
	AVLtree<T>() {
		root = 0;
	}
	~AVLtree<T>() {
		delete root;
	}
	AVLnode<T>* find(T& val) {
		return static_cast<AVLnode<T>*>(root->find(val)); 
	}
	void insert(T& val) { root = recursiveInsert(root, val); }
	void Delete(T& val);
};

template <class T> AVLnode<T>* AVLtree<T>::recursiveInsert(AVLnode<T>* curr, T& val) {
	if (curr == 0) {
		return new AVLnode<T>(val);
	}
	if (curr->getKey() > val) {
		curr->left = recursiveInsert (static_cast<AVLnode<T>*>(curr->left), val);
		static_cast<AVLnode<T>*>(curr->left)->updateParent(curr);
	} else {
		curr->right = recursiveInsert (static_cast<AVLnode<T>*>(curr->right), val);
		static_cast<AVLnode<T>*>(curr->right)->updateParent(curr);
	}
	curr->updateHeight();
	return curr->fixBalance();
}

template <class T> void AVLtree<T>::Delete(T& val) {
	AVLnode<T>* toDel = static_cast<AVLnode<T>*>(root->find(val));
	if (toDel == 0) return;
	AVLnode<T>* Parent = static_cast<AVLnode<T>*>(toDel->parent);
	AVLnode<T>* l = static_cast<AVLnode<T>*>(toDel->left);
	AVLnode<T>* r = static_cast<AVLnode<T>*>(toDel->right);
	bool isLeft;
	if (Parent != 0) {
		isLeft = Parent->left == toDel;
	}
	toDel->left = 0;
	toDel->right = 0;
	delete toDel;
	l->updateParent(0);
	r->updateParent(0);
	if (r == 0) {
		l->updateParent(Parent);
		if (Parent != 0) {
			if (isLeft) {
				Parent->left = l;
			} else {
				Parent->right = l;
			}
		} else {
			root = l;
		}
		return;
	}
	AVLnode<T>* rightMin = static_cast<AVLnode<T>*>(r->getMin());
	AVLnode<T>* curr = static_cast<AVLnode<T>*>(rightMin->parent);
	AVLnode<T>* newSon =  static_cast<AVLnode<T>*>(rightMin->right);
	while (curr != 0) {
		curr->left = newSon;
		newSon = curr->fixBalance();
		curr =  static_cast<AVLnode<T>*>(curr->parent);
	}
	r = newSon;
	rightMin->left = l;
	rightMin->right = r;
	rightMin->parent = Parent;
	l->updateParent(rightMin);
	r->updateParent(rightMin);
	if (Parent != 0) {
		if (isLeft) {
			Parent->left = rightMin;
		} else {
			Parent->right = rightMin;
		}
	} else {
		root = rightMin;
	}
	return;
}

template <class T> void AVLtree<T>::iterate() {
	AVLnode<T>* curr = static_cast<AVLnode<T>*>(root->getMin());
	while (curr != 0) {
		cout << curr->getKey() << " ";
		curr = curr->Successor();
	}
}

/*struct segment {
	int id;
	int x1, y1, x2, y2;
};

struct Event {
	int x, type, id;
	Event(int x, int type, int id) :

		x(x),
		type(type),
		id(id)
	{
	}
	bool operator < (Event e) {
		if (x != e.x)  return x < e.x;
		return type > e.type; //NB
	}
	bool operator == (Event e) {
		return ((x == e.x) && (type == e.type) && (id == e.type)); 
	}
};

pair<int, int> intersection_check(vector<segment>& input) {
	AVLtree <segment> avl;
	vector <Event> Events;
	segment s;
	for (int i = 0;i < input.size();i++) {
		Events.push_back(Event(min(input[i].x1, input[i].x2), 1, input[i].id));
		Events.push_back(Event(max(input[i].x1, input[i].x2), -1, input[i].id));
	}
	sort(Events.begin(), Events.end());
	for (int i = 0;i < Events.size();i++) {
		int id = Events[i].id;
		if (Events[i].type == 1) {
			AVLnode <segment>* nextSeg = avl.find(input[id])->Successor();
			AVLnode <segment>* prevSeg = avl.find(input[id])->Predecessor();
			if ((prevEvent != 0) && (intersect(prevSeg->getKey(), input[id]))) {
				return make_pair(prevSeg->getKey().id, input[id].id);
			}
			if ((nextEvent != 0) && (intersect(nextSeg->getKey(), input[id]))) {
				return make_pair(nextSeg->getKey().id, input[id].id);
			}
		} else {
			continue;
		}
	}
	return make_pair(-1, -1);
}

void intersectionCheck() {
	int n;
	cin >> n;
	segment s;
	vector <segment> segments;
	for (int i = 0;i < n;i++) {
		cin >> s.x1 >> s.y1 >> s.x2 >> s.y2;
		s.id = i;
		segments.push_back(s);
	}
	pair<int, int> res = intersection_check(segments);
	if (res.first == -1) cout << "No intersections." << endl;
	else {
		cout << "Segment number " << res.first + 1 << "intersects with segment number " << res.second + 1 << endl;
	}
}*/

int main() {
	freopen("input.txt", "r", stdin);
	int n, i;
	int a;
	//intersectionCheck();
	_CrtDumpMemoryLeaks;
	return 0;
}
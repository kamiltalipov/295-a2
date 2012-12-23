#include <iostream>
#include <crtdbg.h>
using namespace std;

template <class T>
class AVLTree
{
private:
	class AVLNode
	{
	public:
		AVLNode* left;
		AVLNode* right;
		T key;
		int height;
		
		AVLNode() {}
		AVLNode(T& value, AVLNode* L, AVLNode* R, int h = 1)
		{
			key = value;
			left = L;
			right = R;
			height = h;
		}
		int getHeight();
		void updateHeight();
		int diff();
	};
	void leftRotation(AVLNode* &t);
	void rightRotation(AVLNode* &t);
	void balance(AVLNode* &t);
	void insert(AVLNode* &t, T &value);
	void erase(AVLNode* &t, T &value);
	void deleteAll(AVLNode* &t);
	AVLNode* root;
public:
	AVLTree()
	{
		root = NULL;
	}
	~AVLTree()
	{
		deleteAll(root);
	}
	AVLNode* Find(T &value);
	void Insert(T value);
	void Erase(T &value);
	AVLNode* Next(AVLNode* node);
	AVLNode* Prev(AVLNode* node);
};

template <class T>
typename AVLTree<T>::AVLNode* AVLTree<T>::Find(T &value)
{
	AVLNode* current = root;
	while (current != NULL)
	{
		if (current->x < value)
			current = current->right;
		else if (value < current->x)
			current = current->left;
		else
			return current;
	}
	return NULL;
}

template <class T>
int AVLTree<T>::AVLNode::getHeight()
{
	if (this == NULL)
		return 0;
	else 
		return height;
}

template <class T>
void AVLTree<T>::AVLNode::updateHeight()
{
	height = max(left->getHeight(), right->getHeight()) + 1;
}

template <class T>
int AVLTree<T>::AVLNode::diff()
{
	if (this != NULL)
		return left->getHeight() - right->getHeight();
	else
		return 0;
}

template <class T>
void AVLTree<T>::insert(AVLNode* &t, T &value)
{
	if (t != NULL)
	{
		if (t->key == value)
			return;
		else if (t->key < value)
			insert(t->right, value);
		else
			insert(t->left, value);
	}
	else
		t = new AVLNode(value, NULL, NULL);
	balance(t);
}

template <class T>
void AVLTree<T>::leftRotation(AVLNode* &t)
{
	AVLNode* temp = t->right;
	t->right = temp->left;
	t->updateHeight();
	temp->left = t;
	temp->updateHeight();
	t = temp;
}

template <class T>
void AVLTree<T>::rightRotation(AVLNode* &t)
{
	AVLNode* temp = t->left;
	t->left = temp->right;
	t->updateHeight();
	temp->right = t;
	temp->updateHeight();
	t = temp;
}


template <class T>
void AVLTree<T>::balance(AVLNode* &t)
{
	t->updateHeight();
	if (t->diff() == 2)
	{
		if (t->left->diff() == -1)
			leftRotation(t->left);
		rightRotation(t);
	}
	else if (t->diff() == -2)
	{
		if (t->right->diff() == 1)
			rightRotation(t->right);
		leftRotation(t);
	}
}

template <class T>
void AVLTree<T>::Insert(T value)
{
	insert(root, value);
}

template <class T>
void AVLTree<T>::erase(AVLNode* &t, T& value)
{
	if (t == NULL)
		return;
	else if (t->key < value)
		erase(t->right, value);
	else if (value < t->key)
		erase(t->left, value);
	else
	{
		if (t->left == NULL && t->right == NULL)
		{
			AVLNode* temp = t;
			t = NULL;
			delete temp;
			return;
		}
		else if (t->right != NULL)
		{
			leftRotation(t);
			erase(t->left, value); 
		}
		else
		{
			rightRotation(t);
			erase(t->right, value);
		}
	}

	balance(t);

}

template <class T>
void AVLTree<T>::Erase(T& value)
{
	erase(root, value);
}

template <class T>
void AVLTree<T>::deleteAll(AVLNode* &t)
{
	if(t != NULL)
	{
		deleteAll(t->left);
		deleteAll(t->right);
		delete t;
	}
}

int main()
{
	{
		int a = 5;
		AVLTree<int> Tree;
		Tree.Insert(a);
		a = 6;
		Tree.Insert(a);
		a = 7;
		Tree.Insert(a);
		a = 8;
		Tree.Insert(a);
		a = 9;
		Tree.Insert(a);
	}
	_CrtDumpMemoryLeaks();
	return 0;
}
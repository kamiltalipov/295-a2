#include <iostream>
using std :: cin;
using std :: cout;
#include <cstdlib>
#include <ctime>

#include "BST.h"

template <typename T> class Treep;

template <typename T>
class TreepNode : public BSTNode<T>
{
    friend class Treep<T>;

public:

    TreepNode (const T& val)
        :
        BSTNode<T> :: BSTNode (val),
        prior (rand ()),
        size (1)
    {
    }

    ~TreepNode ()
    {
        if (BSTNode<T> :: parent != NULL)
            static_cast<TreepNode<T>*> (BSTNode<T> :: parent)->size -= size;
        BSTNode<T> :: ~BSTNode ();
    }

    TreepNode<T>* next () const
    {
        return static_cast<TreepNode<T>*> (BSTNode<T> :: next ());
    }
    TreepNode<T>* prev () const
    {
        return static_cast<TreepNode<T>*> (BSTNode<T> :: prev ());
    }


protected:
    int prior;

    size_t size;

    TreepNode (const T& val, int _prior, TreepNode* _parent = NULL)
        :
        BSTNode<T> :: BSTNode (val, _parent),
        prior (_prior),
        size (1)
    {
    }
};

template <typename T>
class Treep : public BSTTree<T>
{
public:
    Treep ()
        :
        BSTTree<T> :: BSTTree ()
    {
    }

    ~Treep ()
    {
		delete root;
		root = NULL;
        BSTTree<T> :: ~BSTTree ();
    }

    TreepNode<T>* find (const T& val) const
    {
		return res = static_cast<TreepNode<T>*> (BSTTree<T> :: find (static_cast<TreepNode<T>*> (root), val));
    }

    TreepNode<T>* insert (const T& val)
    {
		TreepNode<T>* realRoot = static_cast<TreepNode<T>*> (root);
        TreepNode<T>* res = insert (realRoot, NULL, val, rand ());
		root = realRoot;
		return res;
    }

    void remove (const T& toRemoveVal)
    {
		TreepNode<T>* realRoot = static_cast<TreepNode<T>*> (root);
        remove (realRoot, toRemoveVal);
		root = realRoot;
    }

    TreepNode<T>* getNthElem (size_t n) const
    {
        return getNthElem (static_cast<TreepNode<T>*> (root), n);
    }

protected:
    TreepNode<T>* find (TreepNode<T>* node, const T& val) const;
    TreepNode<T>* insert (TreepNode<T>*& node, TreepNode<T>* parent, const T& val, int prior);
    void remove (TreepNode<T>*& node, const T& toRemoveVal);

    size_t getNodeSize (const TreepNode<T>* node) const
    {
        return node == NULL ? 0 : node->size;
    }

    void updateNodeSize (TreepNode<T>*& node);
    TreepNode<T>* getNthElem (TreepNode<T>* node, size_t n) const;

    void split (TreepNode<T>* node, const T& val, TreepNode<T>*& left, TreepNode<T>*& right)
    {
        if (node == NULL)
        {
            left = NULL;
            right = NULL;
			return;
        }
        else if (val < node->curVal)
        {
			TreepNode<T>* nodeLeft = static_cast<TreepNode<T>*> (node->left);
            split (nodeLeft, val, left, nodeLeft);
			node->left = nodeLeft;
            right = node;
        }
        else
        {
			TreepNode<T>* nodeRight = static_cast<TreepNode<T>*> (node->right);
            split (nodeRight, val, nodeRight, right);
			node->right = nodeRight;
            left = node;
        }

		TreepNode<T>* nodeLeft = static_cast<TreepNode<T>*> (node->left);
		TreepNode<T>* nodeRight = static_cast<TreepNode<T>*> (node->right);
        if (nodeLeft != NULL)
		{
            nodeLeft->parent = node;
			node->left = nodeLeft;
		}
        if (node->right != NULL)
		{
            nodeRight->parent = node;
			node->right = nodeRight;
		}
        updateNodeSize (left);
        updateNodeSize (right);
    }

	void merge (TreepNode<T>*& node, TreepNode<T>* left, TreepNode<T>* right)
	{
		if (left == NULL)
		{
			node = right;
			return;
		}
		else if (right == NULL)
		{
			node = left;
			return;
		}
		else if (right->prior < left->prior)
		{
			TreepNode<T>* leftRight = static_cast<TreepNode<T>*> (left->right);
			merge (leftRight, leftRight, right);
			left->right = leftRight;
			updateNodeSize (left);
			TreepNode<T>* parent = static_cast<TreepNode<T>*> (node->parent);
			node->parent = parent;
			node = left;
			TreepNode<T>* nodeRight = static_cast<TreepNode<T>*> (node->right);
			nodeRight->parent = node;
			node->right = nodeRight;
		}
		else
		{
			TreepNode<T>* rightLeft = static_cast<TreepNode<T>*> (right->left);
			merge (rightLeft, left, rightLeft);
			right->left = rightLeft;
			updateNodeSize (right);
			TreepNode<T>* parent = static_cast<TreepNode<T>*> (node->parent);
			node->parent = parent;
			node = right;
			TreepNode<T>* nodeLeft = static_cast<TreepNode<T>*> (node->left);
			nodeLeft->parent = node;
			node->left = nodeLeft;
		}

        updateNodeSize (node);
	}
};

template <typename T>
TreepNode<T>* Treep<T> :: getNthElem (TreepNode<T>* node, size_t n) const
{
    if (node == NULL)
        return NULL;

    size_t leftSize = getNodeSize (static_cast<TreepNode<T>*> (node->left));
    if (n <= leftSize)
        return getNthElem (static_cast<TreepNode<T>*> (node->left), n);
    if (n == leftSize + 1)
        return node;
    return getNthElem (static_cast<TreepNode<T>*> (node->right), n - leftSize - 1);
}

template <typename T>
TreepNode<T>* Treep<T> :: find (TreepNode<T>* node, const T& val) const
{
    if (node == NULL)
        return NULL;

    if (node->curVal == val)
        return node;

	return find (val < node->curVal ? node->left : node->right, val);
}

template <typename T>
TreepNode<T>* Treep<T> :: insert (TreepNode<T>*& node, TreepNode<T>* parent, const T& val, int prior)
{
    if (node == NULL)
    {
        node = new TreepNode<T> (val, prior, parent);
        return node;
    }
    else if (node->curVal == val)
        return node;
    else if (prior < node->prior)
    {
        TreepNode<T>* res = new TreepNode<T> (val, prior, parent);
		TreepNode<T>* left = static_cast<TreepNode<T>*> (res->left),
					* right = static_cast<TreepNode<T>*> (res->right);
        split (node, val, left, right);
		res->left = left;
		res->right = right;
        updateNodeSize (res);
        node = res;
        return node;
    }

	TreepNode<T>* left = static_cast<TreepNode<T>*> (node->left),
				* right = static_cast<TreepNode<T>*> (node->right);
	TreepNode<T>* res = insert (val < node->curVal ? left : right, node, val, prior);
	node->left = left;
	node->right = right;
	updateNodeSize (node);
    return res;
}

template <typename T>
void Treep<T> :: remove (TreepNode<T>*& node, const T& toRemoveVal)
{
	if (node == NULL)
		return;

	if (node->curVal == toRemoveVal)
	{
		bool isLeftNode;
		TreepNode<T>* parent = static_cast<TreepNode<T>*> (node->parent);
		if (parent != NULL)
			isLeftNode = parent->left == node;

		TreepNode<T>* left = static_cast<TreepNode<T>*> (node->left),
				    * right = static_cast<TreepNode<T>*> (node->right);

		merge (left, left, right);
		if (left != NULL)
			left->parent = parent;
		if (parent != NULL)
		{
			if (isLeftNode)
				parent->left = left;
			else
				parent->right = left;
		}

		node->parent = parent;
		node->left = NULL;
		node->right = NULL;
		delete node;

		node = left;
		updateNodeSize (node);
	}
	else
	{
		TreepNode<T>* left = static_cast<TreepNode<T>*> (node->left),
				    * right = static_cast<TreepNode<T>*> (node->right);
		remove (toRemoveVal < node->curVal ? left : right, toRemoveVal);
		node->left = left;
		node->right = right;
	}
}

template <typename T>
void Treep<T> :: updateNodeSize (TreepNode<T>*& node)
{
    if (node == NULL)
        return;

    node->size = getNodeSize (static_cast<TreepNode<T>*> (node->left)) +
			     getNodeSize (static_cast<TreepNode<T>*> (node->right)) + 1;
}

int main ()
{
    srand (time (NULL));

    Treep<int> t;
    for (int i = 0; i < 25; ++i)
		t.insert (i);

    TreepNode<int>* node = t.getNthElem (20);
    cout << node->getVal () << ' ';
	t.remove (19);
	node = t.getNthElem (20);
	cout << node->getVal ();
	cin.get ();

    return 0;
}

#include <iostream>
using std :: cin;
using std :: cout;
#include <cstdlib>
#include <ctime>


template <typename T> class Treep;

template <typename T>
class TreepNode
{
    friend class Treep<T>;

public:

    TreepNode (const T& val)
        :
        curVal (val),
        prior (rand ()),
        parent (NULL),
        left (NULL),
        right (NULL)
    {
    }

    ~TreepNode ()
    {
		delete left;
        delete right;

        if (parent != NULL)
        {
			if (parent->left == this)
                parent->left = NULL;
            else
                parent->right = NULL;
        }
    }

    T getVal () const
    {
        return curVal;
    }

    TreepNode* next () const;
    TreepNode* prev () const;

protected:
    T curVal;

    int prior;

    TreepNode* parent;
    TreepNode* left,
             * right;

    TreepNode (const T& val, int _prior, TreepNode* _parent = NULL)
        :
        curVal (val),
        prior (_prior),
        parent (_parent),
        left (NULL),
        right (NULL)
    {
    }
};

template <typename T>
TreepNode<T>* TreepNode<T> :: next () const
{
    if (right != NULL)
    {
        TreepNode<T>* res = right;
        while (res->left != NULL)
            res = res->left;
        return res;
    }

	if (parent != NULL)
	{
		if (parent->left == this)
			return parent;

		TreepNode<T>* res = parent;
		while (res->parent != NULL && res->parent->right == res)
			res = res->parent;

		res = res->parent;

		return res;
	}

    return NULL;
}

template <typename T>
TreepNode<T>* TreepNode<T> :: prev () const
{
    if (left != NULL)
    {
        TreepNode<T>* res = left;
        while (res->right != NULL)
            res = res->right;
        return res;
    }

    if (parent != NULL)
    {
		if (parent->right == this)
			return parent;

		TreepNode<T>* res = parent;
		while (res->parent != NULL && res->parent->left == res)
			res = res->parent;

		res = res->parent;

		return res;
    }

    return NULL;
}

template <typename T>
class Treep
{
public:
    Treep ()
        :
        root (NULL)
    {
    }

    ~Treep ()
    {
        delete root;
    }

    TreepNode<T>* find (const T& val) const
    {
        return find (root, val);
    }

    TreepNode<T>* insert (const T& val)
    {
        return insert (root, NULL, val, rand ());
    }

    void remove (const T& toRemoveVal)
    {
        return remove (root, toRemoveVal);
    }

protected:
    TreepNode<T>* root;

    TreepNode<T>* find (TreepNode<T>* node, const T& val) const;
    TreepNode<T>* insert (TreepNode<T>*& node, TreepNode<T>* parent, const T& val, int prior);
    void remove (TreepNode<T>*& node, const T& toRemoveVal);

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
            split (node->left, val, left, node->left);
            right = node;
        }
        else
        {
            split (node->right, val, node->right, right);
            left = node;
        }

        if (node->left != NULL)
            node->left->parent = node;
        if (node->right != NULL)
            node->right->parent = node;
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
			merge (left->right, left->right, right);
			TreepNode<T>* parent = node->parent;
			node = left;
			node->parent = parent;
			node->right->parent = node;
		}
		else
		{
			merge (right->left, left, right->left);
			TreepNode<T>* parent = node->parent;
			node = right;
			node->parent = parent;
			node->left->parent = node;
		}

	}
};

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
        split (node, val, res->left, res->right);
        node = res;
        return node;
    }

    return insert (val < node->curVal ? node->left : node->right, node, val, prior);
}

template <typename T>
void Treep<T> :: remove (TreepNode<T>*& node, const T& toRemoveVal)
{
	if (node == NULL)
		return;

	if (node->curVal == toRemoveVal)
	{
		bool isLeftNode;
		if (node->parent != NULL)
			isLeftNode = node->parent->left == node;

		TreepNode<T>* left = node->left, * right = node->right,
					* parent = node->parent;
		node->left = NULL;
		node->right = NULL;
		delete node;

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

		node = left;
	}
	else
		remove (toRemoveVal < node->curVal ? node->left : node->right, toRemoveVal);
}

int main ()
{
    srand (time (NULL));

    return 0;
}

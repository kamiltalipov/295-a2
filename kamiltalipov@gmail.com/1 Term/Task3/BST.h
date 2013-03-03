#include <cstdlib>

template <typename T> class BSTTreep;

template <typename T>
class BSTNode
{
	friend class BSTTreep<T>;

public:
	BSTNode (const T& val)
        :
        curVal (val),
        parent (NULL),
        left (NULL),
        right (NULL)
    {
    }

    ~BSTNode ()
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

    BSTNode<T>* next () const;
    BSTNode<T>* prev () const;

    T getVal () const
    {
        return curVal;
    }

protected:
    T curVal;

    BSTNode<T>* parent;
    BSTNode<T>* left,
              * right;

    BSTNode (const T& val, BSTNode<T>* _parent)
        :
        curVal (val),
        parent (_parent),
        left (NULL),
        right (NULL)
    {
    }
};

template <typename T>
BSTNode<T>* BSTNode<T> :: next () const
{
    if (right != NULL)
    {
        BSTNode<T>* res = right;
        while (res->left != NULL)
            res = res->left;
        return res;
    }

	if (parent != NULL)
	{
		if (parent->left == this)
			return parent;

		BSTNode<T>* res = parent;
		while (res->parent != NULL && res->parent->right == res)
			res = res->parent;

		res = res->parent;

		return res;
	}

    return NULL;
}

template <typename T>
BSTNode<T>* BSTNode<T> :: prev () const
{
    if (left != NULL)
    {
        BSTNode<T>* res = left;
        while (res->right != NULL)
            res = res->right;
        return res;
    }

    if (parent != NULL)
    {
		if (parent->right == this)
			return parent;

		BSTNode<T>* res = parent;
		while (res->parent != NULL && res->parent->left == res)
			res = res->parent;

		res = res->parent;

		return res;
    }

    return NULL;
}


template <typename T>
class BSTTree
{
public:
	BSTTree ()
		:
		root (NULL)
	{
	}
	
	~BSTTree ()
	{
		delete root;
	}

	BSTNode<T>* find (const T& val) const
	{
		return find (root, val);
	}
	
    BSTNode<T>* insert (const T& val)
	{
		return insert (root, NULL, val);
	}
	
    void remove (const T& toRemoveVal)
	{
		remove (root, toRemoveVal);
	}

protected:
	BSTNode<T>* root;
	
	BSTNode<T>* find (BSTNode<T>* node, const T& val) const;
    BSTNode<T>* insert (BSTNode<T>*& node, BSTNode<T>* parent, const T& val);
    void remove (BSTNode<T>*& node, const T& toRemoveVal);
	
    BSTNode<T>* merge (BSTNode<T>* node1, BSTNode<T>* node2)
    {
        if (node1 == NULL)
            return node2;
        if (node2 == NULL)
            return node1;

        if (rand ()  % 2)
        {
            node1->right = merge (node1->right,  node2);
            return node1;
        }
        else
        {
            node2->left = merge (node1, node2->left);
            return node2;
        }

        return NULL;
    }
};

template <typename T>
BSTNode<T>* BSTTree<T> :: find (BSTNode<T>* node, const T& val) const
{
    if (node == NULL)
        return NULL;

    if (node->curVal == val)
        return node;

	return find (val < node->curVal ? node->left : node->right, val);
}

template <typename T>
BSTNode<T>* BSTTree<T> :: insert (BSTNode<T>*& node, BSTNode<T>* parent, const T& val)
{
	if (node == NULL)
	{
		node = new BSTNode<T> (val, parent);
		return node;
	}
		
    if (node->curVal == val)
        return node;

    return insert (val < node->curVal ? node->left : node->right, node, val);
}

template <typename T>
void BSTTree<T> :: remove (BSTNode<T>*& node, const T& toRemoveVal)
{
    if (node == NULL)
        return;
	
	if (node->curVal == toRemoveVal)
	{
		BSTNode<T>* newNode = merge (node->left, node->right);
		if (node->parent != NULL)
		{
			if (node->parent->left == node)
				node->parent->left = newNode;
			else
				node->parent->right = newNode;
		}

		node->left = NULL;
		node->right = NULL;
		delete node;
		node = newNode;
		return;
	}
	
	remove (toRemoveVal < node->val ? node->left : node->right, toRemoveVal);
}

/*
int main ()
{
    srand (time (NULL));

    return 0;
}
*/

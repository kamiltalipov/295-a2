#include <iostream>
using std :: cin;
using std :: cout;
#include <algorithm>
using std :: max;

template <typename T> class AVLTree;

template <typename T>
class AVLNode
{
    friend class AVLTree<T>;

public:

    AVLNode (const T& val)
        :
        curVal (val),
        height (1),
        parent (NULL),
        left (NULL),
        right (NULL)
    {
    }

    ~AVLNode ()
    {
        delete left;
        delete right;
    }

    T getVal () const
    {
        return curVal;
    }

    AVLNode<T>* next () const;
    AVLNode<T>* prev () const;

protected:
    T curVal;

    size_t height;

    AVLNode<T>* parent;
    AVLNode<T>* left,
              * right;

    AVLNode (const T& val, AVLNode<T>* _parent)
        :
        curVal (val),
        height (1),
        parent (_parent),
        left (NULL),
        right (NULL)
    {
    }
};

template <typename T>
AVLNode<T>* AVLNode<T> :: next () const
{
    if (right != NULL)
    {
        AVLNode<T>* res = right;
        while (res->left != NULL)
            res = res->left;
        return res;
    }

	if (parent != NULL)
	{
		if (parent->left == this)
			return parent;

		AVLNode<T>* res = parent;
		while (res->parent != NULL && res->parent->right == res)
			res = res->parent;

		res = res->parent;

		return res;
	}

    return NULL;
}

template <typename T>
AVLNode<T>* AVLNode<T> :: prev () const
{
    if (left != NULL)
    {
        AVLNode<T>* res = left;
        while (res->right != NULL)
            res = res->right;
        return res;
    }

    if (parent != NULL)
    {
		if (parent->right == this)
			return parent;

		AVLNode<T>* res = parent;
		while (res->parent != NULL && res->parent->left == res)
			res = res->parent;

		res = res->parent;

		return res;
    }

    return NULL;
}

template <typename T>
class AVLTree
{
public:
    AVLTree ()
        :
        root (NULL)
    {
    }

    ~AVLTree ()
    {
        delete root;
    }

    void insert (const T& val)
    {
        insert (root, val);
    }

    void remove (const T& val)
    {
        remove (root, val);
    }

    AVLNode<T>* find (const T& val)
    {
        return find (root, val);
    }

protected:
    AVLNode<T>* root;

    AVLNode<T>* rotate_LL (AVLNode<T>* node);
    AVLNode<T>* rotate_RR (AVLNode<T>* node);
    AVLNode<T>* rotate_RL (AVLNode<T>* node);
    AVLNode<T>* rotate_LR (AVLNode<T>* node);

    void update (AVLNode<T>*& node);
    int get_height (AVLNode<T>* node);
    int get_balance (AVLNode<T>* node);
    void balance_tree (AVLNode<T>*& node);

    void insert (AVLNode<T>*& node, const T& val);
    void remove (AVLNode<T>*& node, const T& val);
    AVLNode<T>* find (AVLNode<T>* node, const T& val);

    AVLNode<T>* findMin (AVLNode<T>* node);
    AVLNode<T>* removeMin (AVLNode<T>* node);

    void setParent (AVLNode<T>*& node, AVLNode<T>* parent)
    {
        if (node == NULL)
            return;
        node->parent = parent;
    }
};

template <typename T>
AVLNode<T>* AVLTree<T> :: rotate_LL (AVLNode<T>* node)
{
    AVLNode<T>* child = node->left;
    node->left = child->right;
    child->right = node;
    update (child);
    return child;
}

template <typename T>
AVLNode<T>* AVLTree<T> :: rotate_RR (AVLNode<T>* node)
{
    AVLNode<T>* child = node->right;
    node->right = child->left;
    child->left = node;
    update (child);
    return child;
}

template <typename T>
AVLNode<T>* AVLTree<T> :: rotate_RL (AVLNode<T>* node)
{
    AVLNode<T>* child = node->right;
    node->right = rotate_LL (child);
    update (node->right);
    update (node);
    return rotate_RR (node);
}

template <typename T>
AVLNode<T>* AVLTree<T> :: rotate_LR (AVLNode<T>* node)
{
    AVLNode<T>* child = node->left;
    node->left = rotate_RR (child);
    update (node->left);
    update (node);
    return rotate_LL (node);
}

template <typename T>
void AVLTree<T> :: update (AVLNode<T>*& node)
{
    if (node == NULL)
        return;
    node->height = max (get_height(node->left), get_height (node->right)) + 1;
    setParent (node->left, node);
    setParent (node->right, node);
}

template <typename T>
int AVLTree<T> :: get_height (AVLNode<T>* node)
{
    return node ? node->height : 0;
}

template <typename T>
int AVLTree<T> :: get_balance (AVLNode<T>* node)
{
    return node ? get_height(node->left) - get_height(node->right) : 0;
}

template <typename T>
void AVLTree<T> :: balance_tree (AVLNode<T>*& node)
{
	int height_diff = get_balance (node);

    if (height_diff > 1)
    {
        if (get_balance (node->left) > 0)
            node = rotate_LL (node);
        else
            node = rotate_LR (node);
    }
    else if (height_diff < -1)
    {
        if (get_balance (node->right) < 0)
            node = rotate_RR (node);
        else
            node = rotate_RL (node);
    }

    update (node);
}

template <typename T>
void AVLTree<T> :: insert (AVLNode<T>*& node, const T& val)
{
    if (node == NULL)
    {
        node = new AVLNode<T> (val);
        return;
    }
    else if (val < node->curVal)
    {
        insert(node->left, val);
        update (node->left);
    }
    else if (val == node->curVal)
        return;
    else
    {
        insert (node->right, val);
        update (node->right);
    }

    balance_tree (node);
    update (node);
}

template <typename T>
void AVLTree<T> :: remove (AVLNode<T>*& node, const T& val)
{
    if (node == NULL)
        return;
    if (val < node->curVal)
        remove (node->left, val);
    else if (val == node->curVal)
    {
        AVLNode<T>* left = node->left,
                  * right = node->right;
        node->left = node->right = NULL;
        delete node;
        if (right == NULL)
        {
            node = left;
            return;
        }
        AVLNode<T>* minNode = findMin (right);
        minNode->right = removeMin (right);
        minNode->left = left;
        balance_tree (minNode);
        node = minNode;
    }
    else
        remove (node->right, val);

    balance_tree (node);
}

template <typename T>
AVLNode<T>* AVLTree<T> :: find (AVLNode<T>* node, const T& val)
{
    if (node == NULL)
        return NULL;

    if (val == node->curVal)
        return node;

    return find (val < node->curVal ? node->left : node->right, val);
}

template <typename T>
AVLNode<T>* AVLTree<T> :: findMin (AVLNode<T>* node)
{
    AVLNode<T>* res = node;
    while (res->left != NULL)
        res = res->left;
    return res;
}

template <typename T>
AVLNode<T>* AVLTree<T> :: removeMin (AVLNode<T>* node)
{
    if (node->left == NULL)
        return node->right;
    node->left = removeMin (node->left);
    balance_tree (node);
    return node;
}

int main ()
{
    AVLTree<int> t;
    for (int i = 0; i < 1000000; ++i)
        t.insert (i);
	/*
    AVLNode<int>* n = t.find (5);
    cout << n->getVal ();
	t.remove (5);
    n = t.find (5);
    if (n != NULL)
        cout << " WTF\n";
    n = t.find (8);
    cout << n->getVal ();*/
	cin.get ();

    return 0;
}

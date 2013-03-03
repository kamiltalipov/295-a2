#include <iostream>
using std :: cin;
using std :: cout;
#include <algorithm>
using std :: min;
using std :: max;
#include <vector>
using std :: vector;
#include <cassert>
#include <climits>

class RMQ
{
public:
    RMQ (const vector<int>& a)
        :
        root (NULL)
    {
        assert (!a.empty ());

        createTree (root, 0, a.size () - 1);
        for (size_t i = 0; i < a.size (); ++i)
            modify (root, i, i, a[i]);
    }

    ~RMQ ()
    {
        delete root;
    }

    void modify (size_t l, size_t r, int delta)
    {
        modify (root, l, r, delta);
    }

    int getMin (size_t l, size_t r) const
    {
        return getMin (root, l, r);
    }

private:
    struct RMQNode
    {
        int min, add;
        size_t coverLeft, coverRight;
        RMQNode* left,
               * right;

        RMQNode (size_t _coverLeft = 0, size_t _coverRight = 0)
            :
            min (0), add (0),
            coverLeft (_coverLeft), coverRight (_coverRight),
            left (NULL), right (NULL)
        {
        }

        ~RMQNode ()
        {
            delete left;
            delete right;
        }
    };

    RMQNode* root;

    void createTree (RMQNode*& node, size_t l, size_t r);
    void modify (RMQNode* node, size_t l, size_t r, int delta);
    int getMin (const RMQNode* node, size_t l, size_t r, int sumAdd = 0) const;
};

void RMQ :: createTree (RMQNode*& node, size_t l, size_t r)
{
	node = new RMQNode (l, r);
	if (l < r)
	{
		createTree (node->left, l, (l + r) / 2);
		createTree (node->right, (l + r) / 2 + 1, r);
	}
}

void RMQ :: modify (RMQNode* node, size_t l, size_t r, int delta)
{
	if (node->coverLeft == l && node->coverRight == r)
		node->add += delta;
	else
	{
		if (l <= node->left->coverRight)
			modify (node->left, l, min (r, node->left->coverRight), delta);
		if (r >= node->right->coverLeft)
			modify (node->right, max (l, node->right->coverLeft), r, delta);
		node->min = min (node->left->min + node->left->add, node->right->min + node->right->add);
	}
}

int RMQ :: getMin (const RMQNode* node, size_t l, size_t r, int sumAdd) const
{
	if (node->coverLeft == l && node->coverRight == r)
		return sumAdd + node->min;

	int res = INT_MAX;
	if (l <= node->left->coverRight)
		res = min (getMin (node->left, l, min (r, node->left->coverRight), sumAdd + node->left->add), res);
	if (r >= node->right->coverLeft)
		res = min (getMin (node->right, max (l, node->right->coverLeft), r, sumAdd + node->right->add), res);
	return res;
}

int main ()
{
    vector<int> a (10);
    for (int i = 0; i < 10; ++i)
        a[i] = i;
    RMQ x (a);
    cout << x.getMin (5, 7);

	return 0;
}

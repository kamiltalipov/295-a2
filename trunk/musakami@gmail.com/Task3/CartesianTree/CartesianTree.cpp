#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template<class Value_Type, typename _Compare = less<Value_Type> >
class BST
{
    _Compare Compare;

public:

    class BSTNode
    {
    public:
        Value_Type x;
        BSTNode *left, *right, *parent;

        BSTNode(Value_Type x, BSTNode *p)
        {
            this -> x = x;
            parent = p;
            left = NULL;
            right = NULL;
        }

        ~BSTNode()
        {
            delete left;
            delete right;
        }

    };

    BSTNode *head;

    BST()
    {
        head = NULL;
    }

    ~BST()
    {
        delete head;
    }

    BSTNode* min()
    {
        return min(head);
    }

    BSTNode* max()
    {
        return max(head);
    }

    virtual void Add(Value_Type x)
    {
        head = Add(head, x);
    }

    BSTNode* Find(Value_Type x)
    {
        BSTNode *current = head;
        while (current != NULL && (Compare(current -> x, x) || Compare(x, current -> x)))
        {
            if (Compare(x, current -> x))
                current = current -> left;
            else
                current = current -> right;
        }
        return current;
    }

    void Erase(Value_Type x)
    {
        BSTNode* t = Find(x);
        if (t == NULL)
            return;
        if (t == head)
            head = Erase(head);
        else
            if (t -> parent -> left == t)
                t -> parent -> left = Erase(t);
            else
                t -> parent -> right = Erase(t);
    }

    void Print()
    {
        for (BSTNode* t = min(head); t != NULL; t = next(t))
            cout << t -> x << " ";
    }

private:

    BSTNode* min(BSTNode *t)
    {
        BSTNode *current = t;
        while (current != NULL && current -> left != NULL)
            current = current -> left;
        return current;
    }

    BSTNode* max(BSTNode *t)
    {
        BSTNode *current = t;
        while (current != NULL && current -> right != NULL)
            current = current -> right;
        return current;
    }

    BSTNode* next(BSTNode *t)
    {
        if (t == NULL)
            return NULL;
        if (t -> right != NULL)
            return min(t -> right);
        BSTNode* last;
        do
        {
            last = t;
            t = t -> parent;
        } while (t != NULL && t -> right == last);
        return t;
    }

    BSTNode* Add(BSTNode *t, Value_Type x)
    {
        if (t == NULL)
            return new BSTNode(x, NULL);
        if (x == t -> x)
            return t;
        BSTNode *current = t;
        while (true)
            if (Compare(x, current -> x))
            {
                if (current -> left == NULL)
                {
                    current -> left = new BSTNode(x, current);
                    return t;
                }
                else
                    current = current -> left;
            }
            else
            {
                if (current -> right == NULL)
                {
                    current -> right = new BSTNode(x, current);
                    return t;
                }
                else
                    current = current -> right;
            }
    }

    BSTNode* Erase(BSTNode* t)
    {
        if (t -> left == NULL)
        {
            BSTNode* result = t -> right;
            t -> right = NULL;
            if (result != NULL)
                result -> parent = t -> parent;
            delete t;
            return result;
        }
        else
        {
            BSTNode* result = max(t -> left);
            if (result -> parent != t)
                result -> parent -> right = result -> left;
            else
                result -> parent -> left = result -> left;
            if (result -> left != NULL)
                result -> left -> parent = result -> parent;
            result -> parent = t -> parent;
            result -> left = t -> left;
            result -> right = t -> right;
            t -> left = NULL;
            t -> right = NULL;
            delete t;
            return result;
        }
    }
};

class Treap:public BST<int>
{
public:
    class TNode: public BST<int>::BSTNode
    {
    public:
        int y;
        int size;

        TNode(int x, int y, BSTNode *parent): BSTNode(x, parent)
        {
            this -> y = y;
            size = 1;
        }
    };
private:

    int GetSize(BSTNode *t)
    {
        if (t == NULL)
            return 0;
        return static_cast<TNode*>(t) -> size;
    }

    void Update(BSTNode *t)
    {
        if (t != NULL)
            static_cast<TNode*>(t) -> size = GetSize(t -> left) + GetSize(t -> right) + 1;
    }

    void split(BSTNode *t, int x, BSTNode* &left, BSTNode* &right)
    {
        if (t == NULL)
        {
            left = NULL;
            right = NULL;
            return;
        }
        if (t -> x < x)
        {
            left = t;
            split(t -> right, x, left -> right, right);
        }
        else
        {
            right = t;
            split(t -> left, x, left, right -> left);
        }
        if (left != NULL)
        {
            left -> parent = NULL;
            if (left -> right != NULL)
                left -> right -> parent = left;
        }
        if (right != NULL)
        {
            right -> parent = NULL;
            if (right -> left != NULL)
                right -> left -> parent = right;
        }
        Update(left);
        Update(right);
    }

    BSTNode* merge(BSTNode *left, BSTNode *right)
    {
        if (left == NULL)
            return right;
        if (right == NULL)
            return left;
        BSTNode* result;
        if (static_cast<TNode*>(left) -> y < static_cast<TNode*>(right) -> y)
        {
            result = left;
            left -> right = merge(left -> right, right);
            if (left -> right != NULL)
                left -> right -> parent = left;
        }
        else
        {
            result = right;
            right -> left = merge(left, right -> left);
            if (right -> left != NULL)
                right -> left -> parent = right;
        }
        Update(result);
        return result;
    }

    BSTNode* Add(BSTNode *t, int x, int y, BSTNode* parent)
    {
        if (t == NULL)
            return new TNode(x, y, parent);
        if (static_cast<TNode*>(t) -> y > y)
        {
            TNode *newnode = new TNode(x, y, parent);
            split(t, x, newnode -> left, newnode -> right);
            if (newnode -> left != NULL)
                newnode -> left -> parent = newnode;
            if (newnode -> right != NULL)
                newnode -> right -> parent = newnode;
            Update(newnode);
            return newnode;
        }
        if (t -> x > x)
            t -> left = Add(t -> left, x, y, t);
        else
            t -> right = Add(t -> right, x, y, t);
        Update(t);
        return t;
    }

    BSTNode* Erase(BSTNode* t, int x)
    {
        if (t == NULL)
            return NULL;
        if (t -> x == x)
        {
            BSTNode* result = merge(t -> left, t -> right);
            t -> left = NULL;
            t -> right = NULL;
            delete t;
            return result;
        }
        if (t -> x > x)
        {
            t -> left = Erase(t -> left, x);
            if (t -> left != NULL)
                t -> left -> parent = t;
        }
        else
        {
            t -> right = Erase(t -> right, x);
            if (t -> right != NULL)
                t -> right -> parent = t;
        }
        Update(t);
        return t;
    }

    int GetAt(BSTNode *t, int k)
    {
        if (t == NULL)
            return -1;
        if (GetSize(t -> left) >= k)
            return GetAt(t -> left, k);
        if (GetSize(t -> left) + 1 == k)
            return (t -> x);
        return GetAt(t -> right, k - GetSize(t -> left) - 1);
    }

public:
    void Add(int x)
    {
        head = Add(head, x, rand(), NULL);
        head -> parent = NULL;
    }

    void Erase(int x)
    {
        head = Erase(head, x);
        if (head != NULL)
            head -> parent = NULL;
    }

    int GetAt(int k)
    {
        return GetAt(head, k);
    }
};

int main()
{
    int n;
    cin >> n;
    Treap tree;
    for (int i = 0; i < n; i++)
    {
        int k;
        cin >> k;
        tree.Add(k);
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        int k;
        cin >> k;
        cout << tree.GetAt(k) << endl;
    }
    tree.Print();
    return 0;
}

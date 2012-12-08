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

    void Add(Value_Type x)
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
        for (BSTNode* t = min(); t != NULL; t = next(t))
            cout << t -> x << " ";
    }

protected:

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

class AVLTree:public BST<int>
{
public:
    class TNode: public BST<int>::BSTNode
    {
    public:
        int height;
        bool close;

        TNode(int x, bool close, BSTNode *parent): BSTNode(x, parent)
        {
            height = 1;
            this -> close = close;
        }
    };
private:

    int GetHeight(BSTNode* t)
    {
        if (t == NULL)
            return 0;
        return static_cast<TNode*>(t) -> height;
    }

    void Update(BSTNode* t)
    {
        if (t != NULL)
            static_cast<TNode*>(t) -> height = std::max(GetHeight(t -> left), GetHeight(t -> right)) + 1;
    }

    int Diff(BSTNode* t)
    {
        if (t == NULL)
            return 0;
        return GetHeight(t -> left) - GetHeight(t -> right);
    }

    BSTNode* SmallLeftRotation(BSTNode* a)
    {
        BSTNode* b = a -> right;
        BSTNode* middle = b -> left;
        b -> left = a;
        b -> parent = a -> parent;
        a -> right = middle;
        a -> parent = b;
        if (middle != NULL)
            middle -> parent = a;
        Update(a);
        Update(b);
        return b;
    }

    BSTNode* BigLeftRotation(BSTNode *a)
    {
        BSTNode* b = a -> right;
        BSTNode* c = b -> left;
        BSTNode* cleft = c -> left;
        BSTNode* cright = c -> right;
        c -> left = a;
        c -> right = b;
        c -> parent = a -> parent;
        a -> right = cleft;
        a -> parent = c;
        b -> left = cright;
        b -> parent = c;
        if (cleft != NULL)
            cleft -> parent = a;
        if (cright != NULL)
            cright -> parent = b;
        Update(a);
        Update(b);
        Update(c);
        return c;
    }

    BSTNode* SmallRightRotation(BSTNode* a)
    {
        BSTNode* b = a -> left;
        BSTNode* middle = b -> right;
        b -> right = a;
        b -> parent = a -> parent;
        a -> left = middle;
        a -> parent = b;
        if (middle != NULL)
            middle -> parent = a;
        Update(a);
        Update(b);
        return b;
    }

    BSTNode* BigRightRotation(BSTNode *a)
    {
        BSTNode* b = a -> left;
        BSTNode* c = b -> right;
        BSTNode* cleft = c -> left;
        BSTNode* cright = c -> right;
        c -> right = a;
        c -> left = b;
        c -> parent = a -> parent;
        a -> left = cright;
        a -> parent = c;
        b -> right = cleft;
        b -> parent = c;
        if (cleft != NULL)
            cleft -> parent = b;
        if (cright != NULL)
            cright -> parent = a;
        Update(a);
        Update(b);
        Update(c);
        return c;
    }

    void Balance(BSTNode *t)
    {
        BSTNode *parent = t -> parent;
        bool left = false;
        if (parent != NULL && parent -> left == t)
            left = true;
        int diff = Diff(t);
        if (diff == -2)
            if (Diff(t -> right) == 1)
                t = BigLeftRotation(t);
            else
                t = SmallLeftRotation(t);
        if (diff == 2)
            if (Diff(t -> left) == -1)
                t = BigRightRotation(t);
            else
                t = SmallRightRotation(t);
        if (parent == NULL)
            head = t;
        else
        {
            if (left)
                parent -> left = t;
            else
                parent -> right = t;
        }
    }

    void Restore(BSTNode *t)
    {
        BSTNode* current = t;
        while (current != NULL)
        {
            Update(current);
            Balance(current);
            current = current -> parent;
        }
    }

    pair<BSTNode*, BSTNode*> Add(BSTNode *t, bool close, int x)
    {
        if (t == NULL)
            return make_pair(new TNode(x, close, NULL), (BSTNode*)NULL);
        if (x == t -> x)
            return make_pair(t, (BSTNode*)NULL);
        BSTNode *current = t;
        while (true)
            if (x < current -> x)
            {
                if (current -> left == NULL)
                {
                    current -> left = new TNode(x, close, current);
                    return make_pair(t, current -> left);
                }
                else
                    current = current -> left;
            }
            else
            {
                if (current -> right == NULL)
                {
                    current -> right = new TNode(x, close, current);
                    return make_pair(t, current -> right);
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

public:

    void Add(int x, bool close)
    {
        pair<BSTNode*, BSTNode*> result = Add(head, close, x);
        head = result.first;
        Restore(result.second);
    }

    void Erase(int x)
    {
        BSTNode* t = Find(x);
        if (t == NULL)
            return;
        if (t == head)
        {
            head = Erase(head);
            if (head != NULL)
            {
                if (head -> left != NULL)
                    Restore(max(head -> left));
                else
                    Restore(head);
            }
        }
        else
            if (t -> parent -> left == t)
            {
                BSTNode* parent = t -> parent;
                parent -> left = Erase(t);
                if (parent -> left != NULL)
                    if (parent -> left -> left != NULL)
                        Restore(max(parent -> left -> left));
                    else
                        Restore(max(parent -> left));
                else
                    Restore(parent);
            }
            else
            {
                BSTNode* parent = t -> parent;
                parent -> right = Erase(t);
                if (parent -> right != NULL)
                    if (parent -> right -> left != NULL)
                        Restore(max(parent -> right -> left));
                    else
                        Restore(max(parent -> right));
                else
                    Restore(parent);
            }
    }

    bool Check()
    {
        int cnt = 0;
        for (BSTNode *current = min(); current != NULL; current = next(current))
        {
            if (!static_cast<TNode*>(current) -> close)
                cnt++;
            else
                cnt--;
            if (cnt > 1)
                return false;
        }
        return true;
    }
};

int main()
{
    int n;
    cin >> n;
    AVLTree tree;
    for (int i = 0; i < n; i++)
    {
        int k1, k2;
        cin >> k1 >> k2;
        tree.Add(k1, false);
        tree.Add(k2, true);
    }
    cout << tree.Check();
    return 0;
}

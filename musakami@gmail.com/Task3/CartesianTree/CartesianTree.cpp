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

template<class Value_Type, typename _Compare = less<Value_Type> >
class Treap:public BST<Value_Type, _Compare>
{
public:
    class TNode: public BST<Value_Type, _Compare>::BSTNode
    {
    public:
        int y;
        int size;

        TNode(int x, int y, typename BST<Value_Type, _Compare>::BSTNode *parent): BST<Value_Type, _Compare>::BSTNode(x, parent)
        {
            this -> y = y;
            size = 1;
        }
    };
private:

    int GetSize(typename BST<Value_Type, _Compare>::BSTNode *t)
    {
        if (t == NULL)
            return 0;
        return static_cast<TNode*>(t) -> size;
    }

    void Update(typename BST<Value_Type, _Compare>::BSTNode *t)
    {
        if (t != NULL)
            static_cast<TNode*>(t) -> size = GetSize(t -> left) + GetSize(t -> right) + 1;
    }

    void split(typename BST<Value_Type, _Compare>::BSTNode *t, int x, typename BST<Value_Type, _Compare>::BSTNode* &left, typename BST<Value_Type, _Compare>::BSTNode* &right)
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

    typename BST<Value_Type, _Compare>::BSTNode* merge(typename BST<Value_Type, _Compare>::BSTNode *left, typename BST<Value_Type, _Compare>::BSTNode *right)
    {
        if (left == NULL)
            return right;
        if (right == NULL)
            return left;
        typename BST<Value_Type, _Compare>::BSTNode* result;
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

    typename BST<Value_Type, _Compare>::BSTNode* Add(typename BST<Value_Type, _Compare>::BSTNode *t, int x, int y, typename BST<Value_Type, _Compare>::BSTNode* parent)
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

    typename BST<Value_Type, _Compare>::BSTNode* Erase(typename BST<Value_Type, _Compare>::BSTNode* t, int x)
    {
        if (t == NULL)
            return NULL;
        if (t -> x == x)
        {
            typename BST<Value_Type, _Compare>::BSTNode* result = merge(t -> left, t -> right);
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

    int GetAt(typename BST<Value_Type, _Compare>::BSTNode *t, int k)
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
        BST<Value_Type, _Compare>::head = Add(BST<Value_Type, _Compare>::head, x, rand(), NULL);
        BST<Value_Type, _Compare>::head -> parent = NULL;
    }

    void Erase(int x)
    {
        BST<Value_Type, _Compare>::head = Erase(BST<Value_Type, _Compare>::head, x);
        if (BST<Value_Type, _Compare>::head != NULL)
            BST<Value_Type, _Compare>::head -> parent = NULL;
    }

    int GetAt(int k)
    {
        return GetAt(BST<Value_Type, _Compare>::head, k);
    }
};

template<class Value_Type, typename _Compare = less<Value_Type> >
class AVLTree:public BST<Value_Type, _Compare>
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

    int GetHeight(typename BST<Value_Type, _Compare>::BSTNode* t)
    {
        if (t == NULL)
            return 0;
        return static_cast<TNode*>(t) -> height;
    }

    void Update(typename BST<Value_Type, _Compare>::BSTNode* t)
    {
        if (t != NULL)
            static_cast<TNode*>(t) -> height = std::max(GetHeight(t -> left), GetHeight(t -> right)) + 1;
    }

    int Diff(typename BST<Value_Type, _Compare>::BSTNode* t)
    {
        if (t == NULL)
            return 0;
        return GetHeight(t -> left) - GetHeight(t -> right);
    }

    typename BST<Value_Type, _Compare>::BSTNode* SmallLeftRotation(typename BST<Value_Type, _Compare>::BSTNode* a)
    {
        typename BST<Value_Type, _Compare>::BSTNode* b = a -> right;
        typename BST<Value_Type, _Compare>::BSTNode* middle = b -> left;
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

    typename BST<Value_Type, _Compare>::BSTNode* BigLeftRotation(typename BST<Value_Type, _Compare>::BSTNode *a)
    {
        typename BST<Value_Type, _Compare>::BSTNode* b = a -> right;
        typename BST<Value_Type, _Compare>::BSTNode* c = b -> left;
        typename BST<Value_Type, _Compare>::BSTNode* cleft = c -> left;
        typename BST<Value_Type, _Compare>::BSTNode* cright = c -> right;
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

    typename BST<Value_Type, _Compare>::BSTNode* SmallRightRotation(typename BST<Value_Type, _Compare>::BSTNode* a)
    {
        typename BST<Value_Type, _Compare>::BSTNode* b = a -> left;
        typename BST<Value_Type, _Compare>::BSTNode* middle = b -> right;
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

    typename BST<Value_Type, _Compare>::BSTNode* BigRightRotation(typename BST<Value_Type, _Compare>::BSTNode *a)
    {
        typename BST<Value_Type, _Compare>::BSTNode* b = a -> left;
        typename BST<Value_Type, _Compare>::BSTNode* c = b -> right;
        typename BST<Value_Type, _Compare>::BSTNode* cleft = c -> left;
        typename BST<Value_Type, _Compare>::BSTNode* cright = c -> right;
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

    void Balance(typename BST<Value_Type, _Compare>::BSTNode *t)
    {
        typename BST<Value_Type, _Compare>::BSTNode *parent = t -> parent;
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
            BST<Value_Type, _Compare>::head = t;
        else
        {
            if (left)
                parent -> left = t;
            else
                parent -> right = t;
        }
    }

    void Restore(typename BST<Value_Type, _Compare>::BSTNode *t)
    {
        typename BST<Value_Type, _Compare>::BSTNode* current = t;
        while (current != NULL)
        {
            Update(current);
            Balance(current);
            current = current -> parent;
        }
    }

    pair<typename BST<Value_Type, _Compare>::BSTNode*, typename BST<Value_Type, _Compare>::BSTNode*> Add(typename BST<Value_Type, _Compare>::BSTNode *t, bool close, int x)
    {
        if (t == NULL)
            return make_pair(new TNode(x, close, NULL), (typename BST<Value_Type, _Compare>::BSTNode*)NULL);
        if (x == t -> x)
            return make_pair(t, (typename BST<Value_Type, _Compare>::BSTNode*)NULL);
        typename BST<Value_Type, _Compare>::BSTNode *current = t;
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

    typename BST<Value_Type, _Compare>::BSTNode* Erase(typename BST<Value_Type, _Compare>::BSTNode* t)
    {
        if (t -> left == NULL)
        {
            typename BST<Value_Type, _Compare>::BSTNode* result = t -> right;
            t -> right = NULL;
            if (result != NULL)
                result -> parent = t -> parent;
            delete t;
            return result;
        }
        else
        {
            typename BST<Value_Type, _Compare>::BSTNode* result = max(t -> left);
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
        pair<typename BST<Value_Type, _Compare>::BSTNode*, typename BST<Value_Type, _Compare>::BSTNode*> result = Add(BST<Value_Type, _Compare>::head, close, x);
        BST<Value_Type, _Compare>::head = result.first;
        Restore(result.second);
    }

    void Erase(int x)
    {
        typename BST<Value_Type, _Compare>::BSTNode* t = BST<Value_Type, _Compare>::Find(x);
        if (t == NULL)
            return;
        if (t == BST<Value_Type, _Compare>::head)
        {
            BST<Value_Type, _Compare>::head = Erase(BST<Value_Type, _Compare>::head);
            if (BST<Value_Type, _Compare>::head != NULL)
            {
                if (BST<Value_Type, _Compare>::head -> left != NULL)
                    Restore(max(BST<Value_Type, _Compare>::head -> left));
                else
                    Restore(BST<Value_Type, _Compare>::head);
            }
        }
        else
            if (t -> parent -> left == t)
            {
                typename BST<Value_Type, _Compare>::BSTNode* parent = t -> parent;
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
                typename BST<Value_Type, _Compare>::BSTNode* parent = t -> parent;
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
        for (typename BST<Value_Type, _Compare>::BSTNode *current = BST<Value_Type, _Compare>::min(); current != NULL; current = BST<Value_Type, _Compare>::next(current))
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
    Treap<int> tree;
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

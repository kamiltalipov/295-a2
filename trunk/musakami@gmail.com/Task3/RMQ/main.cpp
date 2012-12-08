#include <iostream>
#include <vector>
#include <limits>

using namespace std;

class Tree
{
    int size;
    int size_2;
    vector<int> data;
    vector<int> add;

    int findmin(int index, int l, int r, int &lq, int &rq)
    {
        push(index);
        if (r < lq || l > rq)
            return numeric_limits<int>::max();
        if (l >= lq && r <= rq)
            return data[index];
        else
        {
            return min(findmin(index << 1, l, (l + r) / 2, lq, rq), findmin((index << 1) + 1, (l + r) / 2 + 1, r, lq, rq));
        }
    }

    void setadd(int index, int &value, int l, int r, int &lq, int &rq)
    {
        if (r < lq || l > rq)
            return;
        if (l >= lq && r <= rq)
            add[index] += value;
        else
        {
            setadd(index << 1, value, l, (l + r) / 2, lq, rq);
            setadd((index << 1) + 1, value, (l + r) / 2 + 1, r, lq, rq);
        }
    }

    void push(int index)
    {
        data[index] += add[index];
        if (index < size_2)
        {
            add[index << 1] += add[index];
            add[(index << 1) + 1] += add[index];
        }
        add[index] = 0;
    }

public:

    Tree(int n)
    {
        int k = 1;
        for (; k < n; k <<= 1);
        size_2 = k;
        size = k << 1;
        data.resize(size, 0);
        add.resize(size, 0);
    }

    int Min(int lq, int rq)
    {
        return findmin(1, 0, size_2 - 1, lq, rq);
    }

    void Add(int l, int r, int value)
    {
        setadd(1, value, 0, size_2 - 1, l, r);
    }

   /* void Set(int index, int value)
    {
        index = size_2 + index;
        data[index] = value;
        while (index != 1)
        {
            index >>= 1;
            data[index] = min(data[index << 1], data[(index << 1) + 1]);
        }
    }*/
};

int main()
{
    int n, m;
    cin >> n >> m;
    Tree t(n);
    for (int i = 0; i < m; i++)
    {
        int k, l, r;
        cin >> k >> l >> r;
        if (k == 0)
        {
            int value;
            cin >> value;
            t.Add(l, r, value);
        }
        else
        {
            cout << t.Min(l, r) << endl;
        }
    }
    return 0;
}

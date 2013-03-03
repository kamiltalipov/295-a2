#include <iostream>
using std :: cin;
using std :: cout;
#include <vector>
using std :: vector;

class FenwickTree
{
public:
    FenwickTree (size_t size)
        :
        treep (size, 0)
    {
    }

    FenwickTree (const vector<int>& v)
        :
        treep (v.size ())
    {
        for (size_t i = 0; i < v.size (); ++i)
            modify (i, v[i]);
    }

    int sum (int left, int right);
    void modify (int i, int delta);

private:
    vector<int> treep;

    int sum (int i)
    {
        int res = 0;
        for (; i >= 0; i = (i & (i + 1)) - 1)
            res += treep[i];

        return res;
    }
};

int FenwickTree :: sum (int left, int right)
{
    if (!left)
        return sum (right);
    if (left > right)
        return 0;
    return sum (right) - sum (left - 1);
}

void FenwickTree :: modify (int i, int delta)
{
    for (; i < treep.size (); i |= i + 1)
        treep[i] += delta;
}

int main ()
{
    size_t n;
    cin >> n;
    FenwickTree tr (n);
    int res = 0;
    for (size_t i = 0; i < n; ++i)
    {
        int cur;
        cin >> cur;
        tr.modify (cur - 1, 1);
        res += tr.sum (cur, n - 1);
    }

    cout << res;

    return 0;
}

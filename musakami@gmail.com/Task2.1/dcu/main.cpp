#include <iostream>
#include <vector>

using namespace std;

class dcu
{
    vector<int> anc;
    vector<int> size;
public:
    dcu(int n)
    {
        anc.resize(n);
        size.resize(n);
        for (int i = 0; i < n; i++)
        {
            anc[i] = i;
            size[i] = 1;
        }

    }

    int root(int v)
    {
        if (anc[v] == v)
            return v;
        return anc[v] = root(anc[v]);
    }

    void join(int v, int u)
    {
        int rv = root(v);
        int ru = root(u);
        if (rv != ru)
        {
            if (size[rv] < size[ru])
                swap(rv, ru);
            anc[ru] = rv;
            size[rv] += size[ru];
        }
    }

    bool check(int v, int u)
    {
        return root(v) == root(u);
    }
};

int main()
{
    int n;
    cin >> n;
    dcu uni(n);
    int m;
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        int k1, k2, k3;
        cin >> k1 >> k2 >> k3;
        if (k1 == 0)
        {
            uni.join(k2, k3);
        }
        else
        {
            cout << (uni.check(k2, k3) ? "YES" : "NO") << endl;
        }
    }
    return 0;
}

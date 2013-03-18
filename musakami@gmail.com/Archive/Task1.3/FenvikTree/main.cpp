#include <iostream>
#include <vector>

using namespace std;

class FTree
{
    vector<int> v;
public:
    FTree(int n)
    {
        v.resize(n, 0);
    }

    void Add(int index, int value)
    {
        while (index < v.size())
        {
            v[index] += value;
            index = (index + 1) | index;
        }
    }

    int Sum(int index)
    {
        int result = 0;
        while (index >= 0)
        {
            result += v[index];
            index = ((index + 1) & index) - 1;
        }
        return result;
    }
};

int main()
{
    int n;
    cin >> n;
    FTree tree(n);
    vector<int> v(n + 1);
    for (int i = 0; i < n; i++)
    {
        int k;
        cin >> k;
        v[k] = i;
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        tree.Add(v[i], 1);
        ans += tree.Sum(n - 1) - tree.Sum(v[i]);
    }
    cout << ans;
    return 0;
}

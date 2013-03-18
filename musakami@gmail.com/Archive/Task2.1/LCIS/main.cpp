#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

int n_global = 0;

class Tree
{
    int size;
    int size_2;
    vector<int> data;
    vector<int> values;

    int findmax(int index, int l, int r, int &lq, int &rq)
    {
        if (r < lq || l > rq)
            return numeric_limits<int>::min();
        if (l >= lq && r <= rq)
            return data[index];
        else
        {
            int maxleft = findmax(index << 1, l, (l + r) / 2, lq, rq);
            int maxright = findmax((index << 1) + 1, (l + r) / 2 + 1, r, lq, rq);
            if (values[maxleft] >= values[maxright])
                return maxleft;
            else
                return maxright;
        }
    }

public:

    Tree(int n = n_global)
    {
        int k = 1;
        for (; k < n; k <<= 1);
        size_2 = k;
        size = k << 1;
        data.resize(size);
        for (int i = size_2; i < size; i++)
            data[i] = i - size_2;
        values.resize(size_2);
        for (int i = size_2 - 1; i > 0; i--)
        {
            if (values[data[i << 1]] >= values[data[(i << 1) + 1]])
                data[i] = data[i << 1];
            else
                data[i] = data[(i << 1) + 1];
        }
    }

    int Max(int lq, int rq)
    {
        return findmax(1, 0, size_2 - 1, lq, rq);
    }

    void Set(int index, int value)
    {
        values[index] = value;
        index = size_2 + index;
        while (index != 1)
        {
            index >>= 1;
            if (values[data[index << 1]] >= values[data[(index << 1) + 1]])
                data[index] = data[index << 1];
            else
                data[index] = data[(index << 1) + 1];
        }
    }
};

bool Comparer(const pair<int, vector<int> > &a, const pair<int, vector<int> > &b)
{
    return a.first < b.first;
}

int main()
{
    int n, m;
    cin >> n >> m;
    n_global = n + 1;
    vector<int> v1, v2;
    for (int i = 0; i < n; i++)
    {
        int k1;
        cin >> k1;
        v1.push_back(k1);
    }
    for (int i = 0; i < m; i++)
    {
        int k2;
        cin >> k2;
        v2.push_back(k2);
    }
    vector<pair<int, vector<int> > > pairs;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (v1[i] == v2[j])
            {
                bool found = false;
                for (int k = 0; k < pairs.size(); k++)
                {
                    if (v1[i] == pairs[k].first)
                    {
                        found = true;
                        pairs[k].second.push_back(i);
                        break;
                    }
                }
                if (!found)
                {
                    vector<int> temp;
                    temp.push_back(i);
                    pairs.push_back(make_pair(v1[i], temp));
                }
                break;
            }
        }
    }
    sort(pairs.begin(), pairs.end(), Comparer);
    vector<vector<int> > dp(n + 1);
    vector<vector<pair<int, int> > > prev(n + 1);
    vector<Tree> maxs(m + 1);
    for (int i = 0; i <= n; i++)
    {
        dp[i].resize(m + 1, 0);
        prev[i].resize(m + 1, make_pair(0, 0));
    }
    for (int i = 0; i < pairs.size(); i++)
    {
        for (int j = pairs[i].second.size() - 1; j >= 0; j--)
        {
            int index = pairs[i].second[j] + 1;
            for (int k = 1; k <= m; k++)
            {
                if (v1[index - 1] != v2[k - 1])
                {
                    dp[index][k] = dp[index][k - 1];
                    prev[index][k] = prev[index][k - 1];
                    maxs[k].Set(index, dp[index][k]);
                }
                else
                {
                    int maxindex = maxs[k - 1].Max(0, index - 1);
                    dp[index][k] = dp[maxindex][k - 1] + 1;
                    prev[index][k] = make_pair(maxindex, k - 1);
                    maxs[k].Set(index, dp[index][k]);
                }
            }
        }
    }
    pair<int, int> maxindex;
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        if (dp[i][m] > ans)
        {
            ans = dp[i][m];
            maxindex = make_pair(i, m);
        }

    }
    cout << ans << endl;
    vector<int> ressequence;
    while (maxindex.first != 0)
    {
        ressequence.push_back(v1[maxindex.first - 1]);
        maxindex = prev[maxindex.first][maxindex.second];
    }
    for (int i = ressequence.size() - 1; i >= 0; i--)
        cout << ressequence[i] << " ";
    return 0;
}


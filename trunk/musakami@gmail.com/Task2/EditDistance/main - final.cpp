#include <iostream>
#include <string>
#include <string.h>
#include <vector>

using namespace std;

int solve(string &s1, string &s2, int l1, int r1, int l2, int r2, vector<pair<int, int> > &ans)
{
    if (l1 == r1)
    {
        if (r2 < l2)
        {
            ans.push_back(make_pair(l1, r2));
            return 1;
        }
        else
        {
            bool jump = false;
            for (int i = l2; i < r2; i++)
            {
                if (s1[i - 1] == s2[l1 - 1])
                    jump = true;
                if (jump)
                    ans.push_back(make_pair(l1, i));
                else
                    ans.push_back(make_pair(l1 - 1, i));
            }
            ans.push_back(make_pair(l1, r2));
            if (!jump && s1[r2 - 1] != s2[l1 - 1])
                return r2 - l2 + 1;
            return r2 - l2;
        }
    }
    int middle = (l1 + r1) / 2;
    int len = r2 - l2 + 1;
    vector<int> dleft[2];
    for (int i = 0; i < 2; i++)
        dleft[i].resize(len + 1, (1 << 31) - 1);
    for (int i = 0; i <= len; i++)
        dleft[0][i] = i;
    for (int i = l1; i <= middle; i++)
    {
        dleft[1][0] = i - l1 + 1;
        for (int j = 1; j <= len; j++)
        {
            dleft[1][j] = (1 << 31) - 1;
            if (s2[i - 1] == s1[l2 + j - 2])
            {
                dleft[1][j] = dleft[0][j - 1];
            }
            dleft[1][j] = min(dleft[1][j], dleft[1][j - 1] + 1);
            dleft[1][j] = min(dleft[1][j], dleft[0][j] + 1);
            dleft[1][j] = min(dleft[1][j], dleft[0][j - 1] + 1);
        }
        dleft[1].swap(dleft[0]);
    }
    vector<int> dright[2];
    for (int i = 0; i < 2; i++)
        dright[i].resize(len + 1, (1 << 31) - 1);
    for (int i = len; i >= 0; i--)
        dright[0][i] = len - i;
    for (int i = r1; i > middle; i--)
    {
        dright[1][len] = r1 - i + 1;
        for (int j = len - 1; j >= 0; j--)
        {
            dright[1][j] = (1 << 31) - 1;
            if (s2[i - 1] == s1[l2 + j - 1])
            {
                dright[1][j] = dright[0][j + 1];
            }
            dright[1][j] = min(dright[1][j], dright[1][j + 1] + 1);
            dright[1][j] = min(dright[1][j], dright[0][j] + 1);
            dright[1][j] = min(dright[1][j], dright[0][j + 1] + 1);
        }
        dright[1].swap(dright[0]);
    }
    int min = 0;
    int mincost = dleft[0][0] + dright[0][0];
    for (int i = 0; i <= len; i++)
    {
        if (dleft[0][i] + dright[0][i] < mincost)
        {
            min = i;
            mincost = dleft[0][i] + dright[0][i];
        }
    }
    solve(s1, s2, l1, middle, l2, l2 + min - 1, ans);
    solve(s1, s2, middle + 1, r1, l2 + min, r2, ans);
    return mincost;
}

int main()
{
    string a, b;
    cin >> a >> b;
    int lena = a.length();
    int lenb = b.length();
    vector<pair<int, int> >ans;
    ans.push_back(make_pair(0, 0));
    cout << solve(a, b, 1, lenb, 1, lena, ans)  << endl;
    for (int i = 1; i < ans.size(); i++)
    {
        if (ans[i].first == ans[i - 1].first)
            cout << "Delete from 1st string at " << ans[i].second << endl;
        else
            if (ans[i].second == ans[i - 1].second)
                cout << "Add " << b[ans[i].first - 1] << " to 1st string before " << ans[i].second + 1 << endl;
            else
                if (a[ans[i].second - 1] != b[ans[i].first - 1])
                    cout << "Change in the 1st string at " << ans[i].second << " to " << b[ans[i].first - 1] << endl;
    }
    return 0;
}

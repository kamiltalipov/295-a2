#include <iostream>
#include <string>
#include <string.h>
#include <vector>

using namespace std;

int main()
{
    string a, b;
    cin >> a >> b;
    int lena = a.length();
    int lenb = b.length();
    vector<vector<int> > dp(lena + 1);
    for (int i = 0; i <= lena; i++)
    {
        dp[i].resize(lenb + 1, (1 << 31) - 1);
    }
    for (int i = 0; i <= lena; i++)
        dp[i][0] = i;
    for (int i = 0; i <= lenb; i++)
        dp[0][i] = i;
    for (int i = 1; i <= lena; i++)
        for (int j = 1; j <= lenb; j++)
        {
            if (a[i - 1] == b[j - 1])
            {
                dp[i][j] = min(dp[i][j], dp[i - 1][j - 1]);
            }
            dp[i][j] = min(dp[i][j], dp[i][j - 1] + 1);
            dp[i][j] = min(dp[i][j], dp[i - 1][j] + 1);
            dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + 1);
        }
    cout << dp[lena][lenb] << endl;
    vector<pair<int, int> > ans;
    int i = lena, j = lenb;
    while (i != 0 || j != 0)
    {
        if (i > 0  && j > 0 && dp[i][j] == dp[i - 1][j - 1] + 1)
        {
            ans.push_back(make_pair(0, i));
            i--;
            j--;
            continue;
        }
        if (i > 0 && dp[i][j] == dp[i - 1][j] + 1)
        {
            ans.push_back(make_pair(1, i));
            i--;
            continue;
        }
        if (j > 0 && dp[i][j] == dp[i][j - 1] + 1)
        {
            ans.push_back(make_pair(2, j));
            j--;
            continue;
        }
        i--;
        j--;
    }
    for (int i = 0; i < ans.size(); i++)
    {
        if (ans[i].first == 0)
            cout << "Change 1st string at " << ans[i].second;
        if (ans[i].first == 1)
            cout << "Delete from 1st string at " << ans[i].second;
        if (ans[i].first == 2)
            cout << "Delete from 2nd string at " << ans[i].second;
        cout << endl;
    }
    return 0;
}

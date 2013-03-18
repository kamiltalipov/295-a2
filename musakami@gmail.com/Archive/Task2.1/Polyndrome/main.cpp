#include <iostream>
#include <string>
#include <string.h>
#include <vector>

using namespace std;

int main()
{
    string a;
    cin >> a;
    int len = a.length();
    vector<vector<int> > dp(2);
    for (int i = 0; i <= 1; i++)
        dp[i].resize(len + 1, 0);
    for (int i = 1; i <= len; i++)
    {
        dp[0].swap(dp[1]);
        for (int j = 1; j <= len; j++)
        {
            if (a[i - 1] == a[len - j])
                dp[1][j] = dp[0][j - 1] + 1;
            dp[1][j] = max(dp[1][j], max(dp[0][j], dp[1][j - 1]));
        }
    }
    vector<char> ans;
    for (int i = 0; i < len; i++)
    {
        if (dp[1][i] < dp[1][i + 1])
        {
            ans.push_back(a[i]);
        }
    }
    for (int i = 0; i * 2 < ans.size(); i++)
        ans[ans.size() - i - 1] = ans[i];
    for (int i = 0; i < ans.size(); i++)
        cout << ans[i];
    return 0;
}

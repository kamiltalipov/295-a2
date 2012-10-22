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
    vector<vector<int> > dp(len + 1);
    for (int i = 0; i <= len; i++)
        dp[i].resize(len + 1, 0);
    for (int i = 1; i <= len; i++)
        for (int j = 1; j <= len; j++)
        {
            if (a[i - 1] == a[len - j])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            dp[i][j] = max(dp[i][j], max(dp[i - 1][j], dp[i][j - 1]));
        }
    vector<char> ans;
    for (int i = 0; i < len; i++)
    {
        if (dp[len][i] < dp[len][i + 1])
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

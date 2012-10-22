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
    cout << dp[lena][lenb];
    return 0;
}

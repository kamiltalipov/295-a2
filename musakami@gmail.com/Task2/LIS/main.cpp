#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> data, dp(n + 1), prev(n);
    for (int i = 0; i < n; i++)
    {
        int k;
        cin >> k;
        data.push_back(k);
    }
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        int l = 0, r = ans + 1;
        while (r - l > 1)
        {
            int j = (l + r) / 2;
            if (j == 0 || data[dp[j]] < data[i])
                l = j;
            else
                r = j;
        }
        dp[l + 1] = i;
        prev[i] = dp[l];
        if (l == ans)
            ans++;
    }
    cout << ans << endl;
    vector<int> out;
    int current = dp[ans];
    for (int i = 0; i < ans; i++)
    {
        out.push_back(data[current]);
        current = prev[current];
    }
    for (int i = ans - 1; i >= 0; i--)
    {
        cout << out[i] << " ";
    }
    return 0;
}

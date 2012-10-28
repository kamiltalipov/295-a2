#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
	string s;
	vector < vector <int> > dp;
	vector <vector <string> > ans;
	int n;
	cin >> s;
	n = s.size();
	dp.resize(n);
	ans.resize(n);
	for (int i = 0; i < n; i++)
	{
		dp[i].resize(n);
		ans[i].resize(n);
	}
	for (int i = 0; i < n; i++)
	{
		dp[i][i] = 1;
		ans[i][i] = s[i];
	}
	for (int i = 1; i < n; i++)
	{
		for (int l = 0, r = i; l < n - i; l++, r++)
		{
			if (dp[l + 1][r] > dp[l][r - 1])
			{
				dp[l][r] = dp[l + 1][r];
				ans[l][r] = ans[l + 1][r];
			}
			else
			{
				dp[l][r] = dp[l][r - 1];
				ans[l][r] = ans[l][r - 1];
			}
			if (s[l] == s[r])
			{
				dp[l][r] = dp[l + 1][r - 1] + 2;
				ans[l][r] = s[l] + ans[l + 1][r - 1] + s[r];
			}
		}
	}
	cout << ans[0][n - 1];
	return 0;
}
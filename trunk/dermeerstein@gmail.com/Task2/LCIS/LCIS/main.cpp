#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

int main()
{
	int n, m;
	cin >> n;
	vector <int> a(n); 
	vector <vector <vector <int> > > dp(n + 1);
	for (int i = 0; i < n; i++)
		cin >> a[i];
	cin >> m;
	vector <int> b(m), c;
	for (int i = 0; i < m; i++)
		cin >> b[i];
	if (n <= m)
		c = a;
	else
		c = b;
	int mn = min(n, m);
	sort(c.begin(), c.end());
	for (int i = 0; i <= n; i++)
	{
		dp[i].resize(m + 1);
		for (int j = 0; j <= m; j++)
			dp[i][j].resize(mn + 1);
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			for (int k = 1; k <= mn; k++)
			{
				if (a[i - 1] == b[j - 1] && b[j - 1] == c[k - 1])
					dp[i][j][k] = dp[i - 1][j - 1][k - 1] + 1;
				dp[i][j][k] = max(dp[i][j][k], max(dp[i - 1][j][k], max(dp[i][j - 1][k], dp[i][j][k - 1])));
			}
		}
	}
	int ans = dp[n][m][mn];
	cout << ans << endl;
	c.resize(ans);
	int i = n, j = m, k = mn, cur_ind = ans - 1;
	while (i != 0 && j != 0 && k != 0)
	{
		if (dp[i][j][k] == dp[i - 1][j - 1][k - 1] + 1)
		{
			c[cur_ind] = a[i - 1];
			--i;
			--j;
			--k;
			--cur_ind;
		}
		else if (dp[i][j][k] == dp[i - 1][j][k])
			--i;
		else if (dp[i][j][k] == dp[i][j - 1][k])
			--j;
		else 
			--k;
	}
	for (int i = 0; i < ans; i++)
		cout << c[i] << " ";
	return 0;
}
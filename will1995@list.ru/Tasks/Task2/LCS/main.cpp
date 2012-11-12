#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <string>

using namespace std;

void lcs(string &a, string &b)
{

}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n, m;
	cin >> n;
	vector < int > a(n);
	for(int i = 0; i < n; i++)
		cin >> a[i];

	cin >> m;
	vector < int > b(m);
	for(int i = 0; i < m; i++)
		cin >> b[i];

	vector < vector < int > > dp(n + 1, vector <int> (m + 1));


	for (int i = 1; i < n; i++)
		for (int j = 1; j < m; j++)
		{
			if (a[i - 1] == b[j - 1])
				dp[i][j] = dp[i - 1][j - 1] + 1;
			else
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
		}

	vector < int > ans;
	int j = m - 1;
	int k = n - 1;
	int len = 0;
	while ((k != 0) && (j != 0))
	{

		if (a[k] == b[j])
		{
			ans.push_back(a[k]);
			k--;
			j--;
			len++;
		}
		else
			if (dp[k][j - 1] <= dp[k - 1][j])
				k--;
			else
				j--;
	}

	bool changed = false;
	
	//if (k != 0)
		while ((k >= 0) && !changed)
			{
			if ((a[k] == b[j]) && (ans.size() <= len))
			{
				ans.push_back(a[k]);
				changed = true;
			}
			k--;
		}

		k = 0;
//	if (j != 0)
		while ((j >= 0) && !changed)
		{
			if ((a[k] == b[j]) && (ans.size() <= len))
			{
				ans.push_back(a[k]);
				changed = true;
			}
			j--;
		}

	for(int i = ans.size() - 1; i >= 0; i--)
		cout << ans[i] << ' ';
	cout << endl;
	fclose(stdin);
	fclose(stdout);
	return 0;
}
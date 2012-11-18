#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
	string s;
	vector < vector <int> > dp;
	vector <vector <pair <int, int> > > pred;
	int n;
	cin >> s;
	n = s.size();
	dp.resize(n);
	pred.resize(n);
	for (int i = 0; i < n; i++)
	{
		dp[i].resize(n);
		pred[i].resize(n);
	}
	for (int i = 0; i < n; i++)
	{
		dp[i][i] = 1;
	}
	for (int i = 1; i < n; i++)
	{
		for (int l = 0, r = i; l < n - i; l++, r++)
		{
			if (dp[l + 1][r] > dp[l][r - 1])
			{
				dp[l][r] = dp[l + 1][r];
				pred[l][r] = make_pair(l + 1, r);
			}
			else
			{
				dp[l][r] = dp[l][r - 1];
				pred[l][r] = make_pair(l, r - 1);
			}
			if (s[l] == s[r])
			{
				dp[l][r] = dp[l + 1][r - 1] + 2;
				pred[l][r] = make_pair(l + 1, r - 1);
			}
		}
	}
	string st;
	int l = 0, r = n - 1;
	while (l <= r)
	{
		if (pred[l][r] == make_pair(l + 1, r))
			l = l + 1;
		else if (pred[l][r] == make_pair(l, r - 1))
			r = r - 1;
		else
		{
			st += s[l];
			l = l + 1;
			r = r - 1;
		}
	}
	for (int i = st.size() - 1 - dp[0][n - 1] % 2; i >= 0; i--)
	{
		st += st[i];
	}
	cout << st;
	return 0;
}
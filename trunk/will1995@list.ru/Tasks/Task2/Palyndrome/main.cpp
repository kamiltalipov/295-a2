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
	string s;
	cin >> s;
	string t;
	for (int i = s.size() - 1; i >= 0; i--)
		t.push_back(s[i]);

	vector < vector < int > > dp(s.size() + 1, s.size() + 1);

	for (int i = 1; i < s.size(); i++)
		for (int j = 1; j < t.size(); j++)
		{
			if (s[i] == t[j])
				dp[i + 1][j + 1] = dp[i][j] + 1;
			else
				dp[i + 1][j + 1] = max(dp[i][j + 1], dp[i + 1][j]);
		}

	string ans;
	int j = t.size();
	int k = j;
	int len = 0;
	while ((k != 0) && (j != 0))
	{

		if (s[k - 1] == t[j - 1])
		{
			ans.push_back(s[k - 1]);
			k--;
			j--;
			len++;
		}
		else
			if (dp[k - 1][j] > dp[k][j - 1])
				k--;
			else
				j--;
	}
	
	while (j >= 0)
	{
		if (s[k] == t[j])
			ans.push_back(s[k]);
		j--;
	}

	j = 0;

	while (k >= 0)
	{
		if (s[k] == t[j])
			ans.push_back(s[k]);
		k--;
	}

	cout << ans;
	fclose(stdin);
	fclose(stdout);
	return 0;
}
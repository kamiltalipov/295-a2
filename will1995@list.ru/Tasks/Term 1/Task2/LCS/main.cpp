#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <string>

using namespace std;

void lcis(vector <int> &a, vector <int> &b, vector<int> &ans)
{
	int n = a.size();
	int m = b.size();
	vector <int> dp (max (a.size(), b.size()) + 1, -1);
	vector <int> prev (max (a.size(), b.size()) + 1, -1);

	int indmax = 0, length = 0;
	for (int i = 0; i < m; i++)
	{
		int current = 0, last = -1;
		for (int j = 0; j < n; j++)
		{
			if ((a[j] == b[i]) && ((current + 1) > dp[j]))
			{
				dp[j] = current + 1;
				if (dp[j] > length)
				{
					length = dp[j];
					indmax = j;
				}
				prev[j] = last;
			}
			else
				if ((a[j] < b[i]) && (current < dp[j]))
				{
					current = dp[j];
					last = j;
				}
		}
	}

	//length++;
	length--;
	while (length != -1)
	{
		ans.push_back(a[length]);
		length = prev[length];
	}
	reverse(ans.begin(), ans.end());
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

	vector<int> ans;
	lcis(a, b, ans);

	for(int i = 1; i < ans.size(); i++)
	{
		if (ans[i] <= ans[i - 1])
		{
			ans.clear();
			lcis(b, a, ans);
			break;
		}
	}

	int tmp = 0;
	for(int i = 0; i < min(a.size(), ans.size()); i++)
		if (ans[tmp] == a[tmp])
			tmp++;

	if (tmp != ans.size())
	{
		ans.clear();
		lcis(b, |a, ans);
	}

	for (int i = 0; i < ans.size(); i++)
		cout << ans[i] << ' ';
	cout << endl;
	fclose(stdin);
	fclose(stdout);
	return 0;
}
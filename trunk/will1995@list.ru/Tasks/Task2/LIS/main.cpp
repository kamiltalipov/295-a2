#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>

using namespace std;

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int n, size = 0;
	cin >> n;

	vector < int > input (n);
	vector < int > prev (n);
	vector < int > dp(n + 1, 1 << 31 - 1);
	dp[0] = 1 << 31;
	vector < int > ind_min (n + 1, 0);

	for (int i = 0; i < n; i++)
	{
		cin >> input[i];
		int j = int (upper_bound(dp.begin(), dp.end(), input[i]) - dp.begin());
		if ((dp[j - 1] < input[i]) && (input[i] < dp[j]))
		{
			if (dp[j] == 1 << 31 - 1)
				size++;
			
			prev[i] = ind_min[j - 1];
			ind_min[j] = i;
			dp[j] = input[i];
		}
	}

	vector < int > ans;
	ans.push_back(dp[size]);
	int tmp = prev[ind_min[size]];
	size--;
	while (size != 0)
	{
		ans.push_back(input[tmp]);
		tmp = prev[tmp];
		size--;
	}

	for (int i = ans.size() - 1; i >= 0; i--)
		cout << ans[i] << ' ';
	cout << endl;
	fclose(stdin);
	fclose(stdout);
	return 0;
}
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


	vector <int> dp (max (n, m) + 1);
	vector <int> prev (max (n, m) + 1);

	int current = 0;
	int last = -1;
	int length = 0;
	int indmax = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			if ((a[i] == b[j]) && ((current + 1) > dp[j]))
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
				if ((a[i] > b[j]) && (current < dp[j]))
				{
					current = dp[j];
					last = j;
				}
		}


	vector <int> ans;
	ans.push_back(a[indmax]);
	cout << length << endl;
	length--;
	while (length != 0)
	{
		indmax = prev[indmax];
		ans.push_back(a[indmax]);
		length--;
	}

	for (int i = 0; i < ans.size(); i++)
		cout << ans[i] << ' ';
	cout << endl;
	fclose(stdin);
	fclose(stdout);
	return 0;
}
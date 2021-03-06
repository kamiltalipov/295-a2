#include <vector>
#include <iostream>
#include <limits.h>
#include <algorithm>
#include <cstdio>
using namespace std;

bool check(const vector < int >& ans, const vector < int >& arr)
{
	for (int i = 0; i < ans.size() - 1; ++i)
		if (ans[i] >= ans[i + 1])
			return false;
	int ind = 0;
	for (int i = 0; i < arr.size() && ind < ans.size(); ++i)
		if (ans[ind] == arr[i])
			++ind;
	return ind == ans.size();
}

void lcis(const vector < int >& a, const vector < int >& b, vector < int >& ans, bool tr = false)
{
	const int NONE = -1;
	ans.clear();
	if (!a.size() || !b.size())
		return;
	vector < int > d(a.size(), 0), p(a.size(), NONE);
	for (int bi = 0; bi < b.size(); ++bi)
	{
		int mx = 0, pr = NONE;
		for (int ai = 0; ai < a.size(); ++ai)
		{
			if (a[ai] == b[bi])
			{
				if (d[ai] < mx + 1)
				{
					d[ai] = mx + 1;
					p[ai] = pr;
				}
			}
			else if (d[ai] > mx && a[ai] < b[bi])
			{
				mx = d[ai];
				pr = ai;
			}
		}
	}
	int pos = max_element(d.begin(), d.end()) - d.begin();
	while (pos != NONE)
	{
		ans.push_back(a[pos]);
		pos = p[pos];
	}
	reverse(ans.begin(), ans.end());
	if (tr && (!check(ans, a) || !check(ans, b)))
		lcis(b, a, ans, true);
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n, m;
	cin >> n;
	vector < int > ar(n);
	for (int i = 0; i < n; ++i)
		cin >> ar[i];
	cin >> m;
	vector < int > br(m);
	for (int i = 0; i < m; ++i)
		cin >> br[i];
	vector < int > ans;
	lcis(ar, br, ans);
	cout << ans.size() << endl;
	for (int i = 0; i < ans.size(); ++i)
		cout << ans[i] << " ";
	return 0;
}
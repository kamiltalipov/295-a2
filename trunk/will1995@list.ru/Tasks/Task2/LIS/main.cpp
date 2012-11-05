#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std;

int lower_bound(int x, vector < int > &arr)
{
	int l = 0; 
	int r = arr.size();
	while (r - l > 1)
	{
		int mid = (l + r) / 2;
		if (arr[mid] < x)
			l = mid;
		else
			r = mid;
	}
	return l;
}


int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int n, size, max = 0;
	cin >> n;
	vector < int > array (n);
	vector < int > dp(n + 1, (1 << 31 - 1));
	vector < int > prev (n, 0);
	int pos;
	dp[0] = (1 << 32 - 1);;
	for (int i = 0; i < n; i++)
		cin >> array[i];

	size = 0;
	for(int i = 0; i < n; i++)
	{
		pos = lower_bound(array[i], dp);
		if (array[i] < dp[pos + 1])
		{
			prev[i] = pos + 1;
			if (pos == size)
			{
				size++;
				max = i;
			}
			dp[pos + 1] = array[i];
		}
	}

	array.clear();
	while (max >= 0)
	{
		if ((prev[max] == size))
		{
			array.push_back(dp[prev[max]]);
			size--;
		}
		max--;
	}

	for(int i = array.size() - 1; i >= 0; i--)
		cout << array[i] << ' ';
	cout << endl;
	fclose(stdin);
	fclose(stdout);
	return 0;
}
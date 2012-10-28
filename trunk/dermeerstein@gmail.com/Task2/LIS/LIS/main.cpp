#include <iostream>
#include <vector>

using namespace std;

int main()
{
	vector <int> dp, pred, ans;
	vector <int> nums;
	int n, max_len, tmp, left, right, middle;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> tmp;
		nums.push_back(tmp);
	}
	dp.resize(n + 1);
	pred.resize(n);
	max_len = 0;
	for (int i = 0; i < n; i++)
	{
		left = 0;
		right = max_len + 1;
		while (right - left > 1)
		{
			middle = (left + right) / 2;
			if (nums[dp[middle]] < nums[i])
				left = middle;
			else
				right = middle;
		}
		pred[i] = (left == 0 ? -1 : dp[left]);
		if (max_len < left + 1)
			dp[left + 1] = i;
		else if (nums[i] < nums[dp[left + 1]]) 
			dp[left + 1] = i;
		max_len = max(max_len, left + 1);
	}
	//cout << max_len << endl;
	int ind = dp[max_len];
	while (ind != -1)
	{
		ans.push_back(nums[ind]);
		ind = pred[ind];
	}
	for (int i = ans.size() - 1; i >= 0; i--)
	{
		cout << ans[i] << " ";
	}
	return 0;
}
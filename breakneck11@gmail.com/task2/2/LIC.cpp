#include <iostream>
#include <vector>
#include <map>
#include <limits>
#include <algorithm>
using namespace std;

vector < int >* lic(const vector < int >& arr)
{
	vector < int > min_val_len_n(arr.size() + 1, INT_MAX),
		pred_n(arr.size() + 1, -1), pred_a(arr.size() + 1, -1);
	min_val_len_n[0] = INT_MIN;
	for (int i = 0, j; i < arr.size(); ++i)
	{
		j = upper_bound(min_val_len_n.begin(), min_val_len_n.end(), arr[i]) - min_val_len_n.begin();
		if (min_val_len_n[j - 1] < arr[i] && arr[i] < min_val_len_n[j])
		{
			min_val_len_n[j] = arr[i];
			pred_n[j] = i;
			pred_a[i] = pred_n[j - 1];
		}
	}
	int len = 0;
	for (int i = 1; i <= arr.size(); ++i)
		if (pred_n[i] != -1)
			len = i;
		else
			break;
	vector < int > *ans = new vector < int > ();
	for (int i = pred_n[len]; i >= 0; i = pred_a[i])
		ans->push_back(arr[i]);
	reverse(ans->begin(), ans->end());
	return ans;
}

int main()
{
	const int n = 4;
	int _a[] = {2, 4, 3, 5};
	vector < int > a(_a, _a + n);
	vector < int > *ans = lic(a);
	for (int i = 0; i < ans->size(); ++i)
		cout << ans->at(i) << " ";
	cout << endl;
	delete ans;
	system("pause");
	return 0;
}
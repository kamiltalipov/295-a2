#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> LIS(vector<int>& a)
{
	int n = a.size();
	vector<int> prev(n,-1);
	vector<int> min_last(1);
	vector<int> d(1,-1);
	for (int i = 0; i < n; ++i) {
		int length = lower_bound(min_last.begin()+1,min_last.end(),a[i])-min_last.begin();
		if (length == min_last.size()) {
			min_last.push_back(a[i]);
			d.push_back(i);
		}
		else {
			min_last[length] = a[i];
			d[length] = i;
		}
		prev[i] = d[length-1];
	}

	vector<int> result;
	for (int i = d.back(); i >= 0; i = prev[i])
		result.push_back(a[i]);
	reverse(result.begin(),result.end());
	return result;
}

void check()
{
	int n;
	cin >> n;

	vector<int> a(n);
	for (int i = 0; i < n; ++i) cin >> a[i];

	vector<int> b = LIS(a);
	for (int i = 0; i < b.size(); ++i) cout << b[i] << ' ';
}

int main()
{
	check();
	_CrtDumpMemoryLeaks();
	return 0;
}
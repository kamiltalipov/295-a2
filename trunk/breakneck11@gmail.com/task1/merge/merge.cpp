#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

int swap_merge(vector < int > &arr, int l, int r)
{
	if (l + 1 >= r) return 0;
	if (l + 2 == r)
		if (arr[l] <= arr[r - 1]) return 0;
		else
		{
			swap(arr[l], arr[r - 1]);
			return 1;
		}
	const int mid = (l + r) >> 1;
	int ans = swap_merge(arr, l, mid) + swap_merge(arr, mid, r);
	vector < int > mv;
	int i, j;
	for (i = l, j = (l + r) >> 1; i < mid && j < r;)
		if (arr[i] <= arr[j])
			mv.push_back(arr[i++]);
		else
			mv.push_back(arr[j++]), ans += mid - i;
	for (; i < mid;  ++i) mv.push_back(arr[i]);
	for (; j < r; ++j) mv.push_back(arr[j]);
	for (i = 0; i + l < r; ++i)
        arr[l + i] = mv[i];
	return ans;
}

int main()
{
	vector < int > v;
	for (int i = 0; i < 10; ++i)
		v.push_back(10 - i);
	cout << swap_merge(v, 0, v.size()) << endl;
	for (int i = 0; i < 10;)
		cout << v[i++] << " ";
	cout << endl;
	system("pause");
	return 0;
}

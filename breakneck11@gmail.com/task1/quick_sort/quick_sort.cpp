#include <iostream>
#include <vector>
#include <stack>
#include <fstream>
using namespace std;

template < typename T >
void quick_sort(vector < T > &arr, int L, int R)
{
	int i = L, j = R;
	const int x = arr[(L + R) >> 1];
	while (i <= j)
	{
		while (arr[i] < x) ++i;
		while (x < arr[j]) --j;
		if (i <= j)
			swap(arr[i++], arr[j--]);
	}
	if (i < R) quick_sort(arr, i, R);
	if (j > L) quick_sort(arr, L, j);
}

template < typename T >
void unrec_sort(vector < T > &arr, int L, int R)
{
	typedef pair < int, int > dint;
	stack < dint > rec;
	rec.push(dint(L, R));
	while (!rec.empty())
	{
		dint top = rec.top();
		rec.pop();
		int i = top.first, j = top.second;
		const int x = arr[(i + j) >> 1];
		while (i <= j)
		{
			while (arr[i] < x) ++i;
			while (x < arr[j]) --j;
			if (i <= j)
				swap(arr[i++], arr[j--]);
		}
		if (i < top.second) rec.push(dint(i, top.second));
		if (j > top.first) rec.push(dint(top.first, j));
	}
}

template < typename T >
int nth_element(vector < T >& arr, int L, int R, int k)
{
	if (L == R)
		return arr[L];
	int i = L, j = R;
	const int x = arr[(L + R) >> 1];
	while (i <= j)
	{
		while (arr[i] < x) ++i;
		while (x < arr[j]) --j;
		if (i <= j)
			swap(arr[i++], arr[j--]);
	}
	int nr = 0;
	while (nr < R && arr[nr] <= x)
		++nr;
	if (k <= nr)
		return nth_element(arr, L, nr - 1, k);
	else
		return nth_element(arr, nr, R, k - nr);
}

int main()
{
	vector < int > arr;
	ifstream inp("input.txt");
	ofstream out("output.txt");
	int n;
	inp >> n;
	arr.resize(n);
	for (int i = 0; i < n; ++i)
		inp >> arr[i];
	for (int i = 0; i < n; ++i)
		out << i + 1 << " - " << nth_element(arr, 0, n - 1, i + 1) << endl;
	return 0;
}
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> helpArray;

int mergesortwork(vector<int> &data, int l, int r)
{
	if (r != l)
	{
		int count = 0;
		count += mergesortwork(data, l, (l + r) / 2);
		count += mergesortwork(data, (l + r) / 2 + 1, r);
		int i, j, k, index;
		i = index = l;
		j = k = (l + r) / 2 + 1;
		while (i < k && j <= r)
		{
			if (data[i] <= data[j])
				helpArray[index++] = data[i++];
			else
			{
				helpArray[index++] = data[j++];
				count += k - i;
			}
		}
		while (i < k)
			helpArray[index++] = data[i++];
		while (j <= r)
			helpArray[index++] = data[j++];
		return count;
	}
	return 0;
}

int mergesort(vector<int> &data)
{
	helpArray.resize(data.size());
	int count = mergesortwork(data, 0, data.size() - 1);
	helpArray.swap(data);
	return count;
}

int bubblesort(vector<int> &data)
{
	int count = 0;
	for (int i = 0; i < data.size() - 1; i++)
		for (int j = 0; j < data.size() - 1 - i; j++)
			if (data[j] > data[j + 1])
			{
				swap(data[j], data[j + 1]);
				count++;
			}
	return count;
}

vector<int> first;

int main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int readable;
		cin >> readable;
		first.push_back(readable);
	}
	vector<int> copyfirst = first;
	cout << "inversions " << mergesort(first) << endl;
	cout << "bubble swaps " << bubblesort(copyfirst);
	return 0;
}
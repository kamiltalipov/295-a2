#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct oper
{
	int pos;
	char type, sym;
};

oper new_oper (int pos, char type, char sym)
{
	oper new_oper;
	new_oper.pos = pos;
	new_oper.type = type;
	new_oper.sym = sym;
	return new_oper;
}

void print (vector <oper> &arr)
{
	for (int i = 0; i < arr.size(); i++)
		if (arr[i].type == 1)
			cout << "Delete " << arr[i].sym << " from " << arr[i].pos << endl;
		else if (arr[i].type == 2)
			cout << "Change at pos " << arr[i].pos << " to " << arr[i].sym << endl;
		else
			cout << "Add " << arr[i].sym << " at " << arr[i].pos << endl;
}

int LevDist (string &a, int la, int ra, string &b, int lb, int rb, vector <oper> &ans)
{
	int n = ra - la + 1;
	int m = rb - lb + 1;

	//and now for something completely stupid
	if (n == 1) 
	{
		for (int i = lb; i < rb; i++)
			ans.push_back(new_oper(la + 1, 1, b[i]));
		return rb - lb;
	}

	if (m == 1)
	{
		for (int i = la; i < ra; i++)
			ans.push_back(new_oper(i, 0, a[i]));
		return ra - la;
	}
	
	if (m == 2)
	{
		int k = la;
		while ((k < ra) && (a[k] != b[lb]))
			k++;

		if (k == ra)
		{
			for(int i = la + 1; i < ra; i++)
				ans.push_back(new_oper(i, 0, a[i]));
			ans.push_back(new_oper(la + 1, 2, b[lb]));
			return ra - la;
		}
		for (int i = la; i < ra; i++)
			if (i != k)
				ans.push_back(new_oper(i, 0, a[i]));
		return ra - la - 1;
	}
	/*else
		if (n == 2)
		{
			int k = lb;
			while ((k < rb) && (a[k] != b[la]))
				k++;

			if (k == rb)
			{
				for(int i = lb + 1; i < rb; i++)
					ans.push_back(new_oper(i, 0, ' '));
				ans.push_back(new_oper(lb + 1, 1, b[la]));
				return rb - lb;
			}
			for (int i = lb; i < rb; i++)
				if (i != k)
					ans.push_back(new_oper(i, 0, ' '));
			return rb - lb - 1;
		}
		*///eos

	vector <int> arr[2];
	arr[0].resize(n);
	arr[1].resize(n);

	for (int i = 0; i < arr[0].size(); i++)
		arr[0][i] = i;
	int mid = (lb + rb) / 2;

	for (int i = 0; i <= mid - lb; i++)
	{
		arr[1][0] = arr[0][0] + 1;
		for (int j = 1; j < arr[0].size(); j++)
		{
			arr[1][j] = (a[j - 1] == b[i] ? arr[0][j - 1] : (min( min(arr[0][j], arr[1][j - 1]), arr[0][j - 1]) ) + 1);
		}
		
		swap(arr[0], arr[1]);
	}
	vector <int> left (arr[0].begin(), arr[0].end());
	
	int sz = arr[0].size() - 1;
	for (int i = sz; i >= 0; i--)
		arr[1][i] = sz - i;

	for (int i = 0; i <= (rb - lb - 1) / 2; i++)
	{
		arr[0][sz] = i + 1;
		for(int j = sz - 1; j >= 0; j--)
		{
			arr[0][j] = (a[la + j] == b[rb - i - 1] ? arr[1][j + 1] : (min( min(arr[1][j], arr[0][j + 1]), arr[1][j + 1]) ) + 1);
		}
		swap(arr[0], arr[1]);
	}
	vector <int> right (arr[1].begin(), arr[1].end());

	int min = 0;
	for (int i = 0; i < left.size(); i++)
		if ((left[min] + right[min]) > (left[i] + right[i]))
			min = i;

	return LevDist(a, la, (la + min), b, lb, mid, ans) + LevDist(a, (la + min), ra, b, mid, rb, ans);
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	string first, second;

	cin >> second;
	cin >> first;
	//int len = max(first.size(), second.size());

	vector < oper > ans;
	cout << LevDist(first, 0, first.size(), second, 0, second.size(), ans) << endl;
	print (ans);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
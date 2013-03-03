#include <iostream>
#include <vector>
#include <stdio.h>
#include <ctime>
#include <stack>

using namespace std;

void print(vector <int> Array)
{
	for(int i = 0; i < Array.size(); i++)
	{
		cout << Array[i] << " ";
	}
	cout << endl;
}

void check(vector <int> Array)
{
	for(int i = 1; i < Array.size(); i++)
	{
		if (Array[i] < Array[i - 1])
		{
			cout << "Fail. Array is unsorted.\n";
			break;
		}
	}
	cout << "Success. Array seems to be sorted.\n";
	print(Array);
}

void Partition(vector <int> &Array, int &i, int &j, int m)
{
	do
	{
		while (Array[i] < m)
			i++;

		while (Array[j] > m)
			j--;

		if (i <= j)
		{
			swap(Array[i], Array[j]);
			i++;
			j--;
		}
	}
	while (i <= j);
		
}

void Non_Recursive_Qsort(vector <int> &Array)
{
	stack <int> Stack;
	Stack.push(Array.size() - 1);
	Stack.push(0);
	while (!Stack.empty())
	{
		int l = Stack.top();
		Stack.pop();
		int r = Stack.top();
		Stack.pop();

		int i = l;
		int j = r;
		int m = Array[l + rand()%(r - l + 1)];

		Partition(Array, i, j, m);

		if (i < r)
		{
			Stack.push(r);
			Stack.push(i);
		}

		if (l < j)
		{
			Stack.push(j);
			Stack.push(l);
		}
	}
}

void Recursive_Qsort(vector <int> &Array, int l, int r)
{
	int i = l;
	int j = r;
	int m = Array[l + rand()%(r - l + 1)];

	
	Partition(Array, i, j, m);
	
	if (i < r)
		Recursive_Qsort(Array, i, r);

	if (l < j)
		Recursive_Qsort(Array, l, j);
}

int Kth_Element(vector <int> &Array, int l, int r, int k)
{
	int i = l;
	int j = r;
	int m = l + rand()%(r - l + 1);

	Partition(Array, i, j, Array[m]);
	if (k > i)
		return Kth_Element(Array, i, r, k);
	else
		if (k < i)
			return Kth_Element(Array, l, j, k);
		else
			return i;
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	srand(time(NULL));
	int n, k;
	cin >> n >> k;
	vector <int> Main_Array(n);
	vector <int> Copied_Array(n);

	for(int i = 0; i < n; i++)
	{
		cin >> Main_Array[i];
		Copied_Array[i] = Main_Array[i];
	}


	cout << Kth_Element(Main_Array, 0, n - 1, k) << endl;
	
	//print(Main_Array);
	Recursive_Qsort(Main_Array, 0, n - 1);
	Non_Recursive_Qsort(Copied_Array);

	check(Main_Array);
	check(Copied_Array);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
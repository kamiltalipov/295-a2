#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <string>

using namespace std;

class Tree
{
public:
	int Sum ( int x );
	void Change ( int x, int val );
	Tree();
	Tree( int n );

private:
	vector <int> data;
};


Tree::Tree( int n )
{
	data.resize(n);
}

int Tree::Sum( int x )
{
	int sum = 0;
	while (x >= 0)
	{
		sum += data[x];
		x = (x & (x + 1)) - 1;
	}
	return sum;
}

void Tree::Change(int x, int val)
{
	while (x < data.size())
	{
		data[x] += val;
		x |= x + 1;
	}
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int n, ans = 0;
	cin >> n;
	vector <int> input (n);
	Tree Ftree(n + 1);
	for (int i = 0; i < n; i++)
	{
		cin >> input[i];
		Ftree.Change(input[i] - 1, 1);
		ans += Ftree.Sum(n - 1) - Ftree.Sum(input[i] - 1);
	}

	cout << ans << endl;

	fclose(stdin);
	fclose(stdout);
	return 0;
}
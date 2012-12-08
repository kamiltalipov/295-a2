#include <iostream>
#include <vector>

using namespace std;

class FenwickTree
{
public:
	FenwickTree(int size);
	FenwickTree(vector <int>& outside_vector);
	void Modify(int index, int delta);
	int GetSum(int left, int right);
private:
	int size;
	vector <int> buffer;
};


FenwickTree::FenwickTree(int size)
{
	this->size = size;
	buffer.resize(this->size);
}

FenwickTree::FenwickTree(vector <int>& outside_vector)
{
	size = outside_vector.size();
	buffer.resize(size);
	for (int i = 0; i < size; i++)
	{
		Modify(i, outside_vector[i]);
	}
}


void FenwickTree::Modify(int index, int delta)
{
	while (index < size)
	{
		buffer[index] += delta;
		index = index | (index + 1);
	}
}

int FenwickTree::GetSum(int left, int right)
{
	if (left != 0)
		return (GetSum(0, right) - GetSum(0, left - 1));
	else
	{
		int result = 0, index = right;
		while (index >= 0)
		{
			result += buffer[index];
			index = (index & (index + 1)) - 1;
		}
		return result;
	}
}

int main()
{
	/*int n, t;
	cin >> n;
	vector <int> Array(n);
	for (int i = 0; i < n; i++)
	{
		cin >> Array[i];
	}
	FenwickTree* tree = new FenwickTree(Array);
	int m, a, b, c;
	cin >> m;
	for (int i = 0; i < m; i++)
	{
		cin >> a >> b >> c;
		if (a == 1)
			cout << tree->GetSum(b, c) << endl;
		else
			tree->Modify(b, c);
	}*/
	int n, val, answer = 0;
	cin >> n;
	FenwickTree* tree = new FenwickTree(n + 1);
	for (int i = 0; i < n; i++)
	{
		cin >> val;
		answer += tree->GetSum(val + 1, n);
		tree->Modify(val, 1);
	}
	cout << answer;
	return 0;
}
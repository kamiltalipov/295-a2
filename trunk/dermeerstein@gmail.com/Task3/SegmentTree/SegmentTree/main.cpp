#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

class SegmentTree
{
public:
	SegmentTree(vector <int>& outside_vector);
	int GetMin(int left, int right);
	void Add(int left, int right, int add);

private:
	int size;
	static const int INF = 1e+9;
	struct Node
	{
		int min_val, left, right, add;
	};
	vector <Node> buffer;

	int _getMin(int left, int right, int index);
	void _add(int left, int right, int add, int index);
	void _push(int index);
};

SegmentTree::SegmentTree(vector <int>& outside_vector)
{
	int pw2 = pow((double) 2, ceil(log((double) outside_vector.size()) / log((double)2)));
	size = 2 * pw2 - 1;
	buffer.resize(size);
	for (int i = 0; i < outside_vector.size(); i++)
	{
		buffer[pw2 - 1 + i].min_val = outside_vector[i];
		buffer[pw2 - 1 + i].left = i;
		buffer[pw2 - 1 + i].right = i;
	}
	for (int i = outside_vector.size(); i < pw2; i++)
	{
		buffer[pw2 - 1 + i].min_val = INF;
		buffer[pw2 - 1 + i].left = i;
		buffer[pw2 - 1 + i].right = i;
	}

	for (int i = pw2 - 2; i >= 0; i--)
	{
		buffer[i].min_val = min(buffer[2 * i + 1].min_val, buffer[2 * i + 2].min_val);
		buffer[i].left = buffer[2 * i + 1].left;
		buffer[i].right = buffer[2 * i + 2].right;
	}
}

int SegmentTree::GetMin(int left, int right)
{
	return _getMin(left, right, 0);
}

int SegmentTree::_getMin(int left, int right, int index)
{
	if (right < buffer[index].left || left > buffer[index].right)
		return INF;
	else if (left <= buffer[index].left && right >= buffer[index].right)
	{
		_push(index);
		return buffer[index].min_val;
	}
	else
	{
		_push(index);
		return min(_getMin(left, right, 2 * index + 1), _getMin(left, right, 2 * index + 2));
	}
}

void SegmentTree::Add(int left, int right, int add)
{
	_add(left, right, add, 0);
}

void SegmentTree::_add(int left, int right, int add, int index)
{
	if (right < buffer[index].left || left > buffer[index].right)
		return;
	if (left <= buffer[index].left && right >= buffer[index].right)
		buffer[index].add += add;
	else
	{
		_add(left, right, add, 2 * index + 1);
		_add(left, right, add, 2 * index + 2);
		buffer[index].min_val = min(buffer[2 * index + 1].min_val + buffer[2 * index + 1].add, buffer[2 * index + 2].min_val + buffer[2 * index + 2].add);
	}
}

void SegmentTree::_push(int index)
{
	buffer[index].min_val += buffer[index].add;
	if (buffer[index].left != buffer[index].right)
	{
		buffer[2 * index + 1].add += buffer[index].add;
		buffer[2 * index + 2].add += buffer[index].add;
	}
	buffer[index].add = 0;
}

int main()
{
	vector <int> Array;
	int n;
	cin >> n;
	Array.resize(n);
	for (int i = 0; i < n; i++)
		cin >> Array[i];
	SegmentTree* tree = new SegmentTree(Array);
	int m, a, b, c;
	cin >> m;
	for (int i = 0; i < m; i++)
	{
		 cin >> a >> b >> c;
		 if (a == 0)
			 cout << tree->GetMin(b, c);
		 else
			 tree->Add(b, c, a);
	}

	return 0;
}
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class FenwikTree
{
	vector < int > fw;
	int sum(int r);
public:
	void Update(int pos, int val);
	int Sum(int l, int r) { return sum(r) - sum(l); }
	FenwikTree(int n) {	fw.assign(n, 0); }
};

void FenwikTree::Update(int pos, int val)
{
	for (register unsigned int i = pos; i < fw.size(); i = i | (i + 1))
		fw[i] += val;
}

int FenwikTree::sum(int r)
{
	int sum = 0;
	for (register int i = r - 1; i >= 0; i = (i & (i + 1)) - 1)
		sum += fw[i];
	return sum;
}

int main()
{
	ifstream inp("input.txt");
	int n;
	inp >> n;
	vector < int > arr(n);
	for (int i = 0; i < n; --arr[i++])
		inp >> arr[i];
	FenwikTree fw(n);
	int res = 0;
	for (register int i = 0; i < n; ++i)
	{
		res += fw.Sum(0, arr[i]);
		fw.Update(arr[i], 1);
	}
	cout << n * (n - 1) / 2 - res << endl;
	system("pause");
	return 0;
}
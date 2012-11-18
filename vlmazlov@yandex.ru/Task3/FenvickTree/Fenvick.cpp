#include <iostream>
#include <vector>
#include <crtdbg.h>
using namespace std;

class FenvickTree {
private:
	vector <int> buffer;
	int PrefixSum(int right);
public:
	FenvickTree(vector <int>& arr);
	FenvickTree(int size);
	int Sum(int left, int right);
	void update(int pos, int old, int changed);
};

int FenvickTree::PrefixSum(int right) {
	int res = 0;
	for (;right >= 0;right =  ((right & (right + 1)) - 1)) {
		res += buffer[right];
	}
	return res;
}

int FenvickTree::Sum(int left, int right) {
	return PrefixSum(right) - PrefixSum(left - 1);
}

void FenvickTree::update(int pos, int old, int changed) {
	int change = changed - old;
	for (;pos < buffer.size();pos = pos | (pos + 1)) {
		buffer[pos] += change;
	}
}

FenvickTree::FenvickTree(vector<int> &arr) {
	buffer.assign(arr.size(), 0);
	for (int i = 0;i < arr.size();i++) {
		update(i, 0, arr[i]);
	}
}

FenvickTree::FenvickTree(int size) {
	buffer.resize(size);
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n, a, inverse = 0;
	cin >> n;
	FenvickTree Tree(n);
	for (int i = 0;i < n;i++) {
		cin >> a;
		Tree.update(a - 1, 0, 1);
		inverse += Tree.Sum(a, n - 1);	
	}
	cout << inverse << endl;
	_CrtDumpMemoryLeaks;
	return 0;
} 
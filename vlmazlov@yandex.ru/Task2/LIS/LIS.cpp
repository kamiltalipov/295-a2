#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

const int MINF = numeric_limits <int>::min(), INF = numeric_limits <int>::max();

pair <int*, int> LIS(vector <int>& seq) {
	vector <int> lisEnd(seq.size() + 1, INF), prev(seq.size() + 1, -1), indexMin(seq.size() + 1, -1);
	lisEnd[0] = MINF;
	int upperBound;		
	for (int i = 0;i < seq.size();i++) {
		upperBound = upper_bound(lisEnd.begin(), lisEnd.end(), seq[i]) - lisEnd.begin();
		indexMin[upperBound] = i;
		prev[i] = indexMin[lower_bound(lisEnd.begin(), lisEnd.end(), seq[i]) - lisEnd.begin() - 1];	
		lisEnd[upperBound] = seq[i];
	}
	int lisLen;
	for (int i = 1;i < lisEnd.size();i++) {
		if (lisEnd[i] == INF) {
			lisLen = i - 1;
			break;
		}
		if (i == lisEnd.size() - 1) {
			lisLen = lisEnd.size() - 1;
		}
	}
	int* lis = new int[lisLen];
	int j = indexMin[lisLen];
	for (int i = 0;i < lisLen;i++) {
		*(lis + lisLen - 1 - i) = seq[j];
		j = prev[j];
	}
	return make_pair(lis, lisLen);
}

int main() {
	freopen ("input.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
	int n, a;
	vector <int> seq;
	cin >> n;
	for (int i = 0;i < n;i++) {
		cin >> a;
		seq.push_back(a);
	}
	pair <int*, int> lis = LIS(seq);
	cout << lis.second << endl;
	for (int i = 0;i < lis.second;i++) {
		cout << *(lis.first + i) << " ";
	}
	cout << endl;
	delete lis.first;
	return 0;
}
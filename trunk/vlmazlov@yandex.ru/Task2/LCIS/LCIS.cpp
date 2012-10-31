#include <iostream>
#include <vector>
#include <limits>
using namespace std;

const int MINF = numeric_limits <int>::min();

pair <int*, int> LCIS (vector <int>& seq1, vector <int> seq2) {
	vector <int> lcisLen(seq1.size(), 0), prev(seq1.size(), 0);
	int currLcisLen, lastUpd;
	for (int i = 0;i < seq2.size();i++) {
		currLcisLen = 0;
		lastUpd = MINF;
		for (int j = 0;j < seq1.size();j++) {
			if ((seq1[j] < seq2[i]) && (currLcisLen < lcisLen[j])) {
				currLcisLen = lcisLen[j];
				lastUpd = j;
			}
			if ((seq2[i] == seq1[j]) && (currLcisLen + 1 > lcisLen[j])) {
				lcisLen[j] = currLcisLen + 1;
				prev[j] = lastUpd;
			}
		}
	}
	int LCISLen = -1, endNum;
	for (int i =  0;i < lcisLen.size();i++) {
		if (lcisLen[i] > LCISLen) {
			LCISLen = lcisLen[i];
			endNum = i;
		}	
	}
	int* null = 0;
	if (LCISLen == 0) return make_pair(null, 0);
	else {
		int* Lcis = new int[LCISLen];
		int i = endNum, j = 0;
		while (i > MINF) {
			*(Lcis + LCISLen - j - 1) = seq1[i]; 
			j++;
			i = prev[i];
		}
		return make_pair(Lcis, LCISLen);
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n, a;
	vector <int> seq1, seq2;
	cin >> n;
	for (int i = 0;i < n;i++) {
		cin >> a;
		seq1.push_back(a);
	}
	cin >> n;
	for (int i = 0;i < n;i++) {
		cin >> a;
		seq2.push_back(a);
	}
	pair <int*, int> res = LCIS(seq1, seq2);
	cout << res.second << endl;
	for (int i = 0;i < res.second;i++) {
		cout << *(res.first + i) << " ";
	}
	cout << endl;
	delete res.first;
	return 0;
}
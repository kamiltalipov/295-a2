#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

vector<int> LCIS(const vector<int>& a, const vector<int>& b)
{
	vector<int> length(b.size());
	vector<int> index(b.size(),-1);
	vector<int> prev(a.size());
	int max_length = 0;
	int i_max_length;

	for (unsigned i = 0; i < a.size(); ++i) {
		int j_max = 0;
		int k = -1;
		for (unsigned j = 0; j < b.size(); ++j) {
			if (a[i] == b[j]) {
				length[j] = (k<0?0:length[k])+1;
				index[j] = i;
				if (length[j] >= length[j_max]) {
					j_max = j;
					if (k >= 0) prev[i] = index[k];
				}
			}
			if (a[i]>b[j] && length[j]>0 && (k<0||length[j]>length[k])) k = j;
		}
		if (length[j_max] > max_length) {
			max_length = length[j_max];
			i_max_length = i;
		}
	}
	vector<int> result(max_length,0);
	for (int i = i_max_length, k = max_length-1; k >= 0; i = prev[i], --k) result[k] = a[i];
	return result;
}

void check_increasing_subsequence(const vector<int>& seq, const vector<int>& subseq)
{
	for (int i = 0, j = 0; j < subseq.size(); ++i) {
		assert(i!=seq.size());
		if (seq[i] == subseq[j]) {
			++j;
			assert(j==subseq.size()||subseq[j]>subseq[j-1]);
		}
	}
}

void check()
{
	int a_length, b_length;
	cin >> a_length >> b_length;
	assert(a_length>=0&&b_length>=0);
	vector<int> a(a_length), b(b_length);

	for (int i = 0; i < a_length; ++i) cin >> a[i];
	for (int i = 0; i < b_length; ++i) cin >> b[i];

	vector<int> answer = LCIS(a,b);
	check_increasing_subsequence(a,answer);
	check_increasing_subsequence(b,answer);
	for (int i = 0; i < answer.size(); ++i) cout << answer[i] << ' ';
}

int main()
{
	check();
	_CrtDumpMemoryLeaks();
    return 0;
}
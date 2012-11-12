#include <iostream>
#include <vector>
#include <string>
using namespace std;

void LCS (string& a, string& b, string& lcs) {
	vector <vector <int> > lcsLen(a.length() + 1, b.length() + 1);// Предполагается обнуление по умолчанию
	for (int i = 1;i <= a.length();i++) {
		for (int j = 1;j <= b.length();j++) {
			if (a[i - 1] == b[j - 1]) {
				lcsLen[i][j] = lcsLen[i - 1][j - 1] + 1;
			}
			else lcsLen[i][j] = max(lcsLen[i - 1][j], lcsLen[i][j - 1]);
		}
	}
	int i = a.size(), j = b.size(), k = 0, ansLen = lcsLen[a.length()][b.length()];
	lcs.resize(ansLen);
	while (lcsLen[i][j] != 0) {
		if (a[i - 1] == b[j - 1]) {
			lcs[ansLen - k - 1] = a[i - 1];
			k++;
			i--;
			j--;
		} else if (lcsLen[i - 1][j] > lcsLen[i][j - 1]) {
			i--;
		} else j--;
	}
}

void LongestSubPalindrom(string& a, string& output) {
	string b(a.rbegin(), a.rend());
	string s;
	LCS(b, a, output);
	for (int i = 0 ;i < (output.length() / 2);i++) {
		output[output.length() - 1 - i] = output[i];
	} 
}

int main() {
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	string input;
	string output;
	cin >> input;
	LongestSubPalindrom(input, output);
	cout << output << endl;
	return 0;
}

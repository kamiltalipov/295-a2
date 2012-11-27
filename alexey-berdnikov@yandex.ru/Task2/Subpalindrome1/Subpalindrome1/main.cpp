#include <iostream>
#include <string>
#include <vector>
#include <cassert>

using namespace std;

string max_subpalindrome(const string& s)
{
	vector<vector<int>> d(s.length()+1);
	d[0].resize(s.length(),0);
	d[1].resize(s.length(),1);
	for (int len = 2; len <= s.length(); ++len) {
		d[len].resize(s.length()-len+1);
		for (int i = 0; i+len <= s.length(); ++i)
			if (s[i] == s[i+len-1])
				d[len][i] = d[len-2][i+1]+2;
			else
				d[len][i] = max(d[len-1][i],d[len-1][i+1]);
	}
	string result(d[s.length()][0],0);
	for (int len = s.length(), i = 0, k = 0; len >= 0; --len)
		if (s[i] == s[i+len-1]) {
			result[k++] = s[i++];
			--len;
		}
		else if (d[len][i] != d[len-1][i])
			++i;
	for (int k = result.length()>>1; k >= 0; --k) result[result.length()-k-1] = result[k];
	return result;
}

void check()
{
	string s;
	cin >> s;
	cout << max_subpalindrome(s);
}

int main()
{
	check();
	_CrtDumpMemoryLeaks();
    return 0;
}
#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef vector < vector < string > > din_table_type;

inline const string& maxpp(const string& a, const string& b)
{
	return a.length() > b.length() ? a : b;
}

const string& d(const string& str, din_table_type& dt, int L, int R)
{
	if (!dt[L][R].length())
	{
		if (L + 1 > R)
			dt[L][R] = "";
		else if (L + 1 == R)
			dt[L][R] = str[L];
		else
		{
			dt[L][R] = maxpp(d(str, dt, L + 1, R), d(str, dt, L, R - 1));
			if (str[L] == str[R - 1] && dt[L][R].length() < d(str, dt, L + 1, R - 1).length() + 2)
				dt[L][R] = str[L] + d(str, dt, L + 1, R - 1) + str[R - 1];
		}
	}
	return dt[L][R];
}

string LSP(const string& str)
{
	din_table_type data(str.length() + 1, vector < string > (str.length() + 1, ""));
	return d(str, data, 0, str.length());
}

int main()
{
	string s, ans;
	getline(cin, s);
	ans = LSP(s);
	cout << ans.length() << endl << ans << endl;
	return 0;
}
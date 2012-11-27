#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum MOVE : unsigned char { _L, _R, _LR };
typedef pair < int, MOVE > din_dat;
const din_dat NONE = make_pair(-1, _LR);
typedef vector < vector < din_dat > > din_table_type;

const din_dat& d(const string& str, din_table_type& dt, int L, int R)
{
	if (dt[L][R] == NONE)
	{
		if (L + 1 > R)
			dt[L][R] = make_pair(0, _LR);
		else if (L + 1 == R)
			dt[L][R] = make_pair(1, _LR);
		else
		{
			if (d(str, dt, L + 1, R).first >= d(str, dt, L, R - 1).first)
				dt[L][R] = make_pair(d(str, dt, L + 1, R).first, _L);
			else
				dt[L][R] = make_pair(d(str, dt, L, R - 1).first, _R);
			if (str[L] == str[R - 1] && dt[L][R].first < d(str, dt, L + 1, R - 1).first + 2)
				dt[L][R] = make_pair(d(str, dt, L + 1, R - 1).first + 2, _LR);
		}
	}
	return dt[L][R];
}

void put_ans(const string& str, const din_table_type& dt, vector < char >& res,
	int L, int R, int posL, int posR)
{
	if (posL + 1 > posR)
		return;
	if (posL + 1 == posR)
		return void(res[posL] = str[L]);
	if (dt[L][R].second == _L)
		put_ans(str, dt, res, L + 1, R, posL, posR);
	else if (dt[L][R].second == _R)
		put_ans(str, dt, res, L, R - 1, posL, posR);
	else
	{
		res[posL] = str[L], res[posR - 1] = str[R - 1];
		put_ans(str, dt, res, L + 1, R - 1, posL + 1, posR - 1);
	}
}

string LSP(const string& str)
{
	din_table_type data(str.length() + 1, vector < din_dat > (str.length() + 1, NONE));
	const int ans_len = d(str, data, 0, str.length()).first;
	vector < char > res_str(ans_len);
	put_ans(str, data, res_str, 0, str.length(), 0, ans_len);
	return string(res_str.begin(), res_str.end());
}

int main()
{
	string s, ans;
	getline(cin, s);
	ans = LSP(s);
	cout << ans.length() << endl << ans << endl;
	char c;
	cin >> c;
	return 0;
}
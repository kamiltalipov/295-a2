#include <iostream>
using std :: cin;
using std :: cout;
#include <string>
using std :: string;
#include <vector>
using std :: vector;
#include <algorithm>
using std :: max;

void findMaxCommonSubseq (const string& a, const string& b,
                          string& res)
{
    vector<vector<int> > ans (a.size () + 1, vector<int> (b.size () + 1, 0));
    for (size_t i = 0; i < a.size (); ++i)
        for (size_t j = 0; j < b.size (); ++j)
        {
            if (a[i] == a[j])
                ans[i + 1][j + 1] = ans[i][j] + 1;
			else
				ans[i + 1][j + 1] = max (ans[i][j + 1], ans[i + 1][j]);
        }	

    size_t i = a.size (), j = b.size ();
	while (i > 0 && j > 0)
    {
        if (a[i - 1] == b[j - 1])
        {
            res.push_back (a[i - 1]);
			--i;
			--j;
        }
		else if (ans[i - 1][j] > ans[i][j - 1])
            --i;
        else
            --j;
   }
}

inline void findMaxSubPolyndrom (const string& a, const string& revA,
                                 string& res)
{
    if (a.empty ())
       return;
    findMaxCommonSubseq (a, revA, res);
}

int main ()
{
	string str;
    cin >> str;
	string revStr (str.rbegin (), str.rend ());

    string res;
    findMaxSubPolyndrom (str, revStr, res);
    cout << res << '\n';

    cin.get ();
    cin.get ();

    return 0;
}

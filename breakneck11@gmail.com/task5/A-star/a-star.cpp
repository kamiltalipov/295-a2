#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <set>
#include <map>
using namespace std;

typedef int val_type;

inline pair < bool, val_type > change(const map < pair < int, int >, val_type >& mp, int x, int y, val_type nv)
{
	map < pair < int, int >, val_type >::const_iterator it = mp.find( make_pair(x, y) );
	return make_pair(it == mp.end() || it->second > nv, it == mp.end() ? 0 : it->second);
}

struct compr {
	inline bool operator() (const pair < pair < int, int >, val_type >& a, const pair < pair < int, int >, val_type >& b) const
	{
		return a.second < b.second;
	}
};

inline int get_ans(const string& s1, const string& s2)
{
	const int s1l = s1.length(), s2l = s2.length();
	map < pair < int, int >, val_type > ds;
	set < pair < pair < int, int >, val_type > , compr> q;
	q.insert( make_pair( make_pair(0, 0), 0) );
	ds[ make_pair(0, 0) ] = 0;
	pair < bool, val_type > rs; 
	while ( true )
	{
		int x = q.begin()->first.first, y = q.begin()->first.second;
		val_type wt = q.begin()->second;
		q.erase(q.begin());
		cout << "x = " << x << ", y = " << y << ", wt = " << wt << endl;
		if (x == s1l && y == s2l)
			return wt;
		if (x < s1l && y < s2l && s1[x] == s2[y] && (rs = change(ds, x + 1, y + 1,
			wt + (s1l + s2l - x - y - 2))).first)
		{
			printf("update x = %d, y = %d, old_val = %d, new_val = %d\n", x + 1, y + 1, rs.second,
				wt + s1l + s2l - x - y - 2);
			q.erase(make_pair( make_pair( x + 1, y + 1 ), rs.second ));
			q.insert(make_pair ( make_pair( x + 1, y + 1), wt + s1l + s2l - x - y - 2));
		}
		if (x < s1l && (rs = change(ds, x + 1, y, wt + (s1l + s2l - x - 1 - y) + 1)).first)
		{
			printf("update x = %d, y = %d, old_val = %d, new_val = %d\n", x + 1, y, rs.second,
				wt + s1l + s2l - x - y);
			q.erase(make_pair( make_pair(x + 1, y), rs.second));
			q.insert(make_pair( make_pair(x + 1, y), wt + (s1l + s2l - x - 1 - y) + 1));
		}
		if (y < s2l && (rs = change(ds, x, y + 1, wt + (s1l - s2l - x - y - 1) + 1)).first)
		{
			printf("update x = %d, y = %d, old_val = %d, new_val = %d\n", x, y + 1, rs.second,
				wt + s1l + s2l - x - y);
			q.erase(make_pair( make_pair(x, y + 1), rs.second));
			q.insert(make_pair( make_pair(x, y + 1), wt + (s1l + s2l - x  - y - 1) + 1));
		}
	}
}

int main()
{
	string s1, s2;
	cin >> s1 >> s2;
	cout << get_ans(s1, s2) << endl;
	return 0;
}

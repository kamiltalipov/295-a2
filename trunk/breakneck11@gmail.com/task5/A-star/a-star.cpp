#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
using namespace std;

enum type { LEFT = 0, RIGHT = 1, LR = 2 };
typedef int val_type;

inline pair < bool, val_type > change(const map < pair < int, int >, val_type >& mp, int x, int y, val_type nv)
{
	map < pair < int, int >, val_type >::const_iterator it = mp.find( make_pair(x, y) );
	return make_pair(it == mp.end() || it->second > nv, it == mp.end() ? 0 : it->second);
}

inline bool ls(const pair < pair < int, int >, val_type > a, 
			pair < pair < int, int >, val_type > b)
{
	return a.second < b.second;
}

int main()
{
	string s1, s2;
	cin >> s1 >> s2;
	//
	// Reading, now s1 and s2 are two strings of different texts
	//
	const int s1l = s1.length(), s2l = s2.length();
	map < pair < int, int >, val_type > ds;
	set < pair < pair < int, int >, val_type > , ls> q;
  q.insert( make_pair( make_pair(0, 0), 0) );
	ds[ make_pair(0, 0) ] = 0;
	while ( true )
	{
		int x = q.begin()->first.first, y = q.begin()->first.second;
		val_type wt = q.begin()->second;
		q.erase(q.begin());
		if (x == s1l && y == s2l)
		{
			cout << wt << endl;
			break;
		}
		pair < bool, val_type > rs = change(ds, x + 1, y + 1, wt + s1l + s2l - x - y - 2);
		if (x < s1l && y < s2l && s1[x] == s2[y] && rs.first)
		{
			q.erase(make_pair( make_pair( x + 1, y + 1 ), rs.second ));
			q.insert(make_pair ( make_pair( x + 1, y + 1), wt + s1l + s2l - x - y - 2));
		}
	  rs = change(ds, x + 1, y, wt + (s1l + s2l - x - 1 - y) + 1);
		if (x < s1l && rs.first)
		{
			q.erase(make_pair( make_pair(x + 1, y), rs.second));
			q.insert(make_pair( make_pair(x + 1, y), wt + (s1l + s2l - x - 1 - y) + 1));
		}
		rs = change(ds, x, y + 1, wt + (s1l + s2l - x - y - 1) + 1);
		if (y < s2l && rs.first)
		{
			q.erase(make_pair( make_pair(x, y + 1), rs.second));
			q.insert(make_pair( make_pair(x, y + 1), wt + (s1l + s2l - x  - y - 1) + 1));
		}
	}
	return 0;
}

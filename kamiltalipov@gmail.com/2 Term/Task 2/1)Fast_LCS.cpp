#include <cstdio>
#include <iostream>
using std :: cin;
using std :: cout;
#include <string>
using std :: string;
#include <map>
using std :: map;
#include <utility>
using std :: pair;
using std :: make_pair;
#include <queue>
using std :: priority_queue;
#include <algorithm>
using std :: max;

typedef pair<size_t, size_t> Position;

template<typename KEY, typename VALUE>
inline const VALUE& getVal (const map<KEY, VALUE>& m, const KEY& key, const VALUE& default_val)
{
    typename map<KEY, VALUE> :: const_iterator it = m.find (key);
    if (it != m.end ())
        return it->second;
    return default_val;
}

size_t calcLevenshtainDistance (const string& s1, const string& s2)
{
    const int INF = 2000000000;
    const Position start_v = make_pair (0, 0);
    const Position finish_v = make_pair (s1.size (), s2.size ());

    map<Position, int> distance;
    distance[start_v] = 0;
    priority_queue<pair<int, Position> > q;
    q.push (make_pair (0, start_v));
    while (!q.empty ())
    {
        const Position v = q.top ().second;
        const int cur_d = -q.top ().first;
        q.pop ();
        if (cur_d > getVal (distance, v, INF))
            continue;
        if (v == finish_v)
            break;

        const int dx[3] = {0, 1, 1};
        const int dy[3] = {1, 0, 1};
        for (size_t i = 0; i < 3; ++i)
        {
            const Position to = make_pair (v.first + dx[i], v.second + dy[i]);
            int len = 1;
            if (i == 2)
                len = s1[to.first - 1] != s2[to.second - 1] ? 1 : 0;

            if (to.first <= s1.size () && to.second <= s2.size ())
            {
                if (getVal (distance, v, INF) + len < getVal (distance, to, INF))
                {
                    distance[to] = distance[v] + len;
                    q.push (make_pair (-distance[to], to));
                }
            }
        }
    }

    return getVal (distance, finish_v, INF);
}

size_t findLCSLen (const string& s1, const string& s2)
{
    //return calcLevenshtainDistance(s1, s2);
    size_t lcsLen = max (s1.size (), s2.size ()) - calcLevenshtainDistance (s1, s2);
	return lcsLen <= max (s1.size (), s2.size ()) ? lcsLen : 0;
}


int main ()
{
    //freopen ("input.txt", "r", stdin);
    string s1, s2;
    cin >> s1 >> s2;

    cout << findLCSLen (s1, s2) << '\n';

    return 0;
}

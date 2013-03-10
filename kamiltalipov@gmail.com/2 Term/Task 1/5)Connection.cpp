#include <iostream>
using std :: cin;
using std :: cout;

#include "DSU.h"

int main ()
{
    size_t all_v = 0;
    cin >> all_v;
	DSU dsu (all_v);
    for (size_t v = 0; v < all_v; ++v)
    {
        size_t v_v = 0;
        cin >> v_v;
        for (size_t i = 0; i < v_v; ++i)
		{
			size_t cur_v;
            cin >> cur_v;
			dsu.union_sets (v, cur_v);
		}
    }

	size_t all_query = 0;
	cin >> all_query;
	for (size_t i = 0; i < all_query; ++i)
	{
		size_t v1, v2;
		cin >> v1 >> v2;
		if (dsu.find_set (v1) == dsu.find_set (v2))
			cout << "YES\n";
		else
			cout << "NO\n";
	}

    return 0;
}

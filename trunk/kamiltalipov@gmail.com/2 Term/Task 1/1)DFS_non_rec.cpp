#include <iostream>
using std :: cin;
using std :: cout;
#include <vector>
using std :: vector;
#include <stack>
using std :: stack;
#include <utility>
using std :: pair;
using std :: make_pair;

enum Color
{
    WHITE,
    GRAY,
    BLACK
};

int dfs (size_t start_v, const vector<vector<size_t> >& g,
          vector<Color>& colors,
		  vector<size_t>& order)
{
    if (colors[start_v] != WHITE)
        return -1;

    stack<pair<size_t, unsigned int> > st;
    st.push (make_pair (start_v, 0));
    while (!st.empty ())
    {
        pair<size_t, unsigned int>& top = st.top ();
        colors[top.first] = GRAY;
		bool need_remove = true;
        if (top.second < g[top.first].size ())
        {
            if (colors[g[top.first][top.second]] == WHITE)
            {
				need_remove = false;
                st.push (make_pair (g[top.first][top.second], 0));
                ++top.second;
            }
			else if (colors[g[top.first][top.second]] == GRAY) //have cycle
			{
				return -1;
			}
        }
        if (need_remove)
        {
            colors[top.first] = BLACK;
            order.push_back (top.first);
            st.pop ();
        }
    }

	return 0;
}

void topsort (const vector<vector<size_t> >& g, vector<size_t>& order)
{
    vector<Color> colors (g.size (), WHITE);
	order.clear ();
    for (size_t i = 0; i < g.size (); ++i)
        if (colors[i] == WHITE)
            if (dfs (i, g, colors, order) < 0)
			{
				order.clear ();
				return;
			}
}

int main ()
{
    size_t all_v = 0;
    cin >> all_v;
    vector<vector<size_t> > g (all_v, vector<size_t> ());
    for (size_t v = 0; v < all_v; ++v)
    {
        size_t v_v = 0;
        cin >> v_v;
        g[v].resize (v_v);
        for (size_t i = 0; i < v_v; ++i)
            cin >> g[v][i];
    }
    
	vector<size_t> order;
	topsort (g, order);
    if (order.empty ())
		cout << "Can't do topsort!\n";
	else
		for (size_t i = 0; i < order.size (); ++i)
			cout << order[i] << ' ';

	cin.get ();
	cin.get ();

    return 0;
}

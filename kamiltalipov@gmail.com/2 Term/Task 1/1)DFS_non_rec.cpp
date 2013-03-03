#include <iostream>
using std :: cin;
using std :: cout;
#include <vector>
using std :: vector;
#include <stack>
using std :: stack;

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
        return;

    stack<size_t> st;
    st.push (start_v);
    while (!st.empty ())
    {
        size_t v = st.top ();
        if (colors[v] == GRAY)
        {
			order.push_back (v);
            colors[v] = BLACK;
            st.pop ();
            continue;
        }
        colors[v] = GRAY;
        for (vector<size_t> :: const_iterator i = g[v].begin (); i != g[v].end (); ++i)
            if (colors[*i] == WHITE)
                st.push (*i);
			else if (colors[*i] == GRAY)
			{
				return -1;
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
	
    return 0;
}

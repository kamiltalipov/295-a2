#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

bool top_sort(const vector < vector < int > >& gr, vector < int >& top_sorted)
{
	const unsigned char WHITE = 0, GREY = 1, BLACK = 2;
	vector < unsigned char > marks(gr.size(), WHITE);
	stack < pair < int, int >, vector < pair < int, int > > > st;
	top_sorted.clear();
	for (size_t i = 0; i < gr.size(); ++i)
	{
		if (marks[i] == WHITE)
		{
			st.push(make_pair(i, 0));
			while (!st.empty())
			{
				int &v = st.top().first, &nv = st.top().second;
				marks[v] = GREY;
				if (nv < gr[v].size())
				{
					if (marks[gr[v][nv]] == GREY)
					{
						top_sorted.clear();
						return false;
					}
					else if (marks[gr[v][nv]] == WHITE)
					{
						st.push(make_pair(gr[v][nv++], 0));
					}
					else
						++nv;
				}
				else if (nv == gr[v].size())
				{
					marks[v] = BLACK;
					top_sorted.push_back(v);
					st.pop();
				}
			}
		}
	}
	reverse(top_sorted.begin(), top_sorted.end());
	return true;
}

int main()
{
	vector < vector < int > > gr;
	int n, m;
	cin >> n >> m;
	gr.resize(n);
	for (int i = 0, a, b; i < m; ++i)
	{
		cin >> a >> b;
		gr[a - 1].push_back(b - 1);
	}
	vector < int > sorted;
	if (!top_sort(gr, sorted))
	{
		cout << "No";
		return 0;
	}
	cout << "Yes" << endl;
	for (int i = 0; i < sorted.size(); ++i)
		cout << sorted[i] + 1 << " ";
	return 0;
}
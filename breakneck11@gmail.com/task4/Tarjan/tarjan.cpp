#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector < vector < int > > gr, ans;
vector < unsigned char > marks;
vector < int > upt;
stack < int, vector < int > > st;
vector < bool > in_stack;
int dtime = 0;
const unsigned int WHITE = 0, GREY = 1, BLACK = 2;

void dfs(int v)
{
	marks[v] = GREY;
	st.push(v);
	in_stack[v] = true;
	int cvertex_time = upt[v] = dtime++;
	for (int i = 0; i < gr[v].size(); ++i)
	{
		if ( marks[ gr[v][i] ] == WHITE)
			dfs( gr[v][i] );
		else if ( in_stack[ gr[v][i] ])
			upt[v] = min(upt[v], upt[gr[v][i]]);
	}
	if (cvertex_time == upt[v])
	{
		ans.push_back(vector < int> ());
		int cur_top;
		do
		{
			ans.back().push_back( cur_top = st.top() );
			in_stack[ st.top() ] = false;
			st.pop();
		} while (cur_top != v);
	}
	marks[v] = BLACK;
}

int main()
{
	int n, m;
	cin >> n >> m;
	gr.resize(n), marks.resize(n), upt.resize(n),
		in_stack.resize(n);
	for (int i = 0; i < n; ++i)
		if (marks[i] == WHITE)
			dfs(i);
	return 0;
}
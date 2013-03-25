#include <iostream>
#include <vector>
using namespace std;

vector < vector < int > > gr;
vector < int > tup;
vector < unsigned char > marks;
const unsigned char WHITE = 0, GREY = 1, BLACK = 2;
int dfs_time = 0;

void dfs(int v, const void (*foundBridge)(int, int), int p = -1)
{
	marks[v] = GREY;
	const int tin = tup[v] = dfs_time++;
	for (int i = 0; i < gr[v][i]; ++i)
	{
		if (marks[ gr[v][i] ] == WHITE)
		{
			dfs(gr[v][i], foundBridge, v);
			tup[v] = min(tup[v], tup[ gr[v][i] ]);
			if (tup[v] == tin)
				foundBridge(v, i);
		}
		else if (gr[v][i] != p)
			tup[v] = min(tup[v], tup[ gr[v][i] ]);
	}
	marks[v] = BLACK;
}

int main()
{
	return 0;
}
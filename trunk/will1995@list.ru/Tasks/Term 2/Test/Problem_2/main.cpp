#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>

using namespace std;

class TGraph
{
public:
	TGraph(int size): size(size)
	{
		Vert.resize(size);
		
		Used.resize(size);
		Used.assign(size, 0);

		comp.resize(size);
		comp.assign(size, 0);
	}

	TGraph();

	bool DFS( int vertex, bool color );
	void Add ( int v, int u );

//private:
	vector < vector < int > > Vert; 
	vector < bool > Used;
	vector < bool > comp; 
	int size;
};

void TGraph::Add( int v, int u )
{
	Vert[v].push_back(u);
}

bool TGraph::DFS (int v, bool color)
{
	comp[v] = color;
	Used[v]= true;
	for (int i = 0; i < Vert[v].size(); i++)
	{
		if (!Used[ Vert[v][i] ])
		{
			return DFS( Vert[v][i], !color );
		}
		else
			if (!(comp[v] ^ comp[ Vert[v][i] ]))
				return false;
	}
	return true;
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n, m;
	cin >> n;

	TGraph Graph (n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			bool x;
			cin >> x;
			if (x)
				Graph.Add(i, j);
		}

	bool ok = true;
	for (int i = 0; i < n; i++)
		if (!Graph.Used[i])
			ok = ok && Graph.DFS ( i, true );

	if (ok)
		cout << "Yes.\n";
	else
		cout << "No.\n";

	fclose(stdin);
	fclose(stdout);

	return 0;
}
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

	void DFS( int vertex, bool ok );
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

void TGraph::DFS (int v, bool ok)
{
	Used[v]= true;
	for (int i = 0; i < Vert[v].size(); i++)
	{
		if (!Used[ Vert[v][i] ])
		{
			comp[ Vert[v][i]] = !comp[v];
			DFS( Vert[v][i], ok );
		}
		else
			if (!(comp[v] ^ comp[ Vert[v][i] ]))
			{
				cout << "NO\n";
				ok = false;
			}
	}
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n, m;
	cin >> n >> m;

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
			Graph.DFS ( i, ok );

	if (ok)
		cout << "YES\n";

	fclose(stdin);
	fclose(stdout);

	return 0;
}
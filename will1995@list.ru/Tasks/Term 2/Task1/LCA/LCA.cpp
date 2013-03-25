#include <iostream>
#include <stdio.h>
#include <vector>
#include <list>

using namespace std;

class Graph
{
public:
	Graph(int size): size(size)
	{
		Vert.resize(size);

		Anc.resize(size);
		Anc.assign(size, -1);
		
		Rank.resize(size);
		Rank.assign(size, 0);

		Dsu.resize(size);
		Dsu.assign(size, 0);

		Used.resize(size);
		Used.assign(size, 0);
	}

	Graph();

	void DFS(int vertex, vector < vector <int> > &quiery);
	void Union(int v, int u, int new_anc);
	int Get(int v);
	void Add (int v, int u);

//private:
	vector < vector <int> > Vert; 
	vector < int > Anc;
	vector < int > Rank;
	vector < int > Dsu;
	vector < bool > Used;
	int size;
};

int Graph::Get(int v)
{
	if ((Dsu[v] == v) || (Dsu[v] == -1))
		return v;
	return Dsu[v] = Get(Dsu[v]);
}

void Graph::Union(int v, int u, int new_anc)
{
	v = Get(v);
	u = Get(u);

	if (rand() & 1)
		swap(v, u);
	Dsu[v] = u;
	Anc[u] = new_anc;
}

void Graph::Add(int v, int u)
{
	Vert[v].push_back(u);
}

void Graph::DFS(int v, vector < vector <int> > &quiery)
{
	Dsu[v] = v;
	Anc[v] = v;
	Used[v] = true;
	for (int i = 0; i < Vert[v].size(); i++)
		if (!Used[Vert[v][i]])
		{
			DFS(Vert[v][i], quiery);
			Union(v, Vert[v][i], v);
		}

	for (int i = 0; i < quiery[v].size(); i++)
		if (Used[quiery[v][i]])
		{
			cout << v <<"'s and " << quiery[v][i] << "'s LCA is " << Anc[Dsu[Get(quiery[v][i])]] << endl;
			//Used[quiery[v][i]] = 1;
			//Used[v] = 1;
		}
}

int main()
{
	freopen ("input.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);

	int n, m, q;
	cin >> n >> m >> q;
	Graph gr(n);
	vector < vector <int> > quiery (n);

	for(int i = 0; i < m; i++)
	{
		int v, u;
		cin >> v >> u;
		gr.Add(v, u);
		gr.Add(u, v);
	}

	for (int i = 0; i < q; i++)
	{
		int v, u;
		cin >> v >> u;
		//quiery[v].push_back(u);
		quiery[u].push_back(v);
	}
	gr.DFS(0, quiery);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
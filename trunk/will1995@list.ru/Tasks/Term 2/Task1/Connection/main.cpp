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

		Rep.resize(size);
		Rep.assign(size, -1);

		Rank.resize(size);
		Rank.assign(size, 0);
	}

	Graph();

	void DFS(int vertex);
	void Union(int &v, int &u);
	int Get(int v);
	void Add (int v, int u);

//private:
	vector < list <int> > Vert; 
	vector < int > Rep;
	vector < int > Rank;
	int size;
};

int Graph::Get(int v)
{
	if ((Rep[v] == v) || (Rep[v] == -1))
		return v;
	return Rep[v] = Get(Rep[v]);
}

void Graph::Union(int &v, int &u)
{
	v = Get(v);
	u = Get(u);

	if (v != u)
	{
		if (Rank[v] < Rank[u])
			swap(v, u);
		Rep[u] = v;
		if (Rank[v] == Rank[u])
			Rank[v]++;
	}
}

void Graph::Add(int v, int u)
{
	Vert[v].push_back(u);
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n, m, k; // vertexes, edges, queries
	cin >> n >> m >> k;
	Graph gr(n);

	for (int i = 0; i < m; i++)
	{
		int v, u;
		cin >> v >> u;
		gr.Add(v, u);
		gr.Add(u, v);
		gr.Union(u, v);
	}

	for (int i = 0; i < k; i++)
	{
		int op, v, u;
		cin >> op >> v >> u;
		if (op == 0)
		{
			if (gr.Get(v) == gr.Get(u))
				cout << "They're connected";
			else
				cout << "They're not connected";
		}
		else
		{
			gr.Union(v, u);
		}
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}
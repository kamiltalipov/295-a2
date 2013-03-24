#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;

class DSU
{
public:
	DSU() {size = 0;}
	void resize(int size);
	void Unite(int x, int y);
	int GetRoot(int x);
private:
	int size;
	vector<int> pred;
	vector<int> rank;
};

class Graph
{
public:
	struct Edge
	{
		int from, to;
		Edge(int f, int t)
		{
			from = f;
			to = t;
		}
	};
	Graph(int vertices);
	void AddEdge(Edge &edge);
	bool SameComponent(int v, int u);
private:
	vector<vector<int>> AdjList;
	DSU Set;
	int vertices;
};

void DSU::resize(int size)
{
	assert(size >= this->size);
	pred.resize(size);
	for (int i = this->size; i < size; ++i)
		pred[i] = i;
	rank.resize(size, 0);
	this->size = size;
}

int DSU::GetRoot(int x)
{
	if (pred[x] == x)
		return x;
	else
		return pred[x] = GetRoot(pred[x]);
}

void DSU::Unite(int x, int y)
{
	if (GetRoot(x) != GetRoot(y))
	{
		if (rank[GetRoot(x)] > rank[GetRoot(y)])
		{
			pred[GetRoot(y)] = GetRoot(x);
		}
		else if (rank[GetRoot(x)] == rank[GetRoot(y)])
		{
			pred[GetRoot(y)] = GetRoot(x);
			rank[GetRoot(x)] += 1;
		}
		else
		{
			pred[GetRoot(x)] = GetRoot(y);
		}
	}
}

Graph::Graph(int vertices)
{
	this->vertices = vertices;
	AdjList.resize(vertices);
	Set.resize(vertices);
}

void Graph::AddEdge(Edge &edge)
{
	AdjList[edge.from].push_back(edge.to);
	AdjList[edge.to].push_back(edge.from);
	Set.Unite(edge.from, edge.to);
}

bool Graph::SameComponent(int v, int u)
{
	return Set.GetRoot(v) == Set.GetRoot(u);
}

int main()
{
	int n, m, a, b, t;
	cin >> n >> m;
	Graph g(n);
	for (int i = 0; i < m; i++)
	{
		cin >> t >> a >> b;
		if (t == 0)
			g.AddEdge(Graph::Edge(a, b));
		else
			cout << g.SameComponent(a, b) ? 1 : 0;
	}

	return 0;
}
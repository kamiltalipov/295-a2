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
	
private:
	friend class LCA;
	vector<vector<int>> AdjList;
	int vertices;
};

class LCA
{
public:
	LCA(Graph &graph, vector<vector<int>> &queries);
	void PrintAnswers();
private:
	enum colors {WHITE, GRAY, BLACK};
	void DFS(int vertex);
	Graph &graph;
	vector<vector<int>> &queries;
	vector<colors> color;
	vector<int> ancestor;
	vector<vector<int>> answers;
	DSU Set;
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
}

void Graph::AddEdge(Edge &edge)
{
	AdjList[edge.from].push_back(edge.to);
}

LCA::LCA(Graph &graph, vector<vector<int>> &queries):graph(graph), queries(queries)
{
	color.resize(graph.vertices, WHITE);
	ancestor.resize(graph.vertices);
	answers.resize(queries.size());
	for (int i = 0; i < answers.size(); ++i)
		answers[i].resize(queries[i].size(), -1);
	Set.resize(graph.vertices);
	DFS(0);
}

void LCA::PrintAnswers()
{
	for (int i = 0; i < queries.size(); ++i)
	{
		for (int j = 0; j < queries[i].size(); ++j)
		if (i <= queries[i][j])
		{
			cout << i << " " << queries[i][j] << " -> " << answers[i][j] << endl;
		}
	}
}

void LCA::DFS(int vertex)
{
	color[vertex] = GRAY;
	ancestor[vertex] = vertex;
	for (auto it = graph.AdjList[vertex].begin(); it != graph.AdjList[vertex].end(); ++it)
	{
		DFS(*it);
		Set.Unite(vertex, *it);
		ancestor[Set.GetRoot(*it)] = vertex;
	}
	color[vertex] = BLACK;
	for (auto it = queries[vertex].begin(); it != queries[vertex].end(); ++it)
	{
		if (color[*it] == BLACK)
		{
			answers[vertex][it - queries[vertex].begin()] = ancestor[Set.GetRoot(*it)];
		}
	}
}

int main()
{
	int n, m, a, b;
	vector<vector<int>> queries;
	cin >> n;
	Graph g(n);
	for (int i = 0; i < n - 1; ++i)
	{
		cin >> a >> b;
		g.AddEdge(Graph::Edge(a, b));
	}
	cin >> m;
	queries.resize(n);
	for (int i = 0; i < m; ++i)
	{
		cin >> a >> b;
		queries[a].push_back(b);
		queries[b].push_back(a);
	}
	LCA L(g, queries);
	L.PrintAnswers();
	return 0;
}
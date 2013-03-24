#include <iostream>
#include <vector>

using namespace std;

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
	friend class GraphAlgorithms;
	Graph(int vertices);
	void AddEdge(Edge &edge);
private:
	vector<vector<int>> AdjList;
	int vertices;
};

class GraphAlgorithms
{
public:
	GraphAlgorithms(Graph &graph);
	vector<int>& EulerianCycle();
private:
	Graph &graph;
	vector<int> Ecycle;
	void DFS(int vertex);
	vector<int> CurBegin;
};

Graph::Graph(int vertices)
{
	this->vertices = vertices;
	AdjList.resize(vertices);
}

void Graph::AddEdge(Edge &edge)
{
	AdjList[edge.from].push_back(edge.to);
}

GraphAlgorithms::GraphAlgorithms(Graph &graph):graph(graph)
{
}

void GraphAlgorithms::DFS(int vertex)
{
	for (auto it = graph.AdjList[vertex].begin() + CurBegin[vertex]; it != graph.AdjList[vertex].end(); ++it)
	{
		CurBegin[vertex] += 1;
		DFS(*it);
	}
	Ecycle.push_back(vertex);
}

vector<int>& GraphAlgorithms::EulerianCycle()
{
	vector<int> DegIn(graph.vertices);
	for (int i = 0; i < graph.vertices; ++i)
	{
		for (auto it = graph.AdjList[i].begin(); it != graph.AdjList[i].end(); ++it)
		{
			DegIn[*it] += 1;
		}
	}
	bool is_Ecycle = true;
	for (int i = 0; i < graph.vertices; ++i)
	{
		if (graph.AdjList[i].size() != DegIn[i])
		{
			is_Ecycle = false;
		}
	}
	if (is_Ecycle)
	{
		CurBegin.resize(graph.vertices);
		DFS(0);
	}
	return Ecycle;
}


int main()
{
	int n, m, a, b;
	cin >> n >> m;
	Graph g(n);
	for (int i = 0; i < m; i++)
	{
		cin >> a >> b;
		g.AddEdge(Graph::Edge(a, b));
	}

	GraphAlgorithms GA(g);
	vector<int>& v = GA.EulerianCycle();
	if (!v.empty())
	{
		for (auto it = v.begin(); it != v.end(); ++it)
		{
			cout << *it << " ";
		}
	}
	else
	{
		cout << "No Eulerian cycles" << endl;
	}
	return 0;
}
#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <assert.h>

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
	Graph(){vertices = 0;}
	Graph(int vertices);
	void resize(int vertices);
	void AddEdge(Edge &edge);
private:
	vector<vector<int>> AdjList;
	int vertices;
};

class GraphAlgorithms
{
public:
	GraphAlgorithms(Graph &graph);
	void Kosaraju();
	void Tarjan();
private:
	enum colors {WHITE, GRAY, BLACK};
	Graph &graph;
	vector<colors> color;
	vector<int> traversal;
	vector<vector<int>> Kosaraju_Comp;
	Graph Tgraph;
	void Kosaraju_Traversal(int vertex);
	void Kosaraju_StronglyConnectedComp(int vertex);
	void Tarjan_StronglyConnectedComp(int vertex);
	vector<vector<int>> Tarjan_Comp;
	int time;
	vector<int> time_in;
	vector<int> up;
	stack<int> Stack;
	vector<bool> onStack;
};

Graph::Graph(int vertices)
{
	this->vertices = vertices;
	AdjList.resize(vertices);
}

void Graph::resize(int vertices)
{
	assert(vertices >= this->vertices);
	this->vertices = vertices;
	AdjList.resize(vertices);
}

void Graph::AddEdge(Edge &edge)
{
	AdjList[edge.from].push_back(edge.to);
}

GraphAlgorithms::GraphAlgorithms(Graph &graph):graph(graph)
{
	color.resize(graph.vertices, WHITE);

	time_in.resize(graph.vertices);
	up.resize(graph.vertices);
	onStack.resize(graph.vertices);
	time = 0;
}

void GraphAlgorithms::Kosaraju()
{
	for (int i = 0; i < graph.vertices; ++i)
	{
		if (color[i] == WHITE)
		{
			Kosaraju_Traversal(i);
		}
	}

	Tgraph.resize(graph.vertices);
	for (int i = 0; i < graph.vertices; ++i)
	{
		for (auto it = graph.AdjList[i].begin(); it != graph.AdjList[i].end(); ++it)
		{
			Tgraph.AddEdge(Graph::Edge(*it, i));
		}
	}
	color.assign(graph.vertices, WHITE);
	for (auto it = traversal.rbegin(); it != traversal.rend(); ++it)
	{
		if (color[*it] == WHITE)
		{
			Kosaraju_Comp.resize(Kosaraju_Comp.size() + 1);
			Kosaraju_StronglyConnectedComp(*it);
		}
	}
}

void GraphAlgorithms::Kosaraju_Traversal(int vertex)
{
	color[vertex] = GRAY;
	for (auto it = graph.AdjList[vertex].begin(); it != graph.AdjList[vertex].end(); ++it)
	{
		if (color[*it] == WHITE)
		{
			Kosaraju_Traversal(*it);
		}
	}
	color[vertex] = BLACK;
	traversal.push_back(vertex);
}

void GraphAlgorithms::Kosaraju_StronglyConnectedComp(int vertex)
{
	color[vertex] = GRAY;
	Kosaraju_Comp[Kosaraju_Comp.size() - 1].push_back(vertex);
	for (auto it = Tgraph.AdjList[vertex].begin(); it != Tgraph.AdjList[vertex].end(); ++it)
	{
		if (color[*it] == WHITE)
		{
			Kosaraju_StronglyConnectedComp(*it);
		}
	}
	color[vertex] = BLACK;
}

void GraphAlgorithms::Tarjan()
{
	time = 0;
	color.assign(graph.vertices, WHITE);
	for (int i = 0; i < graph.vertices; ++i)
	{
		if (color[i] == WHITE)
		{
			Tarjan_StronglyConnectedComp(i);
		}
	}
}

void GraphAlgorithms::Tarjan_StronglyConnectedComp(int vertex)
{
	color[vertex] = GRAY;
	up[vertex] = time_in[vertex] = time;
	time += 1;
	Stack.push(vertex);
	onStack[vertex] = true;
	for (auto it = graph.AdjList[vertex].begin(); it != graph.AdjList[vertex].end(); ++it)
	{
		if (color[*it] == WHITE)
		{
			Tarjan_StronglyConnectedComp(*it);
			up[vertex] = min(up[vertex], up[*it]);
		}
		else if (onStack[*it])
		{
			up[vertex] = min(up[vertex], time_in[*it]);
		}
	}
	color[vertex] = BLACK;
	if (up[vertex] == time_in[vertex])
	{
		Tarjan_Comp.resize(Tarjan_Comp.size() + 1);
		while (Stack.top() != vertex)
		{
			Tarjan_Comp[Tarjan_Comp.size() - 1].push_back(Stack.top());
			onStack[Stack.top()] = false;
			Stack.pop();
		}
		Tarjan_Comp[Tarjan_Comp.size() - 1].push_back(Stack.top());
		onStack[Stack.top()] = false;
		Stack.pop();
	}

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
	GA.Tarjan();
	return 0;
}
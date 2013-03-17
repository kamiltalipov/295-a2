#include <iostream>
#include <vector>
#include <stack>
#include <set>

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
		bool operator==(Edge &other)
		{
			return (this->from == other.from && this->to == other.to) ||
				(this->from == other.to && this->to == other.from);
		}
		bool operator!=(Edge &other)
		{
			return !operator==(other);
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
	set<int>& ArtPoints();
	vector<Graph::Edge>& Bridge();
	vector<vector<Graph::Edge>>& VertexComponents();
	vector<vector<int>>& EdgeComponents();
private:
	enum colors {WHITE, GRAY, BLACK};
	vector<colors> color;
	vector<int> time_in;
	vector<int> up;
	Graph &graph;
	stack<int> Vertices;
	stack<Graph::Edge> Edges;
	set<int> ArticulationPoints;
	vector<Graph::Edge> Bridges;
	vector<vector<Graph::Edge>> VertexComponent;
	vector<vector<int>> EdgeComponent; 

	int time;
	bool done;
	void DFS(int vertex, int parent);
	void findAll();
};

Graph::Graph(int vertices)
{
	this->vertices = vertices;
	AdjList.resize(vertices);
}

void Graph::AddEdge(Edge &edge)
{
	AdjList[edge.from].push_back(edge.to);
	AdjList[edge.to].push_back(edge.from);
}

GraphAlgorithms::GraphAlgorithms(Graph &graph):graph(graph)
{
	color.resize(graph.vertices, WHITE);
	time_in.resize(graph.vertices);
	up.resize(graph.vertices);
	time = 0;
	done = false;
}

void GraphAlgorithms::DFS(int vertex, int parent)
{
	Vertices.push(vertex);
	time += 1;
	up[vertex] = time_in[vertex] = time;
	color[vertex] = GRAY;
	for (auto it = graph.AdjList[vertex].begin(); it != graph.AdjList[vertex].end(); ++it)
	{
		if (color[*it] == WHITE)
		{
			Edges.push(Graph::Edge(vertex, *it));
			DFS(*it, vertex);
			up[vertex] = min(up[vertex], up[*it]);
			if (up[*it] >= time_in[vertex] && parent != -1)
			{
				ArticulationPoints.insert(vertex);
				VertexComponent.resize(VertexComponent.size() + 1);
				while (Edges.top() != Graph::Edge(vertex, *it))
				{
					VertexComponent[VertexComponent.size() - 1].push_back(Edges.top());
					Edges.pop();
				}
				VertexComponent[VertexComponent.size() - 1].push_back(Edges.top());
				Edges.pop();
			}
			else if (parent == -1)
			{
				for (auto it1 = it + 1; it1 != graph.AdjList[vertex].end(); ++it1)
				{
					if (color[*it1] == WHITE)
					{
						ArticulationPoints.insert(vertex);
						VertexComponent.resize(VertexComponent.size() + 1);
						while (Edges.top() != Graph::Edge(vertex, *it))
						{
							VertexComponent[VertexComponent.size() - 1].push_back(Edges.top());
							Edges.pop();
						}
						VertexComponent[VertexComponent.size() - 1].push_back(Edges.top());
						Edges.pop();
						break;
					}
				}
			}
			if (up[*it] >= time_in[*it])
			{
				Bridges.push_back(Graph::Edge(vertex, *it));
				EdgeComponent.resize(EdgeComponent.size() + 1);
				while (Vertices.top() != *it)
				{
					EdgeComponent[EdgeComponent.size() - 1].push_back(Vertices.top());
					Vertices.pop();
				}
				EdgeComponent[EdgeComponent.size() - 1].push_back(Vertices.top());
				Vertices.pop();
			}
		}
		else if (color[*it] == GRAY && *it != parent)
		{
			up[vertex] = min(up[vertex], time_in[*it]);
			Edges.push(Graph::Edge(vertex, *it));
		}
	}
	color[vertex] = BLACK;
}


void GraphAlgorithms::findAll()
{
	for (int i = 0; i < graph.vertices; i++)
	{
		if (color[i] == WHITE)
		{
			DFS(0, -1);
			if (!Edges.empty())
			{
				VertexComponent.resize(VertexComponent.size() + 1);
				while (!Edges.empty())
				{
					VertexComponent[VertexComponent.size() - 1].push_back(Edges.top());
					Edges.pop();
				}
			}
			if (!Vertices.empty())
			{
				EdgeComponent.resize(EdgeComponent.size() + 1);
				while (!Vertices.empty())
				{
					EdgeComponent[EdgeComponent.size() - 1].push_back(Vertices.top());
					Vertices.pop();
				}
			}
		}
	}
}

set<int>& GraphAlgorithms::ArtPoints()
{
	if (!done)
	{
		findAll();
		done = true;
	}
	return ArticulationPoints;
}

vector<Graph::Edge>& GraphAlgorithms::Bridge()
{
	if (!done)
	{
		findAll();
		done = true;
	}
	return Bridges;
}

vector<vector<Graph::Edge>>& GraphAlgorithms::VertexComponents()
{
	if (!done)
	{
		findAll();
		done = true;
	}
	return VertexComponent;
}

vector<vector<int>>& GraphAlgorithms::EdgeComponents()
{
	if (!done)
	{
		findAll();
		done = true;
	}
	return EdgeComponent;
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
	set<int> st = GA.ArtPoints();
	return 0;
}
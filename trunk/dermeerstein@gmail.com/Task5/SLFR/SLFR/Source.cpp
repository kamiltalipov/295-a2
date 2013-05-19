#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

class DSU
{
public:
	DSU(int size);
	void Unite(int x, int y);
	int GetRoot(int x);
private:
	int size;
	vector<int> pred;
	vector<int> rank;
};

class WGraph
{
public:
	struct Edge
	{
		int from, to, weight;
		Edge(int f, int t, int w)
		{
			from = f;
			to = t;
			weight = w;
		}
	};
	WGraph(int vertices);
	void AddEdge(Edge edge);
	
private:
	friend class LCA;
	friend class SLRF;
	vector<vector<Edge>> AdjList;
	int vertices;
};

bool operator<(const WGraph::Edge e1, const WGraph::Edge e2)
{
	return (e1.weight < e2.weight);
}

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
		bool operator==(Edge e)
		{
			return (e.from == from) && (e.to == to);
		}
	};
	Graph(int vertices);
	void AddEdge(Edge edge);
	
private:
	friend class LCA;
	friend class SLRF;
	vector<vector<int>> AdjList;
	int vertices;
};

class LCA
{
public:
	LCA(Graph &graph, vector<vector<int>> &queries);
	int GetLCA(int v, int u);
	vector<vector<int>> answers;
private:
	enum colors {WHITE, GRAY, BLACK};
	void DFS(int vertex);
	Graph &graph;
	vector<vector<int>> &queries;
	vector<colors> color;
	vector<int> ancestor;
	DSU Set;
};

class SLRF
{
public:
	SLRF(WGraph &g);
private:
	static const int INF = 1e+9;
	void Dijkstra();
	WGraph &graph;
	vector<int> dist;
	vector<int> pred;
	Graph SPT;
};


DSU::DSU(int size)
{
	pred.resize(size);
	for (int i = 0; i < size; ++i)
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

WGraph::WGraph(int vertices)
{
	this->vertices = vertices;
	AdjList.resize(vertices);
}

void WGraph::AddEdge(Edge edge)
{
	AdjList[edge.from].push_back(edge);
}

Graph::Graph(int vertices)
{
	this->vertices = vertices;
	AdjList.resize(vertices);
}

void Graph::AddEdge(Edge edge)
{
	AdjList[edge.from].push_back(edge.to);
}


LCA::LCA(Graph &graph, vector<vector<int>> &queries):graph(graph), queries(queries), Set(graph.vertices)
{
	color.resize(graph.vertices, WHITE);
	ancestor.resize(graph.vertices);
	answers.resize(queries.size());
	for (int i = 0; i < answers.size(); ++i)
		answers[i].resize(queries[i].size(), -1);
	DFS(0);
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

int LCA::GetLCA(int v, int u)
{
	int i;
	for (i = 0; i < queries[v].size(); ++i)
	{
		if (queries[v][i] == u)
			break;
	}
	if (answers[v][i] != -1)
		return answers[v][i];
	else
	{
		for (i = 0; i < queries[u].size(); ++i)
		{
			if (queries[u][i] == v)
				break;
		}
		if (answers[u][i] != -1)
			return answers[u][i];
	}
}

SLRF::SLRF(WGraph &g):graph(g), SPT(graph.vertices)
{
	Dijkstra();
	for (int i = 0; i < graph.vertices; ++i)
	{
		if (pred[i] != -1)
		{
			SPT.AddEdge(Graph::Edge(pred[i], i));
		}
	}
	set<WGraph::Edge> NotTreeEdges;
	for (int i = 0; i < graph.vertices; ++i)
	{
		for (int j = 0; j < graph.AdjList[i].size(); ++j)
		{
			bool inTree = false;
			int v = i, u = graph.AdjList[i][j].to, w = graph.AdjList[i][j].weight;
			for (int k = 0; k < SPT.AdjList[v].size() && !inTree; ++k)
			{
				if (SPT.AdjList[v][k] == u)
					inTree = true;
			}
			for (int k = 0; k < SPT.AdjList[u].size() && !inTree; ++k)
			{
				if (SPT.AdjList[u][k] == v)
					inTree = true;
			}
			if (!inTree)
				NotTreeEdges.insert(WGraph::Edge(min(v, u), max(v, u), dist[v] + dist[u] + w));
		}
	}
	vector<vector<int>> queries(graph.vertices);
	for (auto it = NotTreeEdges.begin(); it != NotTreeEdges.end(); ++it)
	{
		queries[(*it).from].push_back((*it).to);
		queries[(*it).to].push_back((*it).from);
	}
	LCA L(SPT, queries);
	vector<vector<Graph::Edge>> EscapeEdge(SPT.vertices);
	for (int i = 0; i < SPT.vertices; ++i)
	{
		EscapeEdge[i].resize(SPT.AdjList[i].size(), Graph::Edge(-1, -1));
	}
	for (auto it = NotTreeEdges.begin(); it != NotTreeEdges.end(); ++it)
	{
		int v = (*it).from, u = (*it).to, w;
		w = L.GetLCA(v, u);
		int x = v;
		while (x != w)
		{
			int i;
			for (i = 0; i < SPT.AdjList[pred[x]].size(); ++i)
			{
				if (SPT.AdjList[pred[x]][i] == x && EscapeEdge[pred[x]][i] == Graph::Edge(-1, -1))
				{
					EscapeEdge[pred[x]][i] = Graph::Edge(v, u);
				}
			}
			x = pred[x];
		}
		x = u;
		while (x != w)
		{
			int i;
			for (i = 0; i < SPT.AdjList[pred[x]].size(); ++i)
			{
				if (SPT.AdjList[pred[x]][i] == x && EscapeEdge[pred[x]][i] == Graph::Edge(-1, -1))
				{
					EscapeEdge[pred[x]][i] = Graph::Edge(v, u);
				}
			}
			x = pred[x];
		}

	}
	for (int i = 0; i < SPT.vertices; ++i)
	{
		for (int j = 0; j < SPT.AdjList[i].size(); ++j)
		{
			cout << i << " " << SPT.AdjList[i][j] << " -> " << EscapeEdge[i][j].from << " " << EscapeEdge[i][j].to << endl;
		}
	}
	return;
}

void SLRF::Dijkstra()
{
	vector<bool> vis;
	dist.resize(graph.vertices, INF);
	pred.resize(graph.vertices, -1);
	vis.resize(graph.vertices, 0);
	dist[0] = 0;
	while (true)
	{
		int min_ind = -1;
		for (int i = 0; i < graph.vertices; ++i)
		{
			if ((min_ind == - 1 || dist[i] < dist[min_ind]) && !vis[i])
			{
				min_ind = i;
			}
		}
		if (min_ind == -1)
			break;
		for (int i = 0; i < graph.AdjList[min_ind].size(); ++i)
		{
			int v = graph.AdjList[min_ind][i].to;
			if (dist[min_ind] + graph.AdjList[min_ind][i].weight < dist[v] && !vis[v])
			{
				dist[v] = dist[min_ind] + graph.AdjList[min_ind][i].weight;
				pred[v] = min_ind;
			}
		}
		vis[min_ind] = 1;
	}
}

int main()
{
	int n, m, a, b, w;
	cin >> n >> m;
	WGraph g(n);
	for (int i = 0; i < m; ++i)
	{
		cin >> a >> b >> w;
		g.AddEdge(WGraph::Edge(a, b, w));
		g.AddEdge(WGraph::Edge(b, a, w));
	}
	SLRF S(g);
	return 0;
}
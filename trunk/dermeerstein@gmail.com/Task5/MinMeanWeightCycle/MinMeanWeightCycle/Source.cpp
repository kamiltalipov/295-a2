#include <iostream>
#include <vector>

using namespace std;

class Graph
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
	Graph(int vertices);
	void AddEdge(Edge edge);
	friend class Karp;
private:
	vector<vector<Edge>> AdjList;
	int vertices;
};

class Karp
{
public:
	Karp(Graph &g);
private:
	Graph &graph;
};

Graph::Graph(int vertices)
{
	this->vertices = vertices;
	AdjList.resize(vertices);
}

void Graph::AddEdge(Edge edge)
{
	AdjList[edge.to].push_back(edge);
}

Karp::Karp(Graph &g):graph(g)
{
	int INF = 1e+9;
	vector<vector<int>> dist(graph.vertices + 1), pred(graph.vertices + 1);
	for (int i = 0; i < graph.vertices + 1; ++i)
	{
		dist[i].resize(graph.vertices, INF);
		pred[i].resize(graph.vertices, -1);
	}
	dist[0][0] = 0;
	for (int k = 1; k <= graph.vertices; ++k)
	{
		for (int i = 0; i < graph.vertices; ++i)
		{
			for (int j = 0; j < graph.AdjList[i].size(); ++j)
			{
				if (dist[k - 1][graph.AdjList[i][j].from] + graph.AdjList[i][j].weight < dist[k][i])
				{
					dist[k][i] = dist[k - 1][graph.AdjList[i][j].from] + graph.AdjList[i][j].weight;
					pred[k][i] = graph.AdjList[i][j].from;
				}
			}
		}
	}
	double answer = INF;
	int ans_len, start_v;
	for (int i = 0; i < graph.vertices; ++i)
	{
		double cur_min = -INF;
		int len;
		for (int k = 0; k < graph.vertices; ++k)
		{
			if (dist[k][i] != INF)
			{
				if ((double)(dist[graph.vertices][i] - dist[k][i]) / (graph.vertices - k) > cur_min)
				{
					cur_min = (double)(dist[graph.vertices][i] - dist[k][i]) / (graph.vertices - k);
					len = graph.vertices - k;
				}
			}
		}
		if (cur_min < answer)
		{
			answer = cur_min;
			ans_len = len;
			start_v = i;
		}
	}
	if (answer != INF)
	{
		cout << answer << endl;
		vector<int> ans;
		int v = start_v;
		ans.push_back(v);
		for (int i = 0; i < ans_len; ++i)
		{
			v = pred[graph.vertices - i][v];
			ans.push_back(v);
		}
		for (auto it = ans.rbegin(); it != ans.rend(); ++it)
		{
			cout << *it << " ";
		}
	}
}

int main()
{
	freopen("input.txt", "r", stdin);
	int n, m, f, t, w;
	cin >> n >> m;
	Graph g(n + 1);
	for (int i = 0; i < m; ++i)
	{
		cin >> f >> t >> w; //from 1
		g.AddEdge(Graph::Edge(f, t, w));
	}
	for (int i = 1; i < n + 1; ++i)
	{
		g.AddEdge(Graph::Edge(0, i, 0));
	}
	Karp K(g);
	return 0;
}
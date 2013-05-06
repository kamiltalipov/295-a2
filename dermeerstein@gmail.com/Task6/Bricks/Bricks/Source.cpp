#include <iostream>
#include <string>
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
	Graph(int first_part, int second_part);
	void AddEdge(Edge edge);
	friend class Kuhn;
private:
	vector<vector<Edge>> AdjList;
	int first_part, second_part;
};

class Kuhn
{
public:
	Kuhn(Graph &g);
private:
	Graph &graph;
	vector <bool> vis;
	vector <int> to_second;
	vector <int> to_first;
	bool DFS(int vertex);
};

Graph::Graph(int first_part, int second_part)
{
	this->first_part = first_part;
	this->second_part = second_part;
	AdjList.resize(first_part);
}

void Graph::AddEdge(Edge edge) //&?
{
	AdjList[edge.from].push_back(edge);
}

Kuhn::Kuhn(Graph &g):graph(g), vis(graph.first_part), to_second(graph.first_part, -1), to_first(graph.second_part, -1)
{
	int ans = 0;
	for (int i = 0; i < graph.first_part; ++i)
	{
		vis.assign(vis.size(), 0);
		if (to_second[i] == -1 && DFS(i))
		{
			ans += 1;
		}
	}
	if (ans == graph.second_part)
	{
		for (int i = 0; i < graph.second_part; ++i)
		{
			 cout << to_first[i] << " ";
		}
	}
	else
		cout << "IMPOSSIBLE" << endl;
}

bool Kuhn::DFS(int vertex)
{
	vis[vertex] = true;
	for (auto it = graph.AdjList[vertex].begin(); it != graph.AdjList[vertex].end(); ++it)
	{
		if (to_first[(*it).to] == -1)
		{
			to_second[vertex] = (*it).to;
			to_first[(*it).to] = vertex;
			return true;
		}
		else
		{
			int u = to_first[(*it).to];
			if (!vis[u] && DFS(u))
			{
				to_second[vertex] = (*it).to;
				to_first[(*it).to] = vertex;
				return true;
			}
		}
	}
	return false;
}

int main()
{
	int n;
	string s, t;
	cin >> n;
	cin >> s;
	Graph g(n, s.size());
	for (int k = 0; k < n; ++k)
	{
		cin >> t;
		for (int i = 0; i < s.size(); ++i)
		{
			for (int j = 0; j < t.size(); ++j)
			{
				if (s[i] == t[j])
					g.AddEdge(Graph::Edge(k, i));
			}
		}
	}
	Kuhn K(g);
	return 0;
}
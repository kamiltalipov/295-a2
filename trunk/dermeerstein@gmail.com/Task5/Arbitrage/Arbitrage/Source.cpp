#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

class Graph
{
public:
	Graph(int vertices);
	friend class FordBellman;
	friend class Floyd;
private:
	vector<vector<double>> AdjMatrix;
	int vertices;
};

class FordBellman
{
public:
	FordBellman(Graph &g);
private:
	Graph &graph;
};

class Floyd
{
public:
	Floyd(Graph &g);
private:
	Graph &graph;
	vector<vector<int>> pred;
	vector<int> ans;
	void getPath(int v, int u);
};

Graph::Graph(int vertices)
{
	this->vertices = vertices;
	AdjMatrix.resize(vertices);
	for (int i = 0; i < vertices; ++i)
		AdjMatrix[i].resize(vertices);
	for (int i = 0; i < vertices; ++i)
	{
		for (int j = 0; j < vertices; ++j)
		{
			cin >> AdjMatrix[i][j];
		}
	}
}


FordBellman::FordBellman(Graph &g):graph(g)
{
	double EPS = 1e-2;
	vector<double> dist;
	vector<int> pred;
	dist.resize(graph.vertices, 0);
	pred.resize(graph.vertices, -1);
	dist[0] = 1;

	for (int k = 1; k < graph.vertices; ++k)
	{
		for (int i = 0; i < graph.vertices; ++i)
		{
			for (int j = 0; j < graph.vertices; ++j)
			{
				if (dist[j] + EPS < dist[i] * graph.AdjMatrix[i][j])
				{
					dist[j] = dist[i] * graph.AdjMatrix[i][j];
					pred[j] = i;
				}
			}
		}
	}

	int vertex = -1;
	for (int i = 0; i < graph.vertices; ++i)
	{
		for (int j = 0; j < graph.vertices; ++j)
		{
			if (dist[j] + EPS < dist[i] * graph.AdjMatrix[i][j])
			{
				vertex = j;
			}
		}
	}
	if (vertex != -1)
	{
		for (int i = 0; i < graph.vertices - 1; ++i)
			vertex = pred[vertex];
		vector<int> ans;
		ans.push_back(vertex);
		for (int v = pred[vertex]; v != vertex; v = pred[v])
		{
			ans.push_back(v);
		}
		ans.push_back(vertex);
		for (auto it = ans.rbegin(); it != ans.rend(); ++it)
			cout << *it << " ";
		cout << endl;
	}
	else
	{
		cout << "NO CYCLES" << endl;
	}
}

void Floyd::getPath(int v, int u)
{
	int k = pred[v][u];
	if (k == -1)
		return;
	getPath(v, k);
	ans.push_back(k);
	getPath(k, u);
}

Floyd::Floyd(Graph &g):graph(g)
{
	double EPS = 1e-2;
	vector<vector<double>> dist(graph.vertices);
	//vector<vector<int>> pred(graph.vertices);
	pred.resize(graph.vertices);
	for (int i = 0; i < graph.vertices; ++i)
	{
		dist[i].resize(graph.vertices);
		pred[i].resize(graph.vertices, -1);
	}
	
	for (int i = 0; i < graph.vertices; ++i)
	{
		for (int j = 0; j < graph.vertices; ++j)
		{
			dist[i][j] = graph.AdjMatrix[i][j];
		}
	}

	int vertex = -1;
	for (int k = 0; k < graph.vertices; ++k)
	{
		for (int i = 0; i < graph.vertices; ++i)
		{
			for (int j = 0; j < graph.vertices; ++j)
			{
				if (dist[i][j] + EPS < dist[i][k] * dist[k][j])
				{
					dist[i][j] = dist[i][k] * dist[k][j];
					pred[i][j] = k;
					if (i == j && dist[i][j] > 1 + EPS)
					{
						vertex = i;
						goto m;
					}
				}
			}
		}
	}
m:	if (vertex != -1)
	{
		ans.push_back(vertex);
		getPath(vertex, vertex);
		ans.push_back(vertex);

		for (auto it = ans.begin(); it != ans.end(); ++it)
			cout << *it << " ";
		cout << endl;
	}
	else
	{
		cout << "NO CYCLES" << endl;
	}
}

int main()
{
	freopen("input.txt", "r", stdin);
	int n;
	cin >> n;
	Graph g(n);
	FordBellman FB(g);
	Floyd F(g);
	return 0;
}
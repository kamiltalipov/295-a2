#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

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
	
	Graph(int vertices);
	void AddEdge(Edge &edge);
	bool DFS(int root);
	void TopSort();

private:
	enum colors {WHITE, GRAY, BLACK};
	vector<vector<int>> graph;
	vector<colors> color;
	vector<int> topSorted;
	int vertices;
};

Graph::Graph(int vertices)
{
	this->vertices = vertices;
	graph.resize(vertices);
	color.resize(vertices, WHITE);
}

void Graph::AddEdge(Edge &edge)
{
	graph[edge.from].push_back(edge.to);
}

bool Graph::DFS(int root)
{
	struct _st
	{
		int vertex, pointer;
		_st() {}
		_st(int v, int p = 0)
		{
			vertex = v;
			pointer = p;
		}
	} cur, next;
	stack<_st> st;
	int i;
	st.push(_st(root, 0));
	while (!st.empty())
	{
		cur = st.top();
		st.pop();
		color[cur.vertex] = GRAY;
		for (i = cur.pointer; i < graph[cur.vertex].size(); ++i)
		{
			next = _st(graph[cur.vertex][i]);
			if (color[next.vertex] == WHITE)
			{
				st.push(_st(cur.vertex, i));
				st.push(next);
				break; //!!!
			}
			else if (color[next.vertex] == GRAY)
			{
				//cycle
				return true;
			}
		}
		if (i == graph[cur.vertex].size())
		{
			color[cur.vertex] = BLACK;
			topSorted.push_back(cur.vertex);
		}
	}
	return false;
}

void Graph::TopSort()
{
	bool cycle;
	for (int i = 0; i < vertices; ++i)
	{
		if (color[i] == WHITE)
		{
			cycle = DFS(i);
			if (cycle)
			{
				cout << "Cycle";
				return;
			}
		}
	}
	reverse(topSorted.begin(), topSorted.end());
	for (auto it = topSorted.begin(); it != topSorted.end(); ++it)
		cout << *it << " ";
}

int main()
{
	int n, a, b;
	cin >> n;
	Graph graph(n);
	cin >> n;
	for (int i = 0; i < n; i++)
	{ 
		cin >> a >> b;
		graph.AddEdge(Graph::Edge(a, b));
	}
	graph.TopSort();
	return 0;
}
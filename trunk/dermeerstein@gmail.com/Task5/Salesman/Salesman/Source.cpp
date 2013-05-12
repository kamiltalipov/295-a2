#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>

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

class Point
{
public:
	Point(double x, double y) { this->x = x; this->y = y; }
	double Dist(const Point p) const 
	{ 
		Point p1 = *this; 
		Point p2 = p; 
		return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
	}
	friend ostream &operator <<(ostream &out, Point p)
	{
		out << p.x << " " << p.y;
		return out;
	}
private:
	double x, y;
};

class MinSpanTree
{
public:
	MinSpanTree(const vector<Point> &P);
	vector<vector<int>> Tree;
private:
	struct Edge
	{
		double dist;
		int v1, v2;
		Edge(int v1, int v2, double dist)
		{
			this->v1 = v1;
			this->v2 = v2;
			this->dist = dist;
		}
		bool operator<(const Edge &e)
		{
			double eps = 1e-7;
			return (this->dist + eps < e.dist);
		}
	};
	const vector<Point> &Points;
	DSU Set;

};


DSU::DSU(int size):pred(size), rank(size, 0)
{
	for (int i = 0; i < size; ++i)
		pred[i] = i;
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

MinSpanTree::MinSpanTree(const vector<Point> &P):Points(P), Set(P.size()), Tree(P.size())
{
	vector<Edge> Edges;
	for (int i = 0; i < Points.size(); ++i)
	{
		for (int j = i + 1; j < Points.size(); ++j)
		{
			Edges.push_back(Edge(i, j, Points[i].Dist(Points[j])));
		}
	}
	sort(Edges.begin(), Edges.end());
	for (int i = 0; i < Edges.size(); ++i)
	{
		if (Set.GetRoot(Edges[i].v1) != Set.GetRoot(Edges[i].v2))
		{
			Set.Unite(Edges[i].v1, Edges[i].v2);
			Tree[Edges[i].v1].push_back(Edges[i].v2);
			Tree[Edges[i].v2].push_back(Edges[i].v1);
		}
	}
}

void dfs(int vertex, vector<vector<int>> &graph, vector<Point> &Points, vector<bool> &vis)
{
	vis[vertex] = 1;
	cout << Points[vertex] << endl;
	for (auto it = graph[vertex].begin(); it != graph[vertex].end(); ++it)
	{
		if (!vis[*it])
			dfs(*it, graph, Points, vis);
	}
}

int main()
{
	vector<Point> Points;
	int n, m;
	double sigma1, sigma2;
	double x, y, s, t, z0, z1, y0, y1;
	cin >> n >> m >> sigma1 >> sigma2;
	srand(time(NULL));
	for (int i = 0; i < n; ++i)
	{
		do
		{
			x = 2 * (double) rand() / RAND_MAX - 1;
			y = 2 * (double) rand() / RAND_MAX - 1;
			s = x * x + y * y;
		} while (s == 0 || s > 1);
		t = sqrt(-2 * log(s) / s);
		z0 = x * t * sigma1;
		z1 = y * t * sigma1;
		for (int j = 0; j < m; ++j)
		{
			do
			{
				x = 2 * (double) rand() / RAND_MAX - 1;
				y = 2 * (double) rand() / RAND_MAX - 1;
				s = x * x + y * y;
			} while (s == 0 || s > 1);
			t = sqrt(-2 * log(s) / s);
			y0 = x * t * sigma2 + z0;
			y1 = y * t * sigma2 + z1;
			Points.push_back(Point(y0, y1));
		}
	}
	MinSpanTree MST(Points);
	vector<bool> vis(Points.size(), 0);
	dfs(0, MST.Tree, Points, vis);
	return 0;
}
#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <algorithm>
#include <ctime>

using namespace std;

const double eps = 1E-6;

class TDSU
{
public:
	void Unite ( int v, int u );
	int Get ( int v );
	TDSU( int n, int m ) 
	{
		for (int i = 0; i < n * m; i++)
		{
			Anc.push_back(i);
		}

		Rank.resize(n * m);
		Rank.assign(n * m, 0);
	}

	TDSU();
	
	vector < int > Rank;
	vector < int > Anc;

//private:
};

class TGraph
{
public:
	TGraph(int n, int m): size(n * m * 2) 
	{
		Tree.resize(n * m);
		Tree.assign(n * m, 0);
		Tree_Weight = 0;
	};
	TGraph();

	void Make_Tree ( TDSU &DSU );
	void Add (int v, int u, double weight);

//private:
	vector < pair < double, pair < int, int > > > Vert; 
	vector < vector < pair < int, double > > > Tree;
	int size;
	double Tree_Weight;
};

int TDSU::Get(int v)
{
	if ((Anc[v] == v) || (Anc[v] == -1))
		return v;
	return Anc[v] = Get(Anc[v]);
}

void TDSU::Unite(int v, int u)
{
	v = Get(v);
	u = Get(u);

	if (v != u)
	{
		if (Rank[v] < Rank[u])
			swap(v, u);
		Anc[u] = v;
		if (Rank[v] == Rank[u])
			Rank[v]++;
	}
}

void TGraph::Add(int v, int u, double w)
{
	Vert.push_back(make_pair( w, make_pair (v, u) ) );
}

void TGraph::Make_Tree( TDSU &DSU )
{
	for (int i = 0; i < size; i++)
	{
		int v = Vert[i].second.first;
		int u = Vert[i].second.second;
		double w = Vert[i].first;
		if (DSU.Get(v) != DSU.Get(u))
		{
			Tree_Weight = Tree_Weight + w;
			Tree[v].push_back( make_pair(u, w) );
			Tree[u].push_back( make_pair(v, w) );
			DSU.Unite(v, u);
		}
	}
}

pair <double, double> Box_Muller (double x0, double y0, double sigma)
{
	double x, y, s = 0;

	do
	{
		x = 2 * (double)rand()/(double)RAND_MAX - 1;
		y = 2 * (double)rand()/(double)RAND_MAX - 1;
		s = x * x + y * y;
	}
	while ((s >= 1) || (s <= eps));

	double lns = log(s);
	double z0 = x * sqrt(-2 * lns / s);
	double z1 = y * sqrt(-2 * lns / s);

	x = x0 + sigma * z0;
	y = y0 + sigma * z1;
	return(make_pair(x, y));
}

double dist( pair < double, double > x, pair < double, double > y)
{
	double result = sqrt((x.first - y.first) * (x.first - y.first) + (x.second - y.second) * (x.second - y.second));
	return result;
}

int main()
{
	freopen ("input.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);

	srand((unsigned)time(0));
	double n, m;
	double s1, s2;
	vector < pair < double, double > > points;
	vector < pair < double, double > > center;
	cin >> n >> m;
	cin >> s1 >> s2;

	for (int i = 0; i < n; i++)
		center.push_back(Box_Muller(0, 0, s1));

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			points.push_back(Box_Muller(center[i].first, center[i].second, s2));

	TGraph Graph (n, m);
	TDSU DSU(n, m);

	for (int i = 0; i < n * m; i++)
		for (int j = 0; j < n * m; j++)
			if (i != j)
				Graph.Add(i, j, dist(points[i], points[j]));

	sort(Graph.Vert.begin(), Graph.Vert.end());
	Graph.Make_Tree( DSU );

	fclose(stdin);
	fclose(stdout);
	return 0;
}
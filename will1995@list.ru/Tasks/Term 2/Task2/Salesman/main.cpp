#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

class TDSU
{
public:
	void Unite ( int v, int u );
	int Get ( int v );
	TDSU( int size ) 
	{
		for (int i = 0; i < size; i++)
		{
			Anc.push_back(i);
		}

		Rank.resize(size);
		Rank.assign(size, 0);
	}

	TDSU();
	
	vector < int > Rank;
	vector < int > Anc;

//private:
};

class TGraph
{
public:
	TGraph(int size): size(size) {};
	TGraph();

	int Make_Tree ( TDSU &DSU );
	void Add (int v, int u, int weight);

//private:
	vector < pair < int, pair < int, int > > > Vert; 
	int size;
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

void TGraph::Add(int v, int u, int w)
{
	Vert.push_back(make_pair( w, make_pair (v, u) ) );
}

int TGraph::Make_Tree( TDSU &DSU )
{
	int ans = 0;
	for (int i = 0; i < size; i++)
	{
		int v = Vert[i].second.first;
		int u = Vert[i].second.second;
		int w = Vert[i].first;
		if (DSU.Get(v) != DSU.Get(u))
		{
			ans += w;
			DSU.Unite(v, u);
		}
	}
	return ans;
}

int main()
{
	freopen ("input.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);

	int n, m;
	cin >> n >> m;
	TGraph Graph(m * 2);
	TDSU DSU(n);

	for (int i = 0; i < m; i++)
	{
		int v, u, w;
		cin >> v >> u >> w;
		//v--;
		//u--;
		Graph.Add(v, u, w);
		Graph.Add(u, v, w);
	}

	sort(Graph.Vert.begin(), Graph.Vert.end());

	cout << Graph.Make_Tree(DSU) << endl;
	fclose(stdin);
	fclose(stdout);
	return 0;
}
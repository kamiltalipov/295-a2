#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

class TGraph
{
public:
	TGraph();

	TGraph ( int n ): size( n )
	{
		Tree.resize( size );

		Recovery.resize ( size, vector < pair < int, int > > ( size, make_pair ( 0,  100000 ) ) );

		LCA.resize( size, vector < int > ( size, -1 ) );
		
		Used.resize( n, 0 );
		
		Anc.resize( size, -1 );

		prev.resize( size, -1 );

		dist.resize( size, 0 );

		Dsu.resize( size );
		for ( int i = 0; i < n; i++ )
			Dsu[i] = i;
	}

	void Add( int v, int u, int weight );	
	void Union( int v, int u, int new_anc );
	void Make_Tree();
	void DFS( int v, int w );
	void Solve( int start );
	void Subsolve( int v, int u, int w );

	int Get( int v );

//private:
	vector < pair < int, pair < int, int > > > Vert; 
	vector < vector < pair < int, int > > > Recovery;
	vector < vector < int > > LCA;
	vector < int > Anc;
	vector < int > prev;
	vector < int > Dsu;
	vector < vector < pair < int, int > > > Tree;
	priority_queue < pair < int, pair < int, int > > > q;
	vector < bool > intree;
	vector < int > dist;
	vector < bool > Used;
	int size;
};

void TGraph::DFS( int v, int w )
{
	Dsu[v] = v;
	Anc[v] = v;
	Used[v] = true;
	for ( int i = 0; i < Tree[v].size(); i++ )
		if ( !Used[Tree[v][i].first] )
		{
			dist[Tree[v][i].first] = max ( dist[Tree[v][i].first], Tree[v][i].second + w);
			DFS( Tree[v][i].first, Tree[v][i].second );
			Union( v, Tree[v][i].first, v );
			prev[Tree[v][i].first] = v;
		}

	for ( int i = 0; i < size; i++ )
		if ( Used[i] )
		{
			LCA[v][i] = Anc[Dsu[Get( i )]];
			LCA[i][v] = LCA[v][i];
		}
}

void TGraph::Subsolve( int v, int u, int w )
{
	if ( Used[v] )
			v = Get( v );

		while ( Get( v ) != Get( w ) )
		{
			Recovery[v][prev[v]] = make_pair ( v, u );
			Recovery[prev[v]][v] = make_pair ( v, u );
			Union( Get( prev[v] ), Get( v ),  prev[v] );
			Used[v] = true;
			v = prev[v];
		}
}

void TGraph::Solve( int start )
{	
	int i = Vert.size() - 1;
	while ( !intree[i] )
	{
		int v = Vert[i].second.first;
		int u = Vert[i].second.second;
		int w = Vert[i].first + dist[u] + dist[v];

		q.push ( make_pair ( -w, make_pair ( v, u ) ) );
		i--;
	}

	Used.assign( size, 0 );
	Used[start] = true;
	
	for ( int i = 0; i < size; i++ )
		Dsu[i] = i;

	while ( !q.empty() )
	{
		pair < int, pair < int, int > > tmp;
		tmp = q.top();
		q.pop();
		q.pop();

		int v = tmp.second.first;
		int u = tmp.second.second;
		int w = -tmp.first;
		int x = LCA[v][u];

		Subsolve( v, u, x );
		Subsolve( u, v, x );
	}
}

void TGraph::Add( int v, int u, int w )
{
	Vert.push_back( make_pair ( w, make_pair ( v, u ) ) );
	intree.push_back( false );
}

int TGraph::Get( int v )
{
	if ( ( Dsu[v] == v ) || ( Dsu[v] == -1 ) )
		return v;
	return Dsu[v] = Get( Dsu[v] );
}

void TGraph::Union( int v, int u, int new_anc )
{
	v = Get(v);
	u = Get(u);

	if (rand() & 1)
		swap(v, u);
	Dsu[v] = u;
	Anc[u] = new_anc;
}

void TGraph::Make_Tree()
{
	for ( int i = 0; i < Vert.size(); i++ )
	{
		int v = Vert[i].second.first;
		int u = Vert[i].second.second;
		int w = Vert[i].first;
		if ( Get( v ) != Get( u ) )
		{
			Tree[v].push_back( make_pair ( u, w ) );
			Tree[u].push_back( make_pair ( v, w ) );
			Union( v, u, -1 );
			intree[i] = true;
			intree[i + 1] = true;
		}
	}
}

int main()
{
	freopen( "input.txt", "r", stdin );
	freopen( "output.txt", "w", stdout );

	int n, m;
	cin >> n >> m;
	
	TGraph Graph(n);

	for ( int i = 0; i < m; i++ )
	{
		int u, v, w;
		cin >> v >> u >> w;
		Graph.Add( v, u, w );
		Graph.Add( u, v, w );
	}

	int start;
	cin >> start;

	sort ( Graph.Vert.begin(), Graph.Vert.end() );
	Graph.Make_Tree();

	Graph.Used.assign( n, 0 );
	Graph.Dsu.assign( n, 0 );
	Graph.DFS( start, 0 );


	Graph.Solve( start );

	cout << "Escape edges:\n";
	for ( int i = 0; i < n; i++ )
		for ( int j = i; j < n; j++ )
			if ( Graph.Recovery[i][j].second != 100000 )
				cout << "For " << i << " and " << j << " is " << Graph.Recovery[i][j].first << " - " << Graph.Recovery[i][j].second << endl;
	fclose( stdin );
	fclose( stdout );
	return 0;
}
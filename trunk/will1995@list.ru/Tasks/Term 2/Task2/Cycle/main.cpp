#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <algorithm>
#include <list>

using namespace std;

class TGraph
{
public:
	TGraph( int n ): size( n )
	{
		Vert.resize( size );
		
		Used.resize( n );
		Used.assign( n, 0 );
		
		prev.resize( n );
		next.resize( n );
		
		dist.resize( n, vector < float > ( n, 100000000 ) );
		weight.resize( n, vector < float > ( n, 0 ) );
		for ( int i = 0; i < n; i++ )
			dist[0][i] = 0;

		pi.resize( n, vector < int > ( n ) );
		m.resize( n, 100000000 );
		k_.resize( n, 0 );
		path.resize( n );
	};

	TGraph();

	void Add ( int v, int u, float weight );
	int Solve();
	bool DFS( int vertex, int count );

//private:
	vector < vector < int > > Vert; 
	vector < vector < int > > prev;
	vector < vector < int > > pi;
	vector < vector < int > > next;
	vector < vector < float > > weight;
	vector < vector < float > > dist;
	vector < float > m;
	vector < int > k_;
	vector < int > path;
	vector < char > Used;
	int size;
};

void TGraph::Add(int v, int u, float w)
{
	Vert[v].push_back( u );
	weight[v][u] = w;
	prev[u].push_back( v );
	next[v].push_back( u );
}

int TGraph::Solve() 
{
	for ( int k = 1; k < size; k++ )
	{
		for ( int v = 0; v < size; v++ )
		{
			for ( int i = 0; i < prev[v].size(); i++ )
			{
				int u = prev[v][i];
				if ( dist[k][v] > ( dist[k - 1][u] + weight[u][v] ) )
				{
					dist[k][v] = dist[k - 1][u] + weight[u][v];
					pi[k][v] = u;
				}
			}
		}
	}

	float l = 10000000;
	int v_;
	int length = 0;
	int anslen = 0;
	for ( int v = 0; v < size; v++ )
	{
		for ( int k = 0; k < size - 1; k++ )
			if ( m[v] > ( dist[size - 1][v] - dist[k][v] ) / ( size - 1 - k ) )
			{
				m[v] = ( dist[size - 1][v] - dist[k][v] ) / ( size - 1 - k ) ;
				length = size - 1 - k;
			}

		if ( l > m[v] )
		{
			l = m[v];
			v_ = v;
			anslen = length;
		}
	}

	if ( l != 10000000 )
	{
		cout << l << endl;
		vector < int > ans;
		int v = v_;
		ans.push_back(v);
		for ( int i = 0; i < anslen; i++ )
		{
			v = pi[size - 1 - i][v];
			ans.push_back( v );
		}

		for ( int i = 0; i < ans.size(); i++ )
			cout << ans[i] << ' ';
		cout << endl;
		return 0;
	}
}

bool TGraph::DFS( int v, int c )
{
	Used[v] = 1;
	for ( int i = 0; i < Vert[v].size(); i++ )
		if ( Used[ Vert[v][i] ] == 0 )
			DFS( Vert[v][i], c + 1 );
		else
			if ( Used[ Vert[v][i] ] == 1)
				return true;
			else
				continue;

	Used[v] = 2;
	if ( c == size )
		return false;
}

int main()
{
	freopen ( "input.txt", "r", stdin );
	freopen ( "output.txt", "w", stdout );

	int n, m;
	cin >> n >> m;
	TGraph Graph( n );
	for ( int i = 0; i < m; i++ )
	{
		int v, u;
		float w;
		cin >> v >> u >> w;
		Graph.Add( v, u, w );
	}

	if ( !Graph.DFS( 0, 0 ) ) 
		cout << "No cycles, sorry.\n";
	else
		Graph.Solve();

	fclose( stdin );
	fclose( stdout );
	return 0;
}
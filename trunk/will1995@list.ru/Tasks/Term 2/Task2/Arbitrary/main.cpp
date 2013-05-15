#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

class TGraph
{
public:
	TGraph();

	TGraph ( int n ): size( n )
	{
		Vert.resize( size );
		for ( int i = 0; i < size; i++ )
		{
			Vert[i].resize( size );
			Vert[i].assign( size, 0 );
		}		
		
		Prev.resize( size );
		for ( int i = 0; i < size; i++ )
		{
			Prev[i].resize( size );
			Prev[i].assign( size, 0 );
		}

		Used.resize( n );
		Used.assign( n, 0 );
	}

	void Add( int v, int u, double weight );
	void Floyd();
	void FB();

//private:
	vector < vector < double > > Vert; 
	vector < vector < int > > Prev; 
	vector < int > ans;
	vector < bool > Used;
	int size;
};

void TGraph::Add( int v, int u, double w )
{
	Vert[v][u] = w;
}

void TGraph::FB()
{
	vector < pair < double, pair < int, int > > > Edges;
	for ( int i = 0; i < size; i++ )
		for ( int j = 0; j < Vert[i].size(); j++ )
			Edges.push_back( make_pair ( Vert[i][j], make_pair( i, j ) ) );

	vector < vector < double > > dist( size, vector < double > ( size, 1.0 ) );
	vector < int > prev( size, -1 );

	int start = -1;
	for ( int i = 0; i < size - 1; i++ )
		for ( int v = 0; v < size; v++ )
			for ( int u = 0; u < Edges.size(); u++ )
			{
				int v0 = Edges[u].second.first;
				int u0 = Edges[u].second.second;
				double w0 = Edges[u].first;

				if ( ( dist[v][v0] * w0 ) > dist[v][u0] )
				{
					dist[v][u0] = max( dist[v][u0], dist[v][v0] * w0 );
					prev[u0] = v0;
					start = u0;
				}
			}

	if ( start != -1 )
	{
		int tmp = prev[start];
		Used.assign(size, 0);
		Used[start] = true;
		ans.push_back(start);
		while ( ( tmp != start ) && ( !Used[tmp] ) )
				{
					ans.push_back( tmp );
					Used[tmp] = true;
					tmp = prev[tmp];
				}
	}
}

void TGraph::Floyd()
{
	for ( int k = 0; k < size; k++ )
		for ( int i = 0; i < size; i++ )
			for ( int j = 0; j < size; j++ )
				if ( ( Vert[i][k] * Vert[k][j] ) > Vert[i][j] )
				{
					Vert[i][j] = Vert[i][k] * Vert[k][j];
					Prev[i][j] = k;
					if ( Vert[i][i] > 1 )
					{
						ans.push_back( i );
						Used[i] = true;
						int tmp = Prev[i][i];
						while ( ( tmp != i ) && ( !Used[tmp] ) )
						{
							ans.push_back( tmp );
							Used[tmp] = true;
							tmp = Prev[tmp][i];
						}
	
						reverse( ans.begin(), ans.end() );
						return;
					}
				}
				//почему надо проверять условие как только мы на него наткнулись?
}

int main()
{
	freopen( "input.txt", "r", stdin );
	freopen( "output.txt", "w", stdout );

	int n;
	cin >> n;
	
	TGraph Graph(n);

	for ( int i = 0; i < n; i++ )
		for ( int j = 0; j < n; j++ )
		{
			double w;
			cin >> w;
			Graph.Add( i, j, w );
		}

	Graph.Floyd();

	if ( Graph.ans.size() == 0 )
		cout << "No infinite money for you.\n";
	else
	{
		cout << "Infinite money: ";
		for ( int i = 0; i < Graph.ans.size(); i++ )
			cout << Graph.ans[i] << ' ';
		cout << endl;
	}
		
	fclose( stdin );
	fclose( stdout );
	return 0;
}
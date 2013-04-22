#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <algorithm>

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
		prev.assign( n, -1 );

		dist.resize( n );
		dist.assign( n, 0 );
	};
	TGraph();

	void Add ( int v, int u, int weight );
	int Find_Cycle( int weight );
	bool Any_Cycle( int vertex );

//private:
	vector < vector < pair < int, int > > > Vert; 
	vector < int > cycle;
	vector < int > prev;
	vector < int > dist;
	vector < char > Used;
	int size;
};

void TGraph::Add(int v, int u, int w)
{
	Vert[v].push_back( make_pair ( u, w ) );
}

bool TGraph::Any_Cycle( int v )
{
	Used[v] = 1;
	for ( int i = 0; i < Vert[v].size(); i++ ) 
	{
		int tmp = Vert[v][i].first;
		if ( Used[tmp] == 0 ) 
		{
			if ( Any_Cycle ( tmp ) )  
				return true;
		}
		else 
			if ( Used[tmp] == 1 ) 
				return true;
	}
	Used[v] = 2;
	return false;
}

int TGraph::Find_Cycle( int m )
{
	dist.assign( size, 0 );
	prev.assign( size, -1 );
	for ( int i = 0; i < size - 1; i++ )
		for ( int v = 0; v < size - 1; v++ )
			for ( int u = 0; u < Vert[v].size(); u++ )
			{
				int tmp = Vert[v][u].first;
				int w = Vert[v][u].second;
				if ( dist[tmp] > ( dist[v] + w - m ) )
				{
					dist[tmp] = dist[v] + w - m;
					prev[tmp] = v;
				}
			}

	int len = 0;
	for ( int i = 0; i < size; i++ )
		if ( dist [i] < 0 )
		{
			len = 0;
			Used.assign( size, 0 );
			cycle.clear();
	
			cycle.push_back( i );
			Used[i] = 1;
			int tmp = prev[i];
			while ( ( tmp != -1 ) && ( !Used[tmp] ) && ( tmp != i ) )
			{
				len += dist[tmp];
				cycle.push_back( tmp );
				Used[tmp] = true;
				tmp = prev[tmp];
			}
			if ( tmp = -1 )
				continue;

			break;
		}
		return len;
}

int main()
{
	freopen ( "input.txt", "r", stdin );
	freopen ( "output.txt", "w", stdout );

	int n, m, max_e = -100000000, min_e = 10000000;
	cin >> n >> m;
	TGraph Graph( n );
	for ( int i = 0; i < m; i++ )
	{
		int v, u, w;
		cin >> v >> u >> w;
		Graph.Add( v, u, w );
		max_e = max( w, max_e );
		min_e = min( w, min_e );
	}

	if ( Graph.Any_Cycle( 0 ) )
	{
		int l = min_e;
		int r = max_e;
		int len = 0;

		while ( r > l )
		{
			int m = ( r + l ) / 2;
			int tmp = Graph.Find_Cycle( m );
			if ( tmp >= len )
				l = m + 1;
			else
				r = m;
		}

		Graph.Find_Cycle( l );
		reverse( Graph.cycle.begin(), Graph.cycle.end() );
		for ( int i = 0; i < Graph.cycle.size(); i++ )
			cout << Graph.cycle[i] << ' ';
		cout << endl;
	}
	else 
		cout << "No cycles, sorry.\n";

	fclose( stdin );
	fclose( stdout );
	return 0;
}
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

void TGraph::Floyd()
{
	for ( int k = 0; k < size; k++ )
		for ( int i = 0; i < size; i++ )
			for ( int j = 0; j < size; j++ )
				if ( ( Vert[i][k] * Vert[k][j] ) > Vert[i][j] )
				{
					Vert[i][j] = Vert[i][k] * Vert[k][j];
					Prev[i][j] = k;
				}

	for ( int i = 0; i < size; i++ )
		if (Vert[i][i] > 1)
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
			break;
		}
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
		cout << "No infinite monay for you.\n";
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
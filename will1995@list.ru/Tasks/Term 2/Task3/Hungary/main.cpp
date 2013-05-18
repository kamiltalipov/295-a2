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
		Vert.resize( size + 1, vector < int > ( size + 1 ) );

		Used.resize( n + 1 );
		Used.assign( n + 1, 0 );

		pot2.resize ( n + 1, 0 );
	}

	void Add( int v, int u, int w );
	void Hungarian();

//private:
	vector < vector < int > > Vert; 
	vector < int > pot2;
	vector < bool > Used;
	int size;
};

void TGraph::Add( int v, int u, int w )
{
	Vert[v][u] = w;
	//if ( w == 0 )
		//Vert[v][ Vert[v].size() ].second = 10000000000;
}

void TGraph::Hungarian()
{
	vector < int > pot1, pair, path;
	pot1.resize( size + 1, 0 );
	pair.resize( size + 1, 0 );
	path.resize( size + 1, 0 );

	for ( int i = 1; i <= size; ++i )
	{
		pair[0] = i;
		int left0 = 0;
		vector < int > minv ( size + 1, 1000000000 );
		Used.assign( size + 1, 0 );
		do
		{
			Used[left0] = true;
			int right0 = pair[left0];
			int delta = 1000000000;
			
			int left1;
			for ( int j = 1; j <= size; ++j )

				if ( !Used[j] )
				{
					int cur = Vert[right0][j] - pot1[right0] - pot2[j];
					if ( cur < minv[j] )
					{
						minv[j] = cur;
						path[j] = left0;
					}

					if ( minv[j] < delta )
					{
						delta = minv[j];
						left1 = j;
					}
				}

			for ( int j = 0; j <= size; j++ )
				if ( Used[j] )
				{
					pot1[ pair[j] ] += delta;
					pot2[j] -= delta;
				}
				else
					minv[j] -= delta;
			left0 = left1;
		} while ( pair[left0] != 0 );

		do
		{
			int left1 = path[left0];
			pair[left0] = pair[left1];
			left0 = left1;
		} while ( left0 );
	}
}

int main()
{
	freopen( "input.txt", "r", stdin );
	freopen( "output.txt", "w", stdout );

	int n;
	cin >> n;

	TGraph Graph( n );
	for ( int i = 1; i <= n; i++ )
		for ( int j = 1; j <= n; j++ )
		{
			int w;
			cin >> w;
			Graph.Add( i, j, w ); 
		}

	Graph.Hungarian();
	cout << -Graph.pot2[0];

	fclose( stdin );
	fclose( stdout );
	return 0;
}
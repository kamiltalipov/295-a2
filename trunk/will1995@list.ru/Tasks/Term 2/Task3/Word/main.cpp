#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>

using namespace std;

class TGraph
{
public:
	TGraph();

	TGraph ( int n ): size( n )
	{
		Vert.resize( size );

		Used.resize( n );
		Used.assign( n, 0 );

		mx.resize( n, -1 );

		ans_size = 0;
	}

	void Add( int v, int u );
	bool Try( int vertex );

//private:
	vector < vector < int > > Vert; 
	vector < bool > Used;
	vector < int > mx;
	int size;
	int ans_size;
};

void TGraph::Add( int v, int u )
{
	Vert[v].push_back( u );
}

bool TGraph::Try( int v )
{
	if ( Used[v] )
		return false;

	Used[v] = true;
	for ( int i = 0; i < Vert[v].size(); i++ )
	{
		int u = Vert[v][i];
		if ( ( mx[u] == -1 ) || ( Try( mx[u] ) ) )
		{
			mx[u] = v;
			ans_size++;
			return true;
		}
	}
	return false;
}

int main()
{
	freopen( "input.txt", "r", stdin );
	freopen( "output.txt", "w", stdout );

	int n;
	cin >> n;

	string s1, s2;
	cin >> s1;

	TGraph Graph( s1.size() );

	for ( int i = 0; i < n; i++ )
	{
		cin >> s2;

		for ( int j = 0; j < s1.size(); j++ )
			for ( int k = 0; k < s2.size(); k++ )
				if ( s1[j] == s2[k] )
					Graph.Add( j, i );
	}

	for ( int i = 0; i < s1.size(); i++ )
	{
		Graph.Used.assign( s1.size(), 0 );
		Graph.Try( i );
	}

	if ( Graph.ans_size == s1.size() )
	{
		for ( int i = 0; i < Graph.mx.size(); i++ )
			if ( Graph.mx[i] != -1 )
				cout << Graph.mx[i] << ' ';
		cout << endl;
	}
	else
		cout << "No way.\n";

	fclose( stdin );
	fclose( stdout );
	return 0;
}
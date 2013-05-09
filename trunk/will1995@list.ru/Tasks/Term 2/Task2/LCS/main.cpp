#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <set>

using namespace std;

struct elem
{
	int x;
	int y;
	int dist;
	int pot;

	bool operator < ( const elem a ) const
	{
		return ( dist + pot ) > ( a.dist + a.pot );
	}
};

class TElement
{
public:
	string s1;
	string s2;
	int len1;
	int len2;
	elem tmp;

	set < pair < int, int > > used;
	priority_queue < elem > q;

	int set_potential ( int x, int y );
	void a_star();

	TElement();
	TElement( string s1, string s2 ): s1(s1), s2(s2)
	{
		len1 = s1.length();
		len2 = s2.length();

		elem el;
		el.dist = el.pot = el.x = el.y = 0;
		q.push( el );
		used.clear();
	}

};

int TElement::set_potential ( int x, int y )
{
	return abs ( x - len1 ) + abs ( y - len2 );
}

void TElement::a_star()
{
	while ( ! q.empty() )
	{
		tmp = q.top();
		q.pop();

		if ( used.find( make_pair ( tmp.x, tmp.y ) ) != used.end() )
			continue;

		used.insert ( make_pair ( tmp.x, tmp.y ) );
		
		if ( ( tmp.x == len1 ) && ( tmp.y == len2 ) )
		{
			cout << "Changed: " << tmp.dist << endl;
			cout << "Remained stable: " << min( len1 - tmp.dist, len2 - tmp.dist ) << endl;
			break;
		}

		elem tmp2;
		if ( ( tmp.x != len1 ) && ( tmp.y != len2 )  && ( s1[tmp.x] == s2[tmp.y] ) )
		{
			tmp2.x = tmp.x + 1;
			tmp2.y = tmp.y + 1;
			tmp2.dist = tmp.dist;
			tmp2.pot = set_potential ( tmp.x + 1, tmp.y + 1 );

			q.push ( tmp2 );
		}

		if ( ( tmp.x != len1 ) && ( tmp.y != len2 )  && ( s1[tmp.x] != s2[tmp.y] ) )
		{
			tmp2.x = tmp.x + 1;
			tmp2.y = tmp.y + 1;
			tmp2.dist = tmp.dist + 1;
			tmp2.pot = set_potential ( tmp.x + 1, tmp.y + 1 );

			q.push ( tmp2 );
		}
		
		if ( tmp.x != len1 )
		{
			tmp2.x = tmp.x + 1;
			tmp2.y = tmp.y;
			tmp2.dist = tmp.dist + 1;
			tmp2.pot = set_potential ( tmp.x + 1, tmp.y );

			q.push ( tmp2 );
		}
		
		if ( tmp.y != len2 )
		{
			tmp2.x = tmp.x;
			tmp2.y = tmp.y + 1;
			tmp2.dist = tmp.dist + 1;
			tmp2.pot = set_potential ( tmp.x, tmp.y + 1 );

			q.push ( tmp2 );
		}
	}
}

int main()
{
	ifstream input1 ( "input1.txt" );
	ifstream input2 ( "input2.txt" );
	freopen ( "output.txt", "w", stdout );

	string s1, s2;
	getline( input1, s1, '\0' );
	getline( input2, s2, '\0' );

	TElement elem ( s1, s2 );
	elem.a_star();

	input1.close();
	input2.close();
	fclose (stdout);
	return 0;
}
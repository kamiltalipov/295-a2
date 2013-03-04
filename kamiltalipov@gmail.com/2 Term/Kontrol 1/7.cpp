#include <iostream>
using std :: cin;
using std :: cout;
#include <map>
using std :: map;
#include <string>
using std :: string;
#include <utility>
using std :: pair;
using std :: make_pair;

class BadCopy {

public:

    explicit BadCopy( int val = -1 ) : value( val ) {}

BadCopy( const BadCopy& other ) {}

void operator=( const BadCopy& other ) {}

    void SetValue( int val ) { value = val; }

    int GetValue() { return value; }

private:

    int value;
};

int main ()
{
    map<string, BadCopy> a;
	a["abcd"].SetValue (5);
    for (map<string, BadCopy> :: iterator i = a.begin (); i != a.end (); ++i)
        cout << i->second.GetValue ();

    return 0;
}

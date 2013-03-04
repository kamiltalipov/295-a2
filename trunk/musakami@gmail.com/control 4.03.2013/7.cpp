#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <stack>
#include <cstdlib>
#include <string>
#include <string.h>
#include <list>

using namespace std;

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

int main()
{
    map<string, BadCopy> m;
    pair<map<string, BadCopy>::iterator, bool> p = m.insert(make_pair("hello", BadCopy()));
    (*p.first).second.SetValue(5);
    cout << (*m.find("hello")).second.GetValue();
    return 0;
}

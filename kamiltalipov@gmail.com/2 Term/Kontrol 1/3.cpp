#include <iostream>
using std :: cin;
using std :: cout;
#include <map>
using std :: map;
#include <string>
using std :: string;

int getElem (const map<string, int>& a, const string& i)
{
    map<string, int> :: const_iterator j = a.find (i);
    if (j == a.end ())
        return -1;
    return j->second;
}


int main ()
{
    map<string, int> a;
    a["dddd"] = 4;
    cout << getElem (a, "dddd") << '\n';
    cout << getElem (a, "fdfff") << '\n';


    return 0;
}

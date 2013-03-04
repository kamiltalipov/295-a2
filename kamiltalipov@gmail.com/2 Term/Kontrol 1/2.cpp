#include <iostream>
using std :: cin;
using std :: cout;
#include <set>
using std :: set;


int main ()
{
    set<int> s;
    //fill
    //s.insert (4);
    if (!s.insert (4).second)
        cout << "This element already exist\n";
    else
        cout << "This element is new\n";

    return 0;
}

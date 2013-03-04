#include <iostream>
using std :: cin;
using std :: cout;
#include <list>
using std :: list;
#include <algorithm>
using std :: swap;

void reverse (list<int>& l)
{
    list<int> :: iterator first = l.begin ();
    list<int> :: iterator last = l.end ();
    for (; first != last && first != --last; ++first)
        swap (*first, *last);
}

int main ()
{
    list<int> a;
    for (int i = 0; i < 10; ++i)
        a.push_back (i);

    reverse (a);
    for (list<int> :: const_iterator i = a.begin (); i != a.end (); ++i)
        cout << *i << ' ';

    return 0;
}

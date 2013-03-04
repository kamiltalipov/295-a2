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

int main()
{
    list<int> l;
    int n = 10;
    srand(42);
    for (int i = 0; i < n; i++)
        l.push_back(rand());
    for (list<int>::iterator i = l.begin(); i != l.end(); i++)
        cout << *i << " ";
    cout << endl;
    //l.reverse();
    list<int>::iterator it1 = l.begin();
    list<int>::reverse_iterator it2 = l.rbegin();
    for (int i = 0; i < n / 2; it1++, it2++, i++)
    {
        int k = *it1;
        *it1 = *it2;
        *it2 = k;
    }

    for (list<int>::iterator i = l.begin(); i != l.end(); i++)
        cout << *i << " ";
    return 0;
}

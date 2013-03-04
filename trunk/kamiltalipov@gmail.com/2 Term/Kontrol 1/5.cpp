#include <iostream>
using std :: cin;
using std :: cout;
#include <string>
using std :: string;


void replace (string& str, int n)
{
    for (int i = 0; i < str.size (); i += n)
        str[i] = 'a';
}

int main ()
{
    string a = "fffffsdfddfd";
    replace (a, 3);
    cout << a;

    return 0;
}

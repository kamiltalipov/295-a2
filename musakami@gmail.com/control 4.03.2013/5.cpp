#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <stack>
#include <cstdlib>
#include <string>
#include <string.h>

using namespace std;

int main()
{
    string s;
    cin >> s;
    int N = s.length();
    int n;
    cin >> n;
    for (int i = n - 1; i < N; i += n)
        s[i] = 'a';
    cout << s;
    return 0;
}

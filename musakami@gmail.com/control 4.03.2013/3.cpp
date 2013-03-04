#include <iostream>
#include <set>
#include <map>

using namespace std;

int check(map<string, int> &m, string &s)
{
    map<string, int>::iterator it = m.find(s);
    if (it == m.end())
        return -1;
    return (*it).second;
}

int main()
{
    map<string, int> m;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string k1;
        int k2;
        cin >> k1 >> k2;
        m.insert(make_pair(k1, k2));
    }
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string k1;
        cin >> k1;
        cout << check(m, k1) << endl;
    }
    return 0;
}

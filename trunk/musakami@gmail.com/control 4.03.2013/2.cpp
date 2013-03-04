#include <iostream>
#include <set>

using namespace std;



int main()
{
    set<int> s;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int k;
        cin >> k;
        if (s.insert(k).second)
            cout << "Added" << endl;
        else
            cout << "Already exists" << endl;
    }
    return 0;
}
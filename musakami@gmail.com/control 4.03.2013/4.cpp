#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <stack>
#include <cstdlib>

using namespace std;

int main()
{
    vector<int> v;
    int n = 5;
    srand(42);
    for (int i = 0; i < n; i++)
    {
        v.push_back(rand());
    }
    stack<int, vector<int> > s(v);
    for (int i = 0; i < n; i++)
    {
        cout << s.top() << " ";
        s.pop();
    }
    return 0;
}

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cstdlib>
#include <cstdio>
using namespace std;

vector < vector < pair < int, int > > > gr;
vector < int > d;

int main()
{
    int m;
    cin >> m;
    for (int i = 0, a, b, c; i < m; ++i)
    {
        cin >> a >> b >> c;
        gr.resize(max((int)gr.size(), max(a, b)));
        gr[a - 1].push_back(make_pair(b - 1, c));
        gr[b - 1].push_back(make_pair(a - 1, c));
    }
    d.assing(n, (int)2e9);
    //Hear must be a dejkstra algorithm, it's in "dejkstra.cpp"
    //Next task is the same
    return 0;
}
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cstdlib>
#include <cstdio>
using namespace std;

vector < vector < int > > gr;
vector < int > marks;
const int NONE = -1, A_GROUP = 0, B_GROUP = 1;

void dfs(int v, int prev = NONE)
{
    for (int i = 0; i < gr[v].size(); ++i)
    {
        if (gr[v][i] == prev || 
            marks[ gr[v][i] ] == (marks[v] + 1) % 2)
            continue;
        if (marks[ gr[v][i] ] == marks[v])
        {
            cout << "NO SOLUTION";
            exit(EXIT_SUCCESS);
        }
        marks[ gr[v][i] ] = (marks[v] + 1) % 2;
        dfs(gr[v][i], v);
    }
}

int main()
{
    int n, a;
    cin >> n;
    gr.resize(n);
    marks.assign(n, -1);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
        {
            cin >> a;
            if (a)
            {
                gr[i].push_back(j);
                gr[j].push_back(i);
            }
        }
    for (int i = 0; i < n; ++i)
    {
        if (marks[i] != NONE)
            continue;
        marks[i] = A_GROUP;
        dfs(i);
    }
    for (int i = 0; i < n; ++i)
        cout << marks[i] << " ";
    return 0;
}
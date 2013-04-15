#include <iostream>
#include <vector>

using namespace std;

bool dfs(int v, vector< vector<bool> > &field, vector<int> &color)
{
    for (int i = 0; i < field[v].size(); i++)
        if (field[v][i])
            if (color[i] == 0)
            {
                color[i] = 3 - color[v];
                if (!dfs(i, field, color))
                    return false;
            }
            else
                if (color[i] == color[v])
                    return false;
    return true;
}

int main()
{
    int n;
    cin >> n;
    vector< vector<bool> > f(n);
    vector<int> color(n, 0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            int k;
            cin >> k;
            f[i].push_back(k == 1);
        }
    for (int i = 0; i < n; i++)
        if (color[i] == 0)
        {
            color[i] = 1;
            if (!dfs(i, f, color))
            {
                cout << "NO";
                return 0;
            }
        }
    cout << "YES";
    return 0;
}

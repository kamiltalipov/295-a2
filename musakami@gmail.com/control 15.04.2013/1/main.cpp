#include <iostream>
#include <vector>


using namespace std;

void dfs(int y, int x, vector< vector<bool> > &field, int &n, int &m)
{
    if (y >= 0 && y < n && x >= 0 && x < m && field[y][x])
    {
        field[y][x] = false;
        dfs(y - 1, x, field, n, m);
        dfs(y, x - 1, field, n, m);
        dfs(y, x + 1, field, n, m);
        dfs(y + 1, x, field, n, m);
    }
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector< vector<bool> > f(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            int k;
            cin >> k;
            f[i].push_back(k == 1);
        }
    int cnt = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (f[i][j])
            {
                cnt++;
                dfs(i, j, f, n, m);
            }
    cout << cnt;
    return 0;
}

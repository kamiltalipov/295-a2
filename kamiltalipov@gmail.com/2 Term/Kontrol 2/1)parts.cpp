#include <iostream>
using std :: cin;
using std :: cout;
#include <vector>
using std :: vector;

void go (const vector<vector<int> >& map, int x, int y,
         vector<vector<bool> >& was)
{
    if (was[x][y])
        return;
    was[x][y] = true;

    if (x - 1 > 0 && map[x - 1][y])
        go (map, x - 1, y, was);
    if (y - 1 > 0 && map[x][y - 1])
        go (map, x, y - 1, was);
    if (x + 1 < map.size () && map[x + 1][y])
        go (map, x + 1, y, was);
    if (y + 1 < map[x].size () && map[x][y + 1])
        go (map, x, y + 1, was);
}

size_t countParts (const vector<vector<int> >& map)
{
    vector<vector<bool> > was (map.size (), vector<bool> (map[0].size (), false));
    size_t parts = 0;
    for (int i = 0; i < map.size (); ++i)
        for (int j = 0; j < map[i].size (); ++j)
            if (!was[i][j] && map[i][j])
            {
                ++parts;
                go (map, i, j, was);
            }

    return parts;
}


int main ()
{
    size_t n, m;
    cin >> n >> m;
    vector<vector<int> > map (n, vector<int> (m, 0));
    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < m; ++j)
            cin >> map[i][j];

    cout << countParts (map);

    return 0;
}

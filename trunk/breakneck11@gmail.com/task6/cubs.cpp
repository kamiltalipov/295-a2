#include <iostream>
#include <string>
#include <algorihm>
#include <vector>
using namespace std;

const int CUB_SIZE = 6, NONE = -1;
int n, n1;
vector < int > n2c, c2n, n2c_par, c2n_par;
string s, name;
vector < bool >  marks;

inline void connect(int let, int cub)
{
    n2c_par[let] = cub;
    c2n_par[cub] = let;
}

bool try_par(int v)
{
    if (marks[v]) return false;
    marks[v] = true;
    for (int i = 0; i < n2c[v].size(); ++i)
        if (c2n_par[n2c[v][i]] == NONE || try_par(c2n_par[n2c[v][i]]))
        {
            connect(v, n2c[v][i]);
            return true;
        }
    return false;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> n;
    cin >> name;
    n1 = name.length();
    for (int i = 0; i < n; ++i)
    {
        cin >> s;
        for (int k = 0; k < CUB_SIZE; ++k)
            for (int j = 0; j < n1; ++j)
                if (s[k] == name[j])
                {
                    n2c[j].push_back(i);
                    c2n[i].push_back(j);
                }
    }
    n2c_par.assign(n1, NONE);
    c2n_par.assign(n, NONE);
    for (int i = 0; i < n1; ++i)
    {
        for (int j = 0; j < n2c[i].size(); ++j)
            if (c2n_par[ n2c[i][j] ] == NONE)
            {
                connect(i, n2c[i][j]);
                break;
            }
        if (n2c_par[i] == NONE)
        {
            for (int j = 0; j < n2c[i].size(); ++j)
            {
                fill(marks.begin(), marks.end(), false);
                if (try_par(c2n_par[n2c[i][j]]))
                {
                    connect(i, n2c[i][j]);
                    break;
                }
            }
        }
    }
    if (find(n2c_par.begin(), n2c_par.end(), NONE) != n2c_par.end())
    {
    	cout << "NO" << endl;
	return 0;
    }
    cout << "YES" << endl;
    for (int i = 0; i < n1; ++i)
        cout << n2c_par[i] + 1 << " ";
    return 0;
}

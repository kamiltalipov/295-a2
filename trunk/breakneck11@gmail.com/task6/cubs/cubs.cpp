#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

const int NONE = -1; /* Is there any other good way to decline constants,
used in a few functions, except passing them as arguments? */

inline void connect(vector < int >& n2c_par,
    vector < int >& c2n_par, const int let, const int cub)
{
    n2c_par[let] = cub;
    c2n_par[cub] = let;
}

bool try_par(const vector < vector < int > >& n2c, const vector < vector < int > >& c2n,
    vector < int >& n2c_par, vector < int >& c2n_par,
    vector < bool >& marks, const int v)
{
    if (marks[v])
   	 return false;
    marks[v] = true;
    for (int i = 0; i < n2c.size(); ++i)
        if (c2n_par[ n2c[v][i] ] == NONE ||
	try_par(n2c, c2n, n2c_par, c2n_par, marks, c2n_par[ n2c[v][i] ] )
	)
        {
            connect(n2c_par, c2n_par, v, n2c[v][i]);
            return true;
        }
    return false;
}

int main()
{
    const int CUB_SIZE = 6, NONE = -1;
    int n, n1;
    vector < vector < int > > n2c, c2n;
    vector < int > n2c_par, c2n_par;
    string s, name;
    vector < bool >  marks;
    cin >> n;
    cin >> name;
    n1 = name.length();
    if (n < n1)
    {
    	cout << "NO";
	return 0;
    }
    n2c.resize(n1);
    c2n.resize(n);
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
                connect(n2c_par, c2n_par, i, n2c[i][j]);
                break;
            }
        if (n2c_par[i] == NONE)
        {
            for (int j = 0; j < n2c[i].size(); ++j)
            {
                fill(marks.begin(), marks.end(), false);
                if (try_par(n2c, c2n, n2c_par, c2n_par, marks, c2n_par[n2c[i][j]]))
                {
                    connect(n2c_par, c2n_par, i, n2c[i][j]);
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

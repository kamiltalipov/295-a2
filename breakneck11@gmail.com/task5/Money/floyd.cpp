#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void print_circle(const vector < vector < int > >& prevs, int v, int u)
{
	int k = prevs[v][u];
	if (k == -1)
	{
		cout << v << " ";
		return;
	}
	print_circle(prevs, v, k);
	print_circle(prevs, k, u);
}

int main()
{
	int n, m;
	cin >> n >> m;
	vector < vector < double > > gr(n);
	vector < vector < int > > prevs(n, vector < int > (-1, n));
	for (int i = 0; i < m; ++i)
	{
		int a, b;
		double c;
		cin >> a >> b >> c;
		gr[a - 1][b - 1] =  1 - c;
	}
	for (int k = 0; k < n; ++k)
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				if (gr[i][j] > gr[i][k] + gr[k][j])
				{
					prevs[i][j] = k;
					gr[i][j] = gr[i][k] + gr[k][j];
					if (i == j && gr[i][j] < 0)
					{
						print_circle(prevs, i, i);
						cout << i + 1 << " ";
						return 0;
					}
				}
	return 0;
}

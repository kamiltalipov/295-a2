#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

const double MAX_WEIGHT = 1000000000;

struct arc {
	unsigned first, second;
	double weight;
};

double Karp(unsigned n, const vector<arc>& arcs)
{
	unsigned m = arcs.size();
	vector<vector<double>> d(n+1);

	d[0].resize(n,MAX_WEIGHT);
	d[0][0] = 0;
	for (unsigned k = 1; k <= n; ++k) {
		d[k].resize(n,MAX_WEIGHT);
		for (unsigned j = 0; j < arcs.size(); ++j) {
			unsigned u = arcs[j].first;
			unsigned v = arcs[j].second;

			d[k][v] = min(d[k][v],d[k-1][u]+arcs[j].weight);
		}
	}

	double result;
	for (unsigned u = 0; u < n; ++u) {
		double a = (d[n][u]-d[0][u])/n;
		for (unsigned k = 1; k < n; ++k) a = max(a,(d[n][u]-d[k][u])/(n-k));
		if (!u || a < result) result = a; 
	}
	return result;
}

int main()
{
	unsigned n, m;
	cin >> n >> m;

	vector<arc> arcs(m);
	for (unsigned i = 0; i < m; ++i)
		cin >> arcs[i].first >> arcs[i].second >> arcs[i].weight;

	cout << Karp(n,arcs);
	return 0;
}
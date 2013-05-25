#include <iostream>
#include <vector>
#include <complex>
#include <cfloat>
#include <cmath>
#include <cstdlib>

using namespace std;

typedef complex<double> point;

const double EPS = 0.00000001;

point Box_Muller(const point& centre, double sigma)
{
	double x, y, s;
	do {
		x = 2.0*rand()/RAND_MAX-1;
		y = 2.0*rand()/RAND_MAX-1;
		s = x*x+y*y;
	} while (s<=EPS || s>1-EPS);

	double ln = log(s);
	return centre + sigma*point(x*sqrt(-2.0*ln/s),y*sqrt(-2.0*ln/s));
}

double dist(const point a, const point & b)
{
	return abs(a-b);
}

void Prim(const vector<point>& points, vector<vector<size_t>>& MST)
{
	size_t n = points.size();
	vector<double> min_dist(n,DBL_MAX);
	vector<bool> used(n);
	vector<size_t> prev(n);

	MST.clear();
	MST.resize(n);
	for (size_t k = 0; k<n; ++k) {
		size_t i_min = 0;
		for (size_t i = 0; i<n; ++i)
			if (used[i_min] || !used[i]&&min_dist[i]<min_dist[i_min]) i_min = i;
		if (i_min) MST[prev[i_min]].push_back(i_min);
		for (size_t i = 0; i<n; ++i) {
			double new_dist = dist(points[i_min],points[i]);
			if (new_dist<min_dist[i]) {
				min_dist[i] = new_dist;
				prev[i] = i_min;
			}
		}
		used[i_min] = true;
	}
}

void DFS_visit(const vector<vector<size_t>>& tree, size_t u, vector<size_t>& list)
{
	list.push_back(u);
	for (size_t i = 0; i<tree[u].size(); ++i)
		DFS_visit(tree,tree[u][i],list);
}

void DFS(const vector<vector<size_t>>& tree, vector<size_t>& list)
{
	list.clear();
	DFS_visit(tree,0,list);
	list.push_back(0);
}

const size_t N = 100;
const size_t M = 100;
const double SIGMA1 = 100;
const double SIGMA2 = 10;

int main()
{
	vector<point> points;
	for (size_t i = 0; i<N; ++i) {
		point c = Box_Muller(0,SIGMA1);
		for (size_t i = 0; i<M;i++)
			points.push_back(Box_Muller(c,SIGMA2));
	}
	vector<vector<size_t>> MST;
	Prim(points,MST);
	vector<size_t> list;
	DFS(MST,list);
	return 0;
}
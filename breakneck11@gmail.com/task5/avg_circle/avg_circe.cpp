#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

struct edge
{
	int a, b;
	double cost;
	edge() : a(-1), b(-1) {}
	edge(int a, int b, double cost) : a(a), b(b), cost(cost) {}
};

class Solver
{
private:
	vector < edge > gr;
	int n;
public:
	Solver(const vector < edge >& gr) : gr(gr)
	{
		set < int > st;
		for_each(gr.begin(), gr.end(), [&](const edge& e) { st.insert(e.a); st.insert(e.b); });
		n = st.size();
	}
	inline bool FindNegativeCircle(const double delta) const;
};

inline bool Solver::FindNegativeCircle(const double delta) const
{
	bool changed = true;
	vector < int > ds(n);
	int step;
	for (step = 0; step < n && changed; ++step)
		for (int i = 0; i < gr.size(); ++i)
		{
			if (ds[gr[i].b] > ds[gr[i].a] + (gr[i].cost - delt))
				ds[gr[i].b] = ds[gr[i].a] + (gr[i].cost - delt);
			if (ds[gr[i].a] < 0 || ds[gr[i].b] < 0)
				return true;
		}
	return step == n - 1 && changed;
}

int main()
{
	vector < edges > gr;
	register double L = 0, R = (int)2e9, m;
	//Reading graph, R = max_element(abs(Edges))
	Solver svl(gr);
	const double eps = 1e-5;
	while (R - L < eps)
	{
		m = (L + R) / 2;
		if (slv.FindNegativeCircle(m))
			L = m;
		else
			R = m;
	}
	return 0;
}

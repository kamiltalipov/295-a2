#include <iostream>
#include <vector>
#include <stdlib.h>
using namespace std;

template < class IDType >
class DSU
{
public:
	const IDType& GetRoot(int v);
	const IDType& Unite(int v1, int v2);
	template < class IteratorType >
	DSU(IteratorType begin, IteratorType end) : syst(vector < IDType >(begin, end)) {}
	const vector < IDType > GetSets() { return syst; }
private:
	vector< IDType > syst;
};

template < class IDType >
const IDType& DSU<IDType>::GetRoot(int v) { return syst[v] == v ? v : syst[v] = GetRoot(syst[v]); }

template < class IDType >
const IDType& DSU<IDType>::Unite(int v1, int v2)
{
	v1 = GetRoot(v1);
	v2 = GetRoot(v2);
	if (rand() & 1)
		swap(v1, v2);
	return syst[v1] = v2;
}

int main()
{
	int n, m, q;
	cin >> n >> m >> q;
	vector < int > arr(n);
	for (int i = 0; i < n; ++i) arr[i] = i;
	DSU < int > dsu_system(arr.begin(), arr.end());
	arr.clear();
	for (int i = 0, x, y; i < m; ++i)
	{
		cin >> x >> y;
		dsu_system.Unite(x, y);
	}
	const int GET = 0, SET = 1;
	for (int i = 0, a, b, c; i < q; ++i)
	{
		cin >> a >> b >> c;
		if (a == GET)
			cout << (dsu_system.GetRoot(b) == dsu_system.GetRoot(c) ? "YES" : "NO") << " ";
		else
			dsu_system.Unite(b, c);
	}
	system("PAUSE");
	return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
using namespace std;

class DSU
{
private:
	vector < int > ids;
	vector < int > marks;
public:
	DSU(int n) : ids(n), marks(n) { for (int i = 0; i < n; ++i) ids[i] = marks[i] = i; }
	int GetSet(int id) { return ids[id] == id ? id : ids[id] = GetSet(ids[id]); }
	void Unite(int a, int b, int accesor);
	int GetAccesor(int id) { return marks[GetSet(id)]; }
};

void DSU::Unite(int a, int b, int accesor)
{
	a = GetSet(a), b = GetSet(b);
	if (rand() & 1)
		swap(a, b);
	ids[b] = a;
	marks[a] = accesor;
}

vector < vector < int > > gr, pairs;
vector < bool > marks;
DSU dsu(0);
map < pair < int, int > , int > ans;

void dfs(int v)
{
	for (int i = 0; i < gr[v].size(); ++i)
	{
		dfs(gr[v][i]);
		dsu.Unite(v, gr[v][i], v);
	}
	marks[v] = true;
	for (int i = 0; i < pairs[v].size(); ++i)
		if (marks[pairs[v][i]])
			ans[ make_pair(v, pairs[v][i]) ] = dsu.GetAccesor(pairs[v][i]);
}

int main()
{
	int n;
	cin >> n;
	gr.resize(n), pairs.resize(n), marks.resize(n);
	vector < pair < int, int > > qs;
	dsu = DSU(n);
	string str;
	for (int i = 0, a, b; i < n; ++i)
	{
		cin >> str >> a >> b;
		if (str == "ADD")
			gr[a - 1].push_back(b - 1);
		else
		{
			pairs[a - 1].push_back(b - 1);
			pairs[b - 1].push_back(a - 1);
			qs.push_back( make_pair(a - 1, b - 1) );
		}
	}
	dfs(0);
	for (
	system("pause");
	return 0;
}
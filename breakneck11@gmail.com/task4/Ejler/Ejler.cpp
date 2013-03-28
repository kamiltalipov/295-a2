#include <iostream>
#include <vector>
#include <stack>
#include <assert.h>
#include <algorithm>
using namespace std;

class EjlerGraph
{
public:
	EjlerGraph(int V) : gr(vector< vector < int > > (V)) {}
	void AddEdge(int v, int to) { assert(v < gr.size()); gr[v].push_back(to); }
	void Find(vector < int > &ans) const;
	~EjlerGraph();
private:
	int is_possible() const;
	vector < vector < int > > gr;
};

void EjlerGraph::Find(vector < int > &ans) const
{
	ans.clear();
	int start = is_possible(), now;
	if (start < 0) return;
	vector < int > act(gr.size());
	stack < int, vector < int > > st;
	st.push(start);
	while (!st.empty())
	{
		now = st.top();
		if (act[now] == gr[now].size())
		{
			ans.push_back(now);
			st.pop();
			continue;
		}
		st.push(gr[now][act[now]++]);
	}
	for (int i = 0; i < gr[i].size(); ++i)
		if (act[i] < gr[i].size())
			return void( ans.clear() );
	reverse(ans.begin(), ans.end());
}

int EjlerGraph::is_possible() const
{
	vector < int > balance(gr.size());
	for (int i = 0; i < gr.size(); ++i)
	{
		for (int j = 0; i < gr[i].size(); ++j)
			++balance[gr[i][j]], --balance[i];
	}
	int start = 0;
	for (int i = 0; i < gr[i].size(); ++i)
		if (!balance[i] && gr[i].size())
			start = i;
		else if (balance[i])
			return -1;
	return start;
}

int main()
{
	return 0;
}
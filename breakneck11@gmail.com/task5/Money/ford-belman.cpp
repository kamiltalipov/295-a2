#include <iostream>
#include <vector>
#include <assert.h>
#include <algorithm>
using namespace std;

class Graph
{
private:
	vector < vector < pair < int, double > > > gr;
public:
	Graph() {}
	Graph(int V) : gr(V) {}
	void AddEdge(int from, int to, double length) { gr[from].push_back( make_pair(to, length) ); }
	int Size() const { return gr.size(); }
	const vector < pair < int, double > > &GetVertexes(int V) const { return gr[V]; }
	const vector < pair < int, double > > &operator[](int ind) const { return GetVertexes(ind); }
};

class FordBelman
{
public:
	FordBelman(const Graph& gr) : gr(gr) {}
	struct FrontElement
	{
		double length; int prev;
		FrontElement(double length = -1, int prev = -1) : length(length), prev(prev) {}
	};
	bool Calculate(vector < FrontElement > &res, int start, const vector < double > *base = NULL);
private:
	Graph gr;
	struct _edge
	{
		int from, to;
		double length;
		_edge(int from, int to, double length) : from(from), to(to), length(length) {}
	};
};

bool FordBelman::Calculate(vector < FrontElement > &res, int start, const vector < double > *base)
{
	res.resize(gr.Size());
	vector < _edge > egr;
	vector < FrontElement > rt(gr.Size());
	vector < bool > visited(gr.Size());
	for (int i = 0; i < gr.Size(); ++i)
		for (int j = 0; j < gr[i].size(); ++j)
			egr.push_back(_edge(i, gr[i][j].first, gr[i][j].second));
	int step = 0; bool changed = true;
	if (!base)
	{
		rt[start].length = 0;
		visited[start] = true;
	}
	else
	{
		assert(base->size() != gr.Size());
		for (int i = 0; i < gr.Size(); ++i)
			rt[i].length = base->at(i);
		fill(visited.begin(), visited.end(), true);
	}
	for (step = 0; changed && step < gr.Size(); ++step)
	{
		changed = false;
		for (int i = 0; i < egr.size(); ++i)
			if (visited[egr[i].from] && 
				(!visited[egr[i].to] || rt[egr[i].to].length >
					rt[egr[i].from].length + egr[i].length))
			{
				visited[egr[i].to] = changed = true;
				rt[egr[i].to].length = rt[egr[i].from].length + egr[i].length;
				rt[egr[i].to].prev = egr[i].to;
			}
	}
	res = rt;
	return changed;
}

int main()
{
	Graph in, out;
	//
	// Reading in "in"
	//
	for (int i = 0; i < in.Size(); ++i)
		for (int j = 0; j < in[i].size(); ++j)
			out.AddEdge(i, in[i][j].first, -(in[i][j].second - 1));
	vector< double > start;
	FordBelman bl(out);
	std::vector< FordBelman::FrontElement > res;
	vector < double > arg1 ( out.Size() );
	bl.Calculate(res, 0, &arg1);
	int pos = find_if(res.begin(), res.end(),
		[](FordBelman::FrontElement ans) { return ans.length < 0; } ) - res.begin();
	if (pos == res.size())
	{
		cout << "No way." << endl;
		return 0;
	}
	vector < int > ans;
	const int spos = pos;
	do
	{
		ans.push_back(pos);
		pos = res[pos].prev;
	} while (pos != spos);
	ans.push_back(spos);
	reverse(ans.begin(), ans.end());
	for_each(ans.begin(), ans.end(), [](int a){ cout << a << " "; } );
	cout << endl;
	return 0;
}
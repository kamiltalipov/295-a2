#include <iostream>
#include <vector>
#include <limits.h>
#include <algorithm>
using namespace std;

class Graph
{
private:
	vector < vector < pair < int, int > > > gr;
public:
	Graph() {}
	Graph(int V) : gr(V) {}
	void AddEdge(int from, int to, int length) { gr[from].push_back( make_pair(to, length) ); }
	int Size() const { return gr.size(); }
	const vector < pair < int, int > > &GetVertexes(int V) { return gr[V]; }
};

const int NONE = -1;

struct FrontElement
{
	int vertex;
	int length;
	int previous;
	FrontElement(int vertex = NONE, int length = NONE, int previous = NONE) :
		vertex(vertex), length(length), previous(previous) {}
};

template < class FrontContainer >
class Dejkstra
{
private:
	Graph graph;
	FrontContainer front;
	vector < FrontElement > res_tree;
public:
	Dejkstra(const Graph &graph, const FrontContainer &front, int start = 0) :
		graph(graph), front(front), res_tree(graph.Size())
		{
			for (int i = 0; i < graph.Size(); ++i)
			{
				res_tree[i].vertex = i;
				res_tree[i].length = res_tree[i].previous = NONE;
			}
			res_tree[start].length = 0;
			this->front.Add( res_tree[start] );
		}
	void RunDejkstra(vector< FrontElement > &res);
};

template < class FrontContainer >
void Dejkstra < FrontContainer >::RunDejkstra(vector< FrontElement > &res)
{
	while ( !front.Empty() )
	{
		const FrontElement now = front.ExtractMin();
		for (int i = 0; i < graph.GetVertexes( now.vertex ).size(); ++i)
		{
			int vert = graph.GetVertexes( now.vertex )[i].first, 
				ln = graph.GetVertexes( now.vertex )[i].second;
			if ( !front.Contain ( vert ) )
			{
				res_tree[ vert ].length = ln + now.length;
				res_tree[ vert ].previous = now.vertex;
				front.Add( res_tree[ vert ] );
			}
			else
				if ( res_tree[ vert ].length > ln + now.length )
				{
					res_tree[ vert ].length = ln + now.length;
					res_tree[ vert ].previous = now.vertex;
					front.Update( res_tree[ vert ] );
				}
		}
	}
	res = res_tree;
}

struct ArrayContainer
{
private:
	vector< FrontElement > data;
	vector< bool > marks;
	bool _ls(const FrontElement &a, const FrontElement &b)
	{
		return (!marks[a.vertex] && marks[b.vertex]) || a.length < b.length;
	}
public:
	ArrayContainer(int n) : data(vector< FrontElement >(n, FrontElement())), 
		marks(vector<bool>(n, false)) {}
	void Add(const FrontElement &el) { data[el.vertex] = el.length; }
	bool Empty() const { return std::find(marks.begin(), marks.end(), false) != marks.end(); }
	bool Contain(const FrontElement &el) { return marks[el.vertex]; }
	void Update(const FrontElement &el) { data[el.vertex] = el.length; }
	FrontElement ExtractMin()
	{
		vector<FrontElement>::iterator it = min_element(data.begin(), data.end(), _ls);
		marks[it - data.begin()] = true;
		return *it;
	}
};

int main()
{
	Graph gr(5);
	Dejkstra < ArrayContainer > dej(gr, ArrayContainer(5));
	vector< FrontElement > v;
	dej.RunDejkstra(v);
	return 0;
}
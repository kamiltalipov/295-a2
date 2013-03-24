#include <cassert>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

enum colour { WHITE, BLACK };

void Kosaraju_DFS_visit(const vector<vector<unsigned>>& arcs, unsigned v, vector<colour>& colours, vector<unsigned>& list)
{
	assert(colours[v]==WHITE);
	colours[v] = BLACK;
	for (unsigned i = 0; i < arcs[v].size(); ++i) {
		unsigned u = arcs[v][i];
		if (colours[u] == WHITE) Kosaraju_DFS_visit(arcs,u,colours,list);
	}
	list.push_back(v);
}

void Kosaraju_DFS1(const vector<vector<unsigned>>& arcs, vector<unsigned>& list)
{
	unsigned n = arcs.size();
	vector<colour> colours(n,WHITE);

	list.clear();
	for (unsigned v = 0; v < n; ++v)
		if (colours[v] == WHITE) Kosaraju_DFS_visit(arcs,v,colours,list);
}

void Kosaraju_DFS2(const vector<vector<unsigned>>& arcs, const vector<unsigned>& list, vector<vector<unsigned>>& strongly_connected_components)
{
	unsigned n = arcs.size();
	vector<colour> colours(n,WHITE);

	assert(list.size()==n);
	strongly_connected_components.clear();
	for (unsigned i = 0; i < n; ++i) {
		unsigned v = list[i];
		if (colours[v] == WHITE) {
			strongly_connected_components.push_back(vector<unsigned>(0));
			Kosaraju_DFS_visit(arcs,v,colours,strongly_connected_components.back());
		}
	}
}


void Kosarju_strongly_connected_components(const vector<vector<unsigned>>& arcs, vector<vector<unsigned>>& strongly_connected_components)
{
	vector<unsigned> list;
	Kosaraju_DFS1(arcs,list);
	Kosaraju_DFS2(arcs,list,strongly_connected_components);
}

void Tarjan_DFS_visit(const vector<vector<unsigned>>& arcs, unsigned v,
	vector<vector<unsigned>>& strongly_connected_components,
	vector<colour>& colours, unsigned& time, vector<unsigned>& time_in, vector<unsigned>& low_time, vector<unsigned>& stack)
{
	assert(colours[v]==WHITE);
	colours[v] = BLACK;
	low_time[v] = time_in[v] = time++;
	stack.push_back(v);
	for (unsigned i = 0; i < arcs[v].size(); ++i) {
		unsigned w = arcs[v][i];
		if (colours[w] == WHITE) {
			Tarjan_DFS_visit(arcs,w,strongly_connected_components,colours,time,time_in,low_time,stack);
			low_time[v] = min(low_time[v],low_time[w]);
		}
		else
			low_time[v] = min(low_time[v],time_in[w]);
	}
	if (low_time[v] == time_in[v]) {
		strongly_connected_components.push_back(vector<unsigned>(0));
		
		unsigned w;
		vector<unsigned>& component = strongly_connected_components.back();
		do {
			component.push_back(w = stack.back());
			stack.pop_back();
		} while (w != v);
	}
}

void Tarjan_strongly_connected_components(const vector<vector<unsigned>>& arcs, vector<vector<unsigned>>& strongly_connected_components)
{
	unsigned n = arcs.size();
	vector<colour> colours(n,WHITE);
	unsigned time = 0;
	vector<unsigned> time_in(n);
	vector<unsigned> low_time(n);
	vector<unsigned> stack;

	for (unsigned v = 0; v < n; ++v)
		if (colours[v] == WHITE) Tarjan_DFS_visit(arcs,v,strongly_connected_components,colours,time,time_in,low_time,stack);
}

void read_graph(vector<vector<unsigned>>& arcs)
{
	unsigned n;
	cin >> n;
	arcs.resize(n);

	for (unsigned i = 0; i < n; ++i) {
		unsigned k;
		cin >> k;
		
		arcs[i].resize(k);
		for (unsigned j = 0; j < k; ++j) {
			cin >> arcs[i][j];
			--arcs[i][j];
		}
	}

}
void check_Kosaraju()
{
	vector<vector<unsigned>> arcs;
	read_graph(arcs);

	vector<vector<unsigned>> strongly_connected_components;
	Kosarju_strongly_connected_components(arcs,strongly_connected_components);
	cout << strongly_connected_components.size();
	for (unsigned i = 0; i < strongly_connected_components.size(); ++i) {
		cout << '\n';
		for (unsigned j = 0; j < strongly_connected_components[i].size(); ++i)
			cout << strongly_connected_components[i][j] << ' ';
	}
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	check_Kosaraju();
	_CrtDumpMemoryLeaks();
	return 0;
}
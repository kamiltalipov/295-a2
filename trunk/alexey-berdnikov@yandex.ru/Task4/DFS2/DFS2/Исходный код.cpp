#include <cassert>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

enum colour { WHITE, GREY, BLACK };

void get_two_edge_connected_component(unsigned v, vector<unsigned>& component, vector<unsigned>& stack)
{
	unsigned w;
	do {
		component.push_back(w=stack.back());
		stack.pop_back();
	} while (w != v);
}

void get_biconnected_component(const pair<unsigned, unsigned>& e, vector<pair<unsigned, unsigned>>& component, vector<pair<unsigned, unsigned>>& stack)
{
	pair<unsigned, unsigned> f;
	do {
		component.push_back(f=stack.back());
		stack.pop_back();
	} while (f != e);
}

void DFS_visit(const vector<vector<unsigned>>& edges, unsigned v, unsigned parent,
	vector<unsigned>& articulation_vertices, vector<pair<unsigned,unsigned>>& bridges,
	vector<vector<pair<unsigned, unsigned>>>& biconnected_components, vector<vector<unsigned>>& two_edge_connected_components,
	vector<colour>& colours, unsigned& time, vector<unsigned>& time_in, vector<unsigned>& low_time,
	vector<unsigned>& stack_vertices, vector<pair<unsigned, unsigned>>& stack_edges)
{
	assert(colours[v]==WHITE);
	colours[v] = GREY;
	low_time[v] = time_in[v] = time++;
	stack_vertices.push_back(v);

	unsigned children = 0;
	for (unsigned i = 0; i < edges[v].size(); ++i) {
		unsigned w = edges[v][i];
		if (w == parent || colours[w] == BLACK) continue;
		stack_edges.push_back(make_pair(v,w));
		if (colours[w] == WHITE) {
			++children;
			DFS_visit(edges,w,v,articulation_vertices,bridges,biconnected_components,two_edge_connected_components,colours,time,time_in,low_time,stack_vertices,stack_edges);
			low_time[v] = min(low_time[v],low_time[w]);
			if (low_time[w] >= time_in[v]) {
				if (parent != -1 || children > 1) articulation_vertices.push_back(v);
				biconnected_components.resize(biconnected_components.size()+1);
				get_biconnected_component(make_pair(v,w),biconnected_components.back(),stack_edges);
			}
		}
		else
			low_time[v] = min(low_time[v],time_in[w]);
	}
	colours[v] = BLACK;
	if (low_time[v] == time_in[v]) {
		if (parent != -1) bridges.push_back(make_pair(parent,v));
		two_edge_connected_components.resize(two_edge_connected_components.size()+1);
		get_two_edge_connected_component(v,two_edge_connected_components.back(),stack_vertices);
	}
}

void DFS(const vector<vector<unsigned>>& edges,
	vector<unsigned>& articulation_vertices, vector<pair<unsigned,unsigned>>& bridges,
	vector<vector<pair<unsigned, unsigned>>>& biconnected_components, vector<vector<unsigned>>& two_edge_connected_components)
{
	unsigned n = edges.size();
	vector<colour> colours(n,WHITE);
	unsigned time = 0;
	vector<unsigned> time_in(n);
	vector<unsigned> low_time(n);
	vector<unsigned> stack_vertices;
	vector<pair<unsigned, unsigned>> stack_edges;
	for (unsigned v = 0; v < n; ++v)
		if (colours[v] == WHITE)
			DFS_visit(edges,v,-1,articulation_vertices,bridges,biconnected_components,two_edge_connected_components,colours,time,time_in,low_time,stack_vertices,stack_edges);
}

void check()
{
	unsigned n;
	cin >> n;

	vector<vector<unsigned>> edges(n);
	for (unsigned i = 0; i < n; ++i) {
		unsigned k;
		cin >> k;
		
		edges[i].resize(k);
		for (unsigned j = 0; j < k; ++j) {
			cin >> edges[i][j];
			--edges[i][j];
		}
	}

	vector<unsigned> articulation_vertices;
	vector<pair<unsigned,unsigned>> bridges;
	vector<vector<pair<unsigned, unsigned>>> biconnected_components;
	vector<vector<unsigned>> two_edge_connected_components;
	DFS(edges,articulation_vertices,bridges,biconnected_components,two_edge_connected_components);

	cout << articulation_vertices.size() << '\n';
	for (unsigned i = 0; i < articulation_vertices.size(); ++i)
		cout << articulation_vertices[i]+1 << ' ';
	cout << '\n' << biconnected_components.size() << '\n';
	for (unsigned i = 0; i < biconnected_components.size(); ++i) {
		for (unsigned j = 0; j < biconnected_components[i].size(); ++j)
			cout << '(' << biconnected_components[i][j].first+1 << ", " << biconnected_components[i][j].second+1 << ") ";
		cout << '\n';
	}
	cout << bridges.size() << '\n';
	for (unsigned i = 0; i < bridges.size(); ++i)
		cout << '(' << bridges[i].first+1 << ", " << bridges[i].second+1 << ") ";
	cout << '\n' << two_edge_connected_components.size();
	for (unsigned i = 0; i < two_edge_connected_components.size(); ++i) {
		cout << '\n';
		for (unsigned j = 0; j < two_edge_connected_components[i].size(); ++j)
			cout << two_edge_connected_components[i][j]+1 << ' ';
	}
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	check();
	_CrtDumpMemoryLeaks();
	return 0;
}
#include <iostream>
using std :: cin;
using std :: cout;
#include <vector>
using std :: vector;
#include <utility>
using std :: pair;
using std :: make_pair;

typedef pair<size_t, size_t> Edge;
typedef pair<size_t, Edge> CostEdge;

const size_t INF = 2000000000;
const CostEdge NOT_SET = make_pair (-1, make_pair (-1, -1));

template<typename T>
void dfs (const vector<vector<pair<size_t, size_t> > >& g, size_t v,
		  vector<T>& prev, const T& prev_not_set, vector<size_t>& len)
{
	if (prev[v] != prev_not_set)
		return;
	
	for (size_t i = 0; i < g[v].size (); ++i)
	{
		if (prev[g[v][i].first] == prev_not_set)
		{
			prev[g[v][i].first] = static_cast<T> (v);
			len[g[v][i].first] = len[v] + g[v][i].second;
			dfs (g, g[v][i].first, prev, prev_not_set, len);
		}
	}
}

void findPath (const vector<vector<pair<size_t, size_t> > >& g, size_t v, 
			   vector<size_t>& prev, vector<size_t>& len)
{
	len[v] = 0;
	dfs (g, v, prev, static_cast<size_t> (-1), len);
}

void getComponent (const vector<vector<pair<size_t, size_t> > >& g, size_t v,
				   vector<bool>& component)
{
	vector<size_t> len (g.size (), INF);
	len[v] = 0;
	dfs (g, v, component, false, len);
}


void findEscapePath (const vector<CostEdge>& g, const vector<vector<pair<size_t, size_t> > >& spt,
					 size_t center_v, const Edge& deleted_edge, 
					 vector<size_t>& escape_prev)
{
	vector<size_t> prev (spt.size (), -1);
	vector<size_t> len (spt.size (), INF);
	findPath (spt, center_v, prev, len);

	vector<bool> component1 (spt.size (), false);
	getComponent (spt, deleted_edge.first, component1);
	
	escape_prev.reserve (prev.size ());
	escape_prev.insert (escape_prev.end (), prev.begin (), prev.end ());
	size_t deleted_v = deleted_edge.first;
	if (component1[center_v] == component1[deleted_edge.first])
		deleted_v = deleted_edge.second;
	
	vector<size_t> del_prev (spt.size (), -1);
	vector<size_t> del_len (spt.size (), INF);
	findPath (spt, deleted_v, del_prev, del_len);
	CostEdge escape_edge = NOT_SET;
	for (size_t i = 0; i < g.size (); ++i)
		if (component1[g[i].second.first] != component1[g[i].second.second])
		{
			size_t del_component_v = component1[g[i].second.first],
				   center_component_v = component1[g[i].second.second];
			if (component1[del_component_v] != component1[deleted_v])
			{
				 del_component_v = component1[g[i].second.second];
				 center_component_v = component1[g[i].second.first];
			}
			
			if (escape_edge == NOT_SET)
			{
				escape_edge = make_pair (g[i].first, make_pair (del_component_v, center_component_v));
			}
			else if (del_len[del_component_v] + g[i].first + len[center_component_v] <
					 del_len[escape_edge.second.first] + escape_edge.first + len[escape_edge.second.second])
			{
				escape_edge = make_pair (g[i].first, make_pair (del_component_v, center_component_v));
			}

		}

	vector<size_t> escape_path;
	escape_path.push_back (escape_edge.second.second);
	size_t cur_v = escape_edge.second.first;
	while (cur_v != deleted_v)
	{
		escape_path.push_back (cur_v);
		cur_v = del_prev[cur_v];
	}

	for	(int i = escape_path.size () - 1; i >= 0; --i)
	{
		escape_prev[cur_v] = escape_path[i];
		cur_v = escape_path[i];
	}
}

int main ()
{
	size_t all_v = 0;
	cin >> all_v;
	vector<vector<pair<size_t, size_t> > > spt (all_v);
	for (size_t i = 0; i < all_v - 1; ++i)
	{
		size_t v, u, cost;
		cin >> v >> u >> cost; 
		spt[v].push_back (make_pair (u, cost));
		spt[u].push_back (make_pair (v, cost));
	}
	
	size_t all_non_mst_e = 0;
	cin >> all_non_mst_e;
	vector<CostEdge> g (all_non_mst_e);
	for (size_t i = 0; i < all_non_mst_e; ++i)
		cin >> g[i].second.first >> g[i].second.first >> g[i].first;

	size_t center_v = 0;
	cin >> center_v;
	
	Edge deleted_edge;
	cin >> deleted_edge.first >> deleted_edge.second;
	


	return 0;
}
#include <iostream>
#include <vector>
#include <stack>
using namespace std;
void dfs(int v, int parent, int timer, vector <int> &tin, vector <int> &up, vector < vector <int> > &g, vector <int> &color, vector < pair<int, int> > &bridges, vector <bool> &cut_vertices, stack <int> &s_vertex, stack < pair<int, int> > &s_edge, vector < vector <int> > &edge_components, vector < vector < pair <int, int> > > &vertex_components)
{
	color[v]=1;
	tin[v]=up[v]=timer++;
	int children=0;
	s_vertex.push(v);
	for(int i=0; i<g[v].size(); ++i)
	{
		int to=g[v][i];
		if(to==parent)
			continue;
		if(color[to]==1)
		{
			up[v]=min(up[v], tin[to]);
			s_edge.push(make_pair(v, to));
		}
		if(color[to]==0)
		{
			s_edge.push(make_pair(v, to));
			dfs(to, v, timer, tin, up, g, color, bridges, cut_vertices, s_vertex, s_edge, edge_components, vertex_components);
			up[v]=min(up[v], up[to]);
			++children;
			if(up[to]>tin[v])
			{
				bridges.push_back(make_pair(v, to));
				edge_components.resize(edge_components.size()+1);
				int vertex;
				do
				{
					vertex=s_vertex.top();
					s_vertex.pop();
					edge_components[edge_components.size()-1].push_back(vertex);
				}
				while(vertex!=to);
			}
			if(up[to]>=tin[v]&&parent!=-1)
			{
				cut_vertices[v]=true;
				vertex_components.resize(vertex_components.size()+1);
				pair <int, int> edge;
				do
				{
					edge=s_edge.top();
					s_edge.pop();
					vertex_components[vertex_components.size()-1].push_back(edge);
				}
				while(edge!=make_pair(v, to));
			}
		}
	}
	color[v]=2;
	if(parent==-1&&children>1)
		cut_vertices[v]=true;
	if(parent==-1)
	{
		edge_components.resize(edge_components.size()+1);
		while(!s_vertex.empty())
		{
			edge_components[edge_components.size()-1].push_back(s_vertex.top());
			s_vertex.pop();
		}
		vertex_components.resize(vertex_components.size()+1);
		while(!s_edge.empty())
		{
			vertex_components[vertex_components.size()-1].push_back(s_edge.top());
			s_edge.pop();
		}
	}
}
int main()
{
	int n, m, timer=0;
	cin>>n>>m;
	vector < vector <int> > g(n), edge_components;
	vector <bool> cut_vertices(n);
	vector <int> color(n), tin(n), up(n);
	vector < pair<int, int> > bridges;
	vector < vector < pair <int, int> > > vertex_components;
	stack <int> s_vertex;
	stack < pair<int, int> > s_edge;
	for(int i=0; i<m; ++i)
	{
		int a, b;
		cin>>a>>b;
		g[a-1].push_back(b-1);
		g[b-1].push_back(a-1);
	}
	for(int i=0; i<n; ++i)
		if(color[i]==0)
			dfs(i, -1, timer, tin, up, g, color, bridges, cut_vertices, s_vertex, s_edge, edge_components, vertex_components);
	printf("Bridges:\n");
	if(bridges.size()==0)
		printf("No\n");
	for(int i=0; i<bridges.size(); ++i)
		printf("(%d, %d)\n", bridges[i].first+1, bridges[i].second+1);
	printf("Edge biconnected components:\n");
	for(int i=0; i<edge_components.size(); ++i)
	{
		for(int j=0; j<edge_components[i].size(); ++j)
			printf("%d ", edge_components[i][j]+1);
		printf("\n");
	}
	printf("Cut vertices:\n");
	bool b=false;
	for(int i=0; i<cut_vertices.size(); ++i)
		if(cut_vertices[i])
		{
			printf("%d\n", i+1);
			b=true;
		}
	if(!b)
		printf("No\n");
	printf("Vertex biconnected components:\n");
	for(int i=0; i<vertex_components.size(); ++i)
	{
		for(int j=0; j<vertex_components[i].size(); ++j)
			printf("(%d, %d) ", vertex_components[i][j].first+1, vertex_components[i][j].second+1);
		printf("\n");
	}
	return 0;
}
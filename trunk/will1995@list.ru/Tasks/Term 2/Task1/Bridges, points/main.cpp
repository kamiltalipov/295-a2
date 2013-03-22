#include <iostream>
#include <stdio.h>
#include <vector>
#include <list>
 
using namespace std;
 
class Graph
{
public:
    Graph(int size): size(size), time(0), points(0)
    {
        Vert.resize(size);
       
        Used.resize(size);
        Used.assign(size, 0);
 
        Added.resize(size);
        Added.assign(size, 0);
 
        tin.resize(size);
        tin.assign(size, 0);
		
        edge_comp.resize(size);
        edge_comp.assign(size, 0);
 
        fup.resize(size);
        fup.assign(size, 1000000);
    }
 
    Graph();
 
    void DFS(int vertex, int parent);
	void DFS2 (int vertex, int color, int parent);
    void Add (int vertex, int another_vertex);
 
//private:
    vector < vector < pair < int, int > > > Vert;
    vector < bool > Used;
    vector < bool > Added;
    vector < int > tin;
    vector < int > fup;
	vector < int > points;
	vector < pair <int, int> > bridges;
	vector < int > vert_comp;
	vector < int > edge_comp;
    int size;
    int time;
};
 
void Graph::Add(int v, int u)
{
    Vert[v].push_back(make_pair(u, -1));
}
 
void Graph::DFS2(int v, int c, int p)
{
	Used[v] = true;
	for (int i = 0; i < Vert[v].size(); i++)
	{
		int tmp = Vert[v][i].first;
		if (tmp == p)
			continue;
		if (!Used[i])
			if (fup[tmp] >= tin[v])
			{
				int c2 = c + 1;
				Vert[v][i].second = c2;
				DFS2(tmp, c2, v);
			}
			else
			{
				Vert[v][i].second = c;
				DFS2(tmp, c, v);
			}
		else
			if (tin[tmp] <= tin[v])
				Vert[v][i].second = c;
	}
}

void Graph::DFS(int v, int p = -1)
{
    Used[v] = true;
    tin[v] = fup[v] = time++;
    int child = 0;
    for (int i = 0; i < Vert[v].size(); i++)
    {
        int tmp = Vert[v][i].first;
        if (tmp == p)
            continue;
        if (Used[tmp])
            fup[v] = min (fup[v], tin[tmp]);
        else
        {
            DFS(tmp, v);
            fup[v] = min (fup[v], fup[tmp]);
            if (fup[tmp] >= tin[v] && p != -1 && !Added[v])
            {
                Added[v] = true;
				points.push_back(v);
            }
			if (fup[tmp] > tin[v])
			{
				bridges.push_back(make_pair(v, tmp));
			}
            child++;
        }
    }
    if (p == -1 && child > 1)
    {
        Added[v] = true;
		points.push_back(v);
    }
}
 
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
 
    int n, m;
    cin >> n >> m;
    Graph gr(n);
 
    for(int i = 0; i < m; i++)
    {
        int v, u;
        cin >> v >> u;
        gr.Add(v, u);
        gr.Add(u, v);
    }
 
    for (int i = 0; i < n; i++)
	{
		if (!gr.Used[i])
			gr.DFS(i);
	}

	gr.Used.assign(n, 0);

	for (int i = 0; i < gr.points.size(); i++)
		cout << gr.points[i] << " ";
	cout << endl;

	for (int i = 0; i < gr.bridges.size(); i++)
		cout << gr.bridges[i].first << '-' << gr.bridges[i].second << endl;

    for (int i = 0; i < n; i++)
	{
		if (!gr.Used[i])
			gr.DFS2(i, 0, -1);
	}

    fclose(stdin);
    fclose(stdout);
    return 0;
}
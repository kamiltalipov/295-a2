#include <iostream>
#include <stdio.h>
#include <vector>
#include <list>
#include <stack>
 
using namespace std;
 
class Graph
{
public:
    Graph(int size): size(size), comp_ind(1)
    {
        Vert.resize(size);
       
        Used.resize(size);
        Used.assign(size, 0);
    }
 
    Graph();
 
    void DFS1(int vertex);
    void DFS2(int vertex, int color);
    void Add (int vertex, int another_vertex);
	void Connect(int vertex, int &index);
 
//private:
    vector < vector < int > > Vert;
    vector < bool > Used;
	vector < bool > instack;
    vector < int > order;
    vector < int > comp;
	vector < int > index;
	vector < int > lowlink;
	stack < int > st;
	int size;
	int comp_ind;
};

void Graph::Add(int v, int u)
{
    Vert[v].push_back(u);
}

void Graph::DFS1 (int v)
{
	Used[v] = true;
	for (int i = 0; i < Vert[v].size(); i++)
		if (!Used[Vert[v][i]])
			DFS1(Vert[v][i]);
	order.push_back(v);
}

void Graph::DFS2(int v, int c)
{
	Used[v] = true;
	
	comp[v] = c;
	for (int i = 0; i < Vert[v].size(); i++)
		if (!Used[Vert[v][i]])
			DFS2(Vert[v][i], c);
}

void Kosaraju(Graph &gr, Graph &inv)
{
	int n = gr.Vert.size();
	for (int i = 0; i < n; i++)
		{
			if (!inv.Used[i])
				inv.DFS1(i);
		}

		gr.comp.resize(n);
		int c = 0;
		for (int i = 0; i < n; i++)
		{
			int tmp = inv.order[n - i - 1];
			if (!gr.Used[tmp])
			{
				c++;
				gr.DFS2(tmp, c);
			}
		}

		cout << c << endl;
		for (int i = 0; i < n; i++)
		{
			cout << gr.comp[i] << ' ';
		}
		cout << endl;
}

void Graph::Connect(int v, int &ind)
{
	index[v] = ind;
	lowlink[v] = ind;
	ind++;
	st.push(v);
	instack[v] = true;

	for (int i = 0; i < Vert[v].size(); i++)
	{
		if (index[Vert[v][i]] == 10000000)
		{
			Connect(Vert[v][i], ind);
			lowlink[v] = min(lowlink[v], lowlink[Vert[v][i]]);
		}
		else
			if (instack[Vert[v][i]])
				lowlink[v] = min(lowlink[v], index[Vert[v][i]]);
	}

	if (lowlink[v] == index[v])
	{
		int tmp;
		do
		{
			tmp = st.top();
			st.pop();
			instack[tmp] = false;
			comp[tmp] = comp_ind;
		}
		while (tmp != v);
		comp_ind++;
	}
}

void Tarjan(Graph &gr)
{
	int n = gr.Vert.size();
	gr.comp.assign(n, 0);
	gr.Used.assign(n, 0);

	gr.index.resize(n);
	gr.lowlink.resize(n);
	
	gr.index.assign(n, 10000000);
	gr.lowlink.assign(n, 10000000);
	
	gr.instack.resize(n);
	gr.instack.assign(n, 0);

	int index = 1;
	for (int i = 0; i < n; i++)
		if (gr.index[i] == 10000000)
			gr.Connect(i, index);

	for (int i = 0; i < n; i++)
		cout << gr.comp[i] << ' ';
	cout << endl;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
 
    int n, m;
    cin >> n >> m;
    Graph gr(n);
	Graph inv(n);

	for (int i = 0; i < m; i++)
	{
		int v, u;
		cin >> v >> u;
		gr.Add(v, u);
		inv.Add(u, v);
	}

	Kosaraju(gr, inv);
	Tarjan(gr);
    fclose(stdin);
    fclose(stdout);
    return 0;
}
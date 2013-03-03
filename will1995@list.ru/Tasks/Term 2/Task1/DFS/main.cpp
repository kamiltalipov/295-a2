#include <stdio.h>
#include <iostream>
#include <list>
#include <vector>
#include <queue>

using namespace std;

class Graph
{
public:
	Graph(int size): size(size)
	{
		Vert.resize(size);
		used.resize(size);
		used.assign(size, 0);
	}

	void Non_rec_DFS(int start);
	void Add (int v, int u);

//private:
	vector < list <int> > Vert; 
	vector <bool> used;
	int size;
};

void Graph::Add(int v, int u)
{
	Vert[v].push_back(u);
	Vert[u].push_back(v);
}

void Graph::Non_rec_DFS(int start)
{
	queue <int> q;
	q.push(start);

	while (!q.empty())
	{
		int tmp = q.back();
		q.pop();
		used[tmp] = 1;
		
		for(list <int>::iterator i = Vert[tmp].begin(); i != Vert[tmp].end(); i++)
		{
			if (!used[*i])
			{
				cout << tmp << ':' << *i << '\n';
				q.push(*i);
			}
		}
	}
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int n, m, v, u;
	cin >> n >> m;

	Graph gr(n);

	for (int i = 0; i < m; i++)
	{
		cin >> v >> u;
		gr.Add(v, u);
	}
	gr.Non_rec_DFS(1);

	fclose(stdin);
	fclose(stdout);
	return 0;
}

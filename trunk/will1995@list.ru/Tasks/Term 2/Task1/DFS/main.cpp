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

		
		for(list <int>::iterator i = Vert[tmp].begin(); i != Vert[tmp].end(); i++)
		{
			cout << tmp << ':' << *i << '\n';
			q.push(*i);
		}
	}
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int n, v, u;
	cin >> n;

	Graph gr(n);

	for (int i = 0; i < n; i++)
	{
		cin >> v >> u;
		gr.Add(v, u);
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}

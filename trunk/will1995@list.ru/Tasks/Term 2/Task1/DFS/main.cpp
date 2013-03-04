#include <stdio.h>
#include <iostream>
#include <list>
#include <vector>
#include <stack>

using namespace std;

class Graph
{
public:
	Graph(int size): size(size)
	{
		Vert.resize(size);
		color.resize(size);
		color.assign(size, 0);
	}

	void Non_rec_DFS(int start);
	void Add (int v, int u);

//private:
	vector < list <int> > Vert; 
	vector <bool> color;
	int size;
};

void Graph::Add(int v, int u)
{
	Vert[v].push_back(u);
}

void Graph::Non_rec_DFS(int start)
{
	stack <int> q;
	q.push(start);

	int count = 0;
	while (!q.empty())
	{
		int tmp = q.top();
		q.pop();
		if (color[tmp] == 0)
		{
			color[tmp] = 1;
			count++;
		
			for(list <int>::iterator i = Vert[tmp].begin(); i != Vert[tmp].end(); i++)
				q.push(*i);
		}
	}
	cout << count;
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int n, m, v, u;
	cin >> n >> m;

	Graph gr(n);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> v >> u;
			gr.Add(v, u);
		}
	}
	gr.Non_rec_DFS(m - 1);

	fclose(stdin);
	fclose(stdout);
	return 0;
}

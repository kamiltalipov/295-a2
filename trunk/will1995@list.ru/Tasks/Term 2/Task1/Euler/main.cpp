#include <iostream>
#include <stdio.h>
#include <vector>
#include <list>
#include <stack>

using namespace std;

class Graph
{
public:
	Graph(int size): size(size)
	{
		Vert.resize(size);
		diff.assign(size, 0);
	}

	void DFS(int vertex);
	void Add (int v, int u);
	void PrintCycle();

//private:
	vector < list <int> > Vert; 
	vector <int> diff;
	int size;
	stack < pair <int, int> > st;
};

void Graph::Add(int v, int u)
{
	Vert[v].push_back(u);
	diff[v]++;
	diff[u]--;
}

void Graph::DFS(int v)
{
	while(!Vert[v].empty())
	{
		list<int>::iterator it = Vert[v].begin();
		int tmp = *it;
		it = Vert[v].erase(it);
		st.push(make_pair(v, tmp));
		DFS(tmp);
	}
}

void Graph::PrintCycle()
{
	while (!st.empty())
	{
		cout << st.top().first << " - " << st.top().second << endl;
		st.pop();
	}
}

pair <int, int> Check (Graph &gr)
{
	pair <int, int> tmp = make_pair <int, int> (-100500, -100500);

	for (int i = 0; i < gr.diff.size(); i++)
	{
		if (gr.diff[i] == -1)
			if (tmp.first == -100500)
				tmp.first = i;
			else
			{
				tmp.first = -1;
				return tmp;
			}

		if (gr.diff[i]  == 1)
			if (tmp.second == -100500)
				tmp.second = i;
			else
			{
				tmp.first = -1;
				return tmp;
			}

		if (abs(gr.diff[i] ) > 1)
		{
			tmp.first = -1;
			return tmp;
		}
	}

	return tmp;
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

	pair <int, int> tmp = Check(gr);
	if (tmp.first == -1)
		cout << "No Euler cycles, sorry.\n";
	else 
		if ((tmp.first != -100500) || (tmp.second != -100500))
		{
			cout << "There's only an Euler path, here:\n";
			gr.Add(tmp.second, tmp.first);
			gr.DFS(0);
			gr.st.pop();
			gr.PrintCycle();
		}
		else
		{
			cout << "Here's the cycle:\n";
			gr.DFS(0);
			gr.PrintCycle();
		}

	fclose(stdin);
	fclose(stdout);
	return 0;
}
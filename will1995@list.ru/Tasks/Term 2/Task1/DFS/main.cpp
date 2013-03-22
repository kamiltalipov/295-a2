#include <stdio.h>
#include <iostream>
#include <algorithm>
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

	bool Non_rec_DFS(vector <int> &topsort);
	void Add (int v, int u);

//private:
	vector < vector <int> > Vert; 
	vector <char> color;
	int size;
};

void Graph::Add(int v, int u)
{
	Vert[v].push_back(u);
}

bool Graph::Non_rec_DFS(vector <int> &topsort)
{
	stack < pair <int, int> > q;
	topsort.clear();

	for (int i = 0; i < Vert.size(); i++)
		if (color[i] == 0)
		{
			q.push(make_pair(i, 0));
			while (!q.empty())
			{
				pair <int, int> &tmp = q.top();
				color[tmp.first] = 1;  
				if (tmp.second < Vert[tmp.first].size())
				{
					if (color[Vert[tmp.first][tmp.second]] == 1)
					{
						return false;
					}
					else
						if (color[Vert[tmp.first][tmp.second]] == 0)
							q.push(make_pair(Vert[tmp.first][tmp.second++], 0));
						else
							tmp.second++;
				}
				else
					if (tmp.second == Vert[tmp.first].size())
					{
						color[tmp.first] = 2;
						topsort.push_back(tmp.first);
						q.pop();
					}
			}
		}

	reverse(topsort.begin(), topsort.end());
	return true;
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int n, m, v, u, s;
	cin >> n >> m;

	Graph gr(n);
	vector <int> topsort;

	for (int i = 0; i < m; i++)
	{
		cin >> v >> u;
		gr.Add(v - 1, u - 1);

	}
	if (gr.Non_rec_DFS(topsort))
	{
		cout << "Yes" << endl;
		for (int i = 0; i < topsort.size(); i++)
			cout << topsort[i] + 1 << " ";
	}
	else
		cout << "No" << endl;

	fclose(stdin);
	fclose(stdout);
	return 0;
}

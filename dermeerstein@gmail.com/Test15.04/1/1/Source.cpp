#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

vector<int> vis;
vector<vector<int> > graph;

bool dfs(int v)
{
	vis[v] = 1;
	for (int i = 0; i < graph[v].size(); ++i)
	{
		if (vis[graph[v][i]] == 0)
			dfs(graph[v][i]);
		else if (vis[graph[v][i]] == 1)
		{
			cout << "NOT CORRECT";
			exit(0);
		}
	}
	vis[v] = 2;
}


int main()
{
	int d, m;
	string s;
	map<string, int> words;
	
	vector<vector<string> > f;
	cin >> d;
	graph.resize(d);
	f.resize(d);
	vis.resize(d, 0);
	map<string, int>::iterator it;
	for (int i = 0; i < d; ++i)
	{
		cin >> s;
		if ((it = words.find(s)) != words.end())
		{
			cout << "NOT CORRECT";
			return 0;
		}
		words[s] = i;
		cin >> m;
		for (int j = 0; j < m; ++j)
		{
			cin >> s;
			f[i].push_back(s);
		}
	}
	for (int i = 0; i < d; ++i)
	{
		for (int j = 0; j < f[i].size(); j++)
		{
			if (words.find(f[i][j]) != words.end())
			{
				graph[i].push_back(words[f[i][j]]);
			}
		}
	}
	for (int i = 0; i < d; ++i)
	{
		if (vis[i] == 0)
			dfs(i);
	}
	cout << "CORRECT";

	return 0;
}
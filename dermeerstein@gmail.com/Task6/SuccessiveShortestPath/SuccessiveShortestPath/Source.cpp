#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


class Assignment
{
public:
	Assignment();

private:
	static const int INF = 2e+9 + 1;
	int n;
	vector<vector<int>> cost, zcost;
	vector<vector<int>> flow;

	void Dijkstra(vector<int> &dist, vector<int> &ans);
	void ReduceCost(vector<int> &potentials);
};

void Assignment::Dijkstra(vector<int> &dist, vector<int> &ans)
{
	vector<int> pred;
	vector<bool> vis;
	dist.resize(2 * n + 2, INF);
	pred.resize(2 * n + 2, -1);
	vis.resize(2 * n + 2, 0);
	dist[0] = 0;
	while (true)
	{
		int min_ind = -1;
		for (int i = 0; i < 2 * n + 2; ++i)
		{
			if ((min_ind == - 1 || dist[i] < dist[min_ind]) && !vis[i])
			{
				min_ind = i;
			}
		}
		if (min_ind == -1)
			break;
		for (int i = 0; i < 2 * n + 2; ++i)
		{
			if (dist[min_ind] + cost[min_ind][i] < dist[i] && !vis[i] && flow[min_ind][i] > 0)
			{
				dist[i] = dist[min_ind] + cost[min_ind][i];
				pred[i] = min_ind;
			}
		}
		vis[min_ind] = 1;
	}
	
	int v = 2 * n + 1;
	ans.push_back(v);
	while (pred[v] != -1)
	{
		ans.push_back(pred[v]);
		v = pred[v];
	}
	reverse(ans.begin(), ans.end());
}

void Assignment::ReduceCost(vector<int> &potentials)
{
	for (int i = 0; i < 2 * n + 2; ++i)
	{
		for (int j = 0; j < 2 * n + 2; ++j)
		{
			if (flow[i][j] > 0)
			{
				cost[i][j] += potentials[i] - potentials[j];
				cost[j][i] = 0;
			}
		}
	}
}


Assignment::Assignment()
{
	cin >> n;
	cost.resize(2 * n + 2);
	zcost.resize(2 * n + 2);
	flow.resize(2 * n + 2);
	for (int i = 0; i < 2 * n + 2; ++i)
	{
		cost[i].resize(2 * n + 2, INF);
		zcost[i].resize(2 * n + 2, INF);
		flow[i].resize(2 * n + 2, -INF);
	}
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			cin >> cost[i + 1][n + j + 1];
			zcost[i + 1][n + j + 1] = cost[i + 1][n + j + 1];
			cost[n + j + 1][i + 1] = 0;
			flow[i + 1][n + j + 1] = 1;
			flow[n + j + 1][i + 1] = 0;
		}
	}
	for (int i = 0; i < n; ++i)
	{
		cost[0][i + 1] = 0;
		cost[i + 1][0] = 0;
		cost[n + i + 1][2 * n + 1] = 0;
		cost[2 * n + 1][n + i + 1] = 0;
		flow[0][i + 1] = 1;
		flow[i + 1][0] = 0;
		flow[n + i + 1][2 * n + 1] = 1;
		flow[2 * n + 1][n + i + 1] = 0;
	}

	vector<int> potentials, ans;

	for (int k = 0; k < n; ++k)
	{
		Dijkstra(potentials, ans);
		ReduceCost(potentials);
		for (int i = 0; i < ans.size() - 1; ++i)
		{
			flow[ans[i]][ans[i + 1]] -= 1;
			flow[ans[i + 1]][ans[i]] += 1;
		}
		potentials.clear();
		ans.clear();
	}
	int res = 0;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (flow[i + 1][n + j + 1] == 0)
			{
				cout << i + 1 << " -> " << j + 1 << endl;
				res += zcost[i + 1][n + j + 1];
			}
		}
	}
	cout << res << endl;
	return;
}

int main()
{
	Assignment();
	return 0;
}
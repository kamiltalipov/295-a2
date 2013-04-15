#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>

using namespace std;

class TGraph
{
public:
	TGraph(int sizen, int sizem): sizen(sizen), sizem(sizem)
	{
		Vert.resize(sizen, vector < bool > (sizem, 0));
		Used.resize(sizen, vector < bool > (sizem, 0));
	}

	TGraph();

	int BFS();
	bool okay(int a, int b);

//private:
	vector < vector < bool > > Vert; 
	vector < vector < bool > > Used; 
	int sizen;
	int sizem;
};

bool TGraph::okay (int a, int b)
{
	return ((a >= 0) && (a < sizem) && (b >= 0) && (b < sizen)) && (!Used[b][a]) && (Vert[b][a]);
}

int TGraph::BFS()
{
	int ans = 0;
	queue < pair < int, int > > q;
	int startx = 0, starty = 0;
	
	const int dx[4] = {0, 1, 0, -1};
	const int dy[4] = {1, 0, -1, 0};


	for ( int i = 0; i < sizen; i++ )
		for( int j = 0; j < sizem; j++ )
			if (Vert[i][j] && (!Used[i][j]))
			{
				starty = i;
				startx = j;

				q.push (make_pair (startx, starty));
				int v, u;
				while (!q.empty())
				{
					pair <int, int> tmp = q.back();
					v = tmp.first;
					u = tmp.second;
					Used[u][v] = true;
					q.pop();

					for (int k = 0; k < 4; k++)
					{
						if (okay(v + dy[k], u + dx[k]))
						{
							q.push( make_pair (v + dy[k], u + dx[k]));
						}
					}
				}

				ans++;
			}

	return ans;
}

int main()
{

	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int n, m;
	cin >> n >> m;

	TGraph Graph (n, m);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			bool x;
			cin >> x;
			Graph.Vert[i][j] = x;
		}

	cout << Graph.BFS() << endl;

	//fclose(stdin);
	//fclose(stdout);
	return 0;
}
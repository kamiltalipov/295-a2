#include <iostream>
#include <vector>
#include <utility>
#include <queue>
using namespace std;

bool ok(int a, int n)
{
	return a < n && a >=0;
}

void BFS(int n,int m, vector<vector<int>>& a, pair<int,int> pos)
{
	int d[] = {0,1,0,-1,0};
	queue<pair<int,int>> q;
	q.push(pos);
	a[pos.first][pos.second] = 2;
	while(!q.empty()){
		pos = q.front();
		q.pop();
		for (int i = 0; i < 4; ++i) {
			pair<int,int> new_pos(pos.first+d[i],pos.second+d[i+1]);
			if (ok(new_pos.first,n) && ok(new_pos.second,m)&& a[new_pos.first][new_pos.second] == 1) {
				q.push(new_pos);
				a[new_pos.first][new_pos.second] = 2;
			}
		}

	}
}

int main()
{
	int n,m;
	int res = 0;

	cin >> n >> m;
	vector<vector<int>> a(n,m);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			cin >> a[i][j];
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			if (a[i][j]==1) {
				BFS(n,m,a,make_pair(i,j));
				++res;
			}
	cout << res;
	return 0;
}
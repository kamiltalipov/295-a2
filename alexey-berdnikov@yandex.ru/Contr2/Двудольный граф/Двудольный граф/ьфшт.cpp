#include <iostream>
#include <vector>
#include <utility>
#include <queue>
using namespace std;

bool BFS(int n, vector<vector<int>>& a, int i, vector<int>& colour)
{
	int d[] = {0,1,0,-1,0};
	queue<int> q;
	q.push(i);
	colour[i] = 1;
	while(!q.empty()){
		i = q.front();
		q.pop();
		for (int j = 0; j < n; ++j) {
			if (a[i][j]) {
				if(colour[j] == colour[i]) return 0;
				if (!colour[j]) {
					q.push(j);
					colour[j] = 3-colour[i];
				}
			}
		}
	}
	return 1;
}

int main()
{
	int n;

	cin >> n;
	vector<vector<int>> a(n,n);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			cin >> a[i][j];
	vector<int> colour(n);

	for (int i = 0; i < n; ++i)
			if (!colour[i]) {
				if (!BFS(n,a,i,colour)) {
					cout << "NO";
					return 0;
				}
			}
	cout << "YES";
	return 0;
}
#include<iostream>
#include<stdio.h>
#include<vector>
#include<algorithm>
 
using namespace std;

int find(const vector<vector<int>>&MaxLine, const vector<int>& a, int var, int x, int y, int& k){
	k = -1;
	if (y == -1)
		return 0;
	int result = 0;
	
	for (int i = 0; i < x; i++){
		if (a[i] <= var && result < MaxLine[i][y]){
			result = MaxLine[i][y];
			k = i;
		}
	}
	return result;
}

void MakeLCIS(const vector<int>& a, const vector<int>& b, int n, int m){
	vector<vector<int>>MaxLen(n, m), MaxLine(n, m), Par(n, m), MinNumLen(n + 1, m);
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			int k = 0;
			if (a[i] == b[j])
				MaxLen[i][j] = 1 + find(MaxLine, a, a[i], i, j - 1, k);
			Par[i][j] = k;
			MaxLine[i][j] = MaxLen[i][j];
			if (j > 0 && MaxLine[i][j] < MaxLine[i][j - 1]){
				MaxLine[i][j] = MaxLine[i][j - 1]; 
				Par[i][j] = Par[i][j - 1];
			}
			/*if (a[MinNumLen[MaxLine[i][j]][j]] > a[i])
				MinNumLen[MaxLine[i][j]][j] = i;*/
		}
	}
	int result = 0, j = 0;
	for (int i = 0; i < n; i++){
		if (result < MaxLine[i][m - 1]){
			result = MaxLine[i][m - 1];
			j = i;
		}
	}
	cout << result << endl;
	vector<int>ans;
	int i = m - 1;
	while (j != -1){
		ans.push_back(a[j]);
		j = Par[j][i];
		i--;
	}
	for (int i = ans.size() - 1; i >= 0; i--)
		cout << ans[i] << " ";
}

int main( void ){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);

	int n, m;
	cin >> n;
	vector<int>a(n);                                                     
	for (int i = 0; i < n; i++)
		cin >> a[i];
	cin >> m;
	vector<int>b(m);
	for (int i = 0; i < n; i++)
		cin >> b[i];
	int j = 1;
	for (int i = 1; i < n; i++)
		if (a[i] != a[i - 1]){
			a[j] = a[i];
			j++;
		}
	n = j;
	j = 1;
	for (int i = 1; i < n; i++)
		if (b[i] != b[i - 1]){
			b[j] = b[i];
			j++;
		}
	m = j;

	MakeLCIS(a, b, n, m);
	return 0;
}
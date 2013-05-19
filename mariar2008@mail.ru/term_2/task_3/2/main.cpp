#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <math.h>
#include <vector>
#include <algorithm>

#define inf 100000000
using namespace std;

class table{
public:
	void Read(){
		cin >> n;
		++n;
		a.resize(n);
		for (int i = 0; i < n; ++i)
			a[i].resize(n);
			
		for (int i = 1; i < n; ++i)
			for (int j = 1; j < n; ++j){
				cin >> a[i][j];
			}
		minv.resize(n, inf);
		u.resize(n, 0);
		v.resize(n, 0);
		in.resize(n);
		used.resize(n);
	}
	void Hungarian_algorithm(){
		prev.resize(n, 0);
		for (int i = 1; i < n; ++i){
			in[0] = i;
			int cur_j = 0;
			for (int j = 0; j < n; ++j){
				minv[j] = inf;
				used[j] = false;
			}
			while (in[cur_j] > 0){
				used[cur_j] = true;
				int cur_i = in[cur_j], d = inf, j0;
				for (int k = 1; k < n; ++k)
					if (used[k] == false){
						if (a[cur_i][k] - u[cur_i] - v[k] < minv[k]){
							minv[k] = a[cur_i][k] - u[cur_i] - v[k];
							prev[k] = cur_j;
						}
						if (minv[k] < d){
							d = minv[k];
							j0 = k;
						}
					}
				for (int k = 0; k < n; ++k)
					if (used[k] == true){
						u[in[k]] += d;
						v[k] -=d;
					}
					else
						minv[k] -= d;
				cur_j = j0;
			}			
			while (cur_j > 0){
				in[cur_j] = in[prev[cur_j]];
				cur_j = prev[cur_j];
			} 
		}
		int ans = 0;
		for (int i = 1; i < n; ++i)
			ans += a[in[i]][i];
		cout << ans;
	}
private:
	vector<int> prev;
	int n;
	vector<vector<int> > a;
	vector<int> minv;
	vector<int> u;
	vector<int> v;
	vector<int> in;
	vector<bool> used;
};

int main(){
	table my_table;
	my_table.Read();
	my_table.Hungarian_algorithm();
	return 0;
}

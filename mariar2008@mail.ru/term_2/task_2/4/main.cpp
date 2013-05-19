#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <sys/time.h>
#include <math.h>
#include <vector>
#include <algorithm>

#define N 100
#define M 100
#define S1 100
#define S2 10
#define inf 1000000000

using namespace std;

class graph{
public:
	void Solve(){
		for (int i = 0; i < N; ++i){
			double x0, y0;
			Generation(S1, 0, 0, x0, y0);
			for (int j = 0; j < M; ++j){
				double cur_x, cur_y;
				Generation(S2, x0, y0, cur_x, cur_y);
				x.push_back(cur_x);
				y.push_back(cur_y);
			}
		}
		for (int i = 0; i < x.size(); ++i)
			cout << x[i] << " " << y[i] << endl; 
		Prima();
		sort(skeleton.begin(), skeleton.end());
		for (int i = 0; i < size; ++i)
			used[i] = false;
		begin.resize(size);
		for (int i = 0; i < skeleton.size(); ++i)
				begin[skeleton[i].first] = i;
		for (int i = 0; i < skeleton.size(); ++i)
			cout << skeleton[i].first << " " << skeleton[i].second << endl;
		
		dfs(0);
		cout << 0;
	}
	bool sort_function(pair<int, int> one, pair<int, int> two){
		if (one.first == two.first)
			return (one.second < two.second);
		else
			return (one.first < two.first);
	}
private:
	int size;
	vector<double> x;
	vector<double> y;
	vector<bool> used;
	vector<pair<double, int> > min;
	vector<pair<int, int> > skeleton;
	vector<int> begin;
	void dfs(int v){
		//cout << "dfs" << endl;
		cout << v << " ";
		used[v] = true;
		int i = begin[v];
		while (i >= 0 && skeleton[i].first == v){
			int u = skeleton[i].second;
			if (!used[u])
				dfs(u);
			--i;
		}
	}
	
	double dist(int one, int two){
		return sqrt((x[one] - x[two])*(x[one] - x[two]) + (y[one] - y[two])*(y[one] - y[two]));
	}
	
	void Prima(){
		size = x.size();
		used.resize(size);
		min.resize(size);
		used[0] = true;
		pair<double, int> current;
		for (int i = 1; i < size; ++i){
			current.first = dist(i, 0);
			current.second = 0;
			min[i] = current;
		}
		//cout << "ololo"<<endl;
		for (int i = 1; i < size; ++i){
			pair<double, int>cur_min(inf, -1);
			int num = -1;
			for (int j = 0; j < size; ++j)
				if (used[j] == false && cur_min.first > min[j].first){
					cur_min = min[j];
					num = j;
				}
			used[num] = true;
			pair<int, int> edge(num, cur_min.second);
			skeleton.push_back(edge);
			edge.first = cur_min.second;
			edge.second = num;
			skeleton.push_back(edge);
			for (int j = 0; j < size; ++j){
				//cout << min[j].first << " " << dist(j, num) << endl;
				if (used[j] == false && min[j].first > dist(j, num)){
					min[j].first = dist(j, num);
					min[j].second = num;
				}
			}
		}
	}
	void Generation(int sigma, double x0, double y0, double &x, double &y){
		struct timeval time;
		srand(time.tv_sec*1000 + time.tv_usec);
		while (true){
			double first = ((double)2*(double)rand()/(double)RAND_MAX) - 1;
			double second = ((double)2*(double)rand()/(double)RAND_MAX) - 1;
			double s = first*first + second*second;
			if (s > 0 && s <= 1){
				double t = sqrt(-2*log(s)/s);
				x = first*t*(double)sigma + x0;
				y = second*t*(double)sigma + y0;
				return;
			}
		}
	}
};

int main(){
	graph my_graph;
	my_graph.Solve();
	return 0;
}

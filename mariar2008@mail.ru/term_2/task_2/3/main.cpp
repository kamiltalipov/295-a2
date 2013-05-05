#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <vector>

#define INF 1000000000
using namespace std;

class graph{
private:
	struct my_edge{
		my_edge(int first, int second, int third){
			begin = first;
			end = second;
			coast = third;
		}
		int begin, end, coast;
	};

	int n, m;
	vector<my_edge> edge;
	vector<vector<int> > dist;
public:
	graph(){}
	~graph(){}
	void Read(){
		cin >> n >> m;
		for (int i = 0; i < m; ++i){
			int u, v, coast;
			cin >> u >> v >> coast;
			my_edge current_edge(u, v, coast);
			edge.push_back(current_edge);
		}
	}
	
	void Ford_Bellman(){
		dist.resize(n + 1);
		for (int i = 0; i < n; ++i)
			dist[i].resize(n + 1, INF);
		dist[0][0] = 0;
		for (int i = 1; i <= n; ++i){
			for (int j = 0; j < m; ++j){
				int u = edge[j].begin, v = edge[j].end, coast = edge[j].coast;
				if (dist[v][i] > dist[u][i - 1] + coast){
					dist[v][i] = dist[u][i - 1] + coast;
					//cout << i << " " << u << " " << v << " " << coast << " " << dist[v][i] << endl;
				}
			}
		}
	}
	void Solve(){
		double result = INF;
		for (int v = 0; v < n; ++v){
			double value = 0;
			for (int i = 0; i < n; ++i)
				if (dist[v][n] > dist[v][i] && dist[v][n] < INF && dist[v][i] < INF){
					double cur_val = ((double)dist[v][n] - (double)dist[v][i])/((double)n - (double)i);
					if (value < cur_val)
						value = cur_val;
				}
			if (result > value && value != 0)
				result = value;
		}
		if (result < INF)
			cout << result << endl;
		else
			cout << -1;
	}
};

int main(){
	graph my_graph;
	my_graph.Read();
	my_graph.Ford_Bellman();
	my_graph.Solve();
	//cout << "ololo" << endl;
	return 0;
}

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;

class graph{
public:
	void Read(){
		cin >> n;
		string name;
		string kub;
		cin >> name;
		m = name.length();
		edge.resize(m + n);
		used.resize(n + m);
		in.resize(n + m);
		for (int i = 0; i < n; ++i){
			cin >> kub;
			//cout << kub << endl;
			for (int j = 0; j < 6; ++j)
				for (int v = 0; v < m; ++v)
					if (name[v] == kub[j]){
						//cout << kub[j] << " " << name[v] << endl; 
						edge[v].push_back(m + i);
					}
		}
		/*for (int i = 0; i < m; ++i){
			for (int j = 0; j < edge[i].size(); ++j)
				cout << edge[i][j] << " ";
			cout << endl;
		}*/
		//cout << "Success\n";
	}
	
	void Solve(){
		//cout << "in solve \n";
		for (int i = 0; i < m + n; ++i){
			in[i] = -1;
		}
		for (int i = 0; i < m; ++i){
			//cout << i << endl;
	
			for (int j = 0; j < n + m; ++j)
				used[j] = false;
				
			//cout << i << endl;
			kun(i);
		}
	}
	void Write(){
		vector<int> answer;
		for (int i = 0; i < m; ++i){
			bool find = false;
			for (int j = m; j < n + m; ++j)
				if (in[j] == i){
					answer.push_back(j - m + 1);
					find = true;
					break;
				}
			if (!find){
				cout << "NO\n";
				exit(0);
			}
		}
		cout << "YES\n";
		for (int i = 0; i < answer.size(); ++i)
			cout << answer[i] << " ";
		
	}
private:
	int n, m;
	vector<vector<int> > edge;
	vector<bool> used;
	vector<int> in;
	bool kun(int v){
		
		if (!used[v]){
			//cout << v << endl;
			used[v] = true;
			for (int i = 0; i < edge[v].size(); ++i){
				int u = edge[v][i];
				//cout << v << " " << u << " " << in[u] << endl;
				if (in[u] == -1 || kun(in[u])){
					in[u] = v;
					return true;
				}
			}
				
		}
		return false;
	}
};

int main(){
	graph my_graph;
	my_graph.Read();
	my_graph.Solve();
	my_graph.Write();
	return 0;
}

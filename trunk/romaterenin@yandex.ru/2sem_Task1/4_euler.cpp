#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>
using namespace std;
class Euler{
public:
	int n,m;
	vector <vector <int> > g;
	vector <int> ans;
	vector <int> ind;
	vector<int> deg_in,deg_out;
	Euler () {}

	void read(){
		cin>>n>>m;
		g.resize(n);
		deg_in.resize(n,0);
		deg_out.resize(n,0);
		ind.resize(n,0);
		for(int i=0;i<m;i++){
			int v1,v2;
			cin>>v1>>v2;
			deg_in[v2-1]++;
			deg_out[v1-1]++;
			g[v1-1].push_back(v2-1);
		}
	}

	void check(){
		for (int i=0; i<n; ++i)
			if(deg_in[i]!=deg_out[i]){
				cout<<"There isn't Euler cycle."<<endl;
				exit(0);
			}
	}

	void searchEC(int v){
		if(ind[v]<g[v].size()){
			ind[v]++;
			searchEC(g[v][ind[v]-1]);
		}
		ans.push_back(v);
	}

	void printf(){
		reverse(ans.begin(),ans.end());
		for (int i=0; i<ans.size(); i++)
			cout<<ans[i]+1<<" ";
	}
};
int main(){
	freopen("TextFile2.txt", "r", stdin);
	Euler a;
	a.read();
	a.check();
	a.searchEC(0);
	a.printf();
	return 0;
}
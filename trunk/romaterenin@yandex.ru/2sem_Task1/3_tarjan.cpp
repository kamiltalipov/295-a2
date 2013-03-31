#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Tarjan{
public:
	int n;
	int m;
	int dfs_timer;
	vector < vector <int> > g;
	vector <bool> used, for_st;
	vector <int> deg_in, deg_out, up;
	stack <int> st;
	Tarjan () {dfs_timer=0;}

	void read(){
		cin>>n>>m;
		g.resize(n);
		used.resize(n,false);
		for_st.resize(n,false);
		deg_in.resize(n);
		deg_out.resize(n);
		up.resize(n);
		for(int i=0; i<m; i++){
			int v1,v2;
			cin>>v1>>v2;
			g[v1-1].push_back(v2-1);
		}
	}

	void dfs(int v){
		st.push(v);
		used[v]=true;
		for_st[v]=true;
		deg_in[v]=dfs_timer++;
		up[v]=deg_in[v];
		for(int i=0; i<g[v].size(); i++)
			if(!used[g[v][i]]){
				dfs(g[v][i]);
				up[v]=min(up[v], up[g[v][i]]);
			}
			else
				if(for_st[g[v][i]])
					up[v]=min(up[v], deg_in[g[v][i]]);
		if(up[v]==deg_in[v]){
			while(st.top()!=v){
				cout<<st.top()+1<<" ";
				for_st[st.top()]=false;
				st.pop();
			}
			cout<<v+1<<endl;
			st.pop();
		}
	}

	void go(){
		for(int i=0; i<n; ++i)
			if(!used[i])
				dfs(i);
	}

};

int main(){
	freopen("TextFile2.txt","r",stdin);
	Tarjan a;
	a.read();
	a.go();
	return 0;
}
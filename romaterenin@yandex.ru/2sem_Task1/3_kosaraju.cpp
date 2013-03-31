#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>
using namespace std;
class Kosaraju{
public:
	int n,m;
	vector <vector <int> > g,p,comp;
	vector <int> prom,ans,ind;
	vector <bool> used;

	void read(){
		cin>>n>>m;
		g.resize(n);
		p.resize(n);
		used.resize(n,false);
		for(int i=0; i<m; i++){
			int v1, v2;
			cin>>v1>>v2;
			g[v1-1].push_back(v2-1);
			p[v2-1].push_back(v1-1);
		}
		
	}

	void dfsg(int v){
		used[v]=true;
		for(int i=0; i<g[v].size(); i++)
			if(!used[g[v][i]])
				dfsg(g[v][i]);
		prom.push_back(v);
	}

	void dfsp(int v){
		used[v]=true;
		comp[comp.size()-1].push_back(v);
		for(int i=0; i<p[v].size(); i++)
			if(!used[p[v][i]])
				dfsp(p[v][i]);
	}

	void bypass_g(){
		for(int i=0; i<n; ++i)
			if(!used[i])
				dfsg(i);
	}

	void bypass_p(){
		used.assign(n,false);
		for(int i=n-1; i>=0; i--)
			if(!used[prom[i]]){
				comp.resize(comp.size()+1);
				dfsp(prom[i]);
			}

	}

	void printf(){
		for(int i=0; i<comp.size(); i++){
			for(int j=0; j<comp[i].size(); ++j)
				cout<<comp[i][j]+1<<" ";
			cout<<endl;
			}
	}
};
int main(){
	freopen("TextFile2.txt","r",stdin);
	Kosaraju a;
	a.read();
	a.bypass_g();
	a.bypass_p();
	a.printf();
	return 0;
}
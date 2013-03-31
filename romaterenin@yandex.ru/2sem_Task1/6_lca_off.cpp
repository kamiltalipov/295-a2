#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;

class DSU{
public:
	vector <int> parent;
	vector <int> rank;
	vector <int> ancestor;
	DSU(int n) {
		parent.resize(n);
		rank.resize(n);
		ancestor.resize(n);
		for(int i=0;i<n;i++)
			make_set(i);
	}
	void make_set(int v){
		rank[v]=1;
		parent[v]=v;
		ancestor[v]=v;
	}
	int root(int v){
		if(parent[v]==v)
			return v;
		return parent[v]=root(parent[v]);
	}

	void unite(int v1,int v2, int new_ancestor){
		v1=root(v1);
		v2=root(v2);
		if(v1!=v2){
			if(rank[v1]<rank[v2])
				swap(v1,v2);
			parent[v2]=v1;
			rank[v1]+=v2;
			ancestor[v1]=new_ancestor;
		}
	}
};

void dfs(int v, vector <vector<int> > &g, vector <vector<int> > &req,vector <bool> used, DSU &a){
	a.make_set(v);
	used[v]=1;
	for(int i=0;i<g[v].size();i++)
		if(!used[g[v][i]]){
			dfs(g[v][i], g, req, used, a);
			a.unite(v, g[v][i], v);
		}
	for(int i=0;i<req[v].size();i++)
		if(used[req[v][i]] && v != a.ancestor[a.root(req[v][i])])
			cout<<"LCA "<<v+1<<" and "<<req[v][i]+1<<" is "<<a.ancestor[a.root(req[v][i])]+1<<endl;
	
}

int main(){
	//freopen("TextFile2.txt","r",stdin);
	int n;
	cin>>n;
	vector <vector<int> > g(n);
	vector <bool> used(n,false);
	DSU a(n);
	for(int i=0;i<n-1;i++){
		int v1,v2;
		cin>>v1>>v2;
		g[v1-1].push_back(v2-1);
		g[v2-1].push_back(v1-1);
	}
	int kol_req;
	cin>>kol_req;
	vector <vector<int> > req(n);
	for(int i=0;i<kol_req;i++){
		int v1,v2;
		cin>>v1>>v2;
		req[v1-1].push_back(v2-1);
		req[v2-1].push_back(v1-1);
	}
	dfs(0,g,req, used,a);
	return 0;
}
#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;

class DSU{
public:
	vector <int> parent;
	vector <int> rank;
	DSU(int n) {
		parent.resize(n);
		rank.resize(n);
		for(int i=0;i<n;i++)
			make_set(i);
	}

	void make_set(int v){
		rank[v]=1;
		parent[v]=v;
	}
	int root(int v){
		if(parent[v]==v)
			return v;
		return parent[v]=root(parent[v]);
	}

	void unite(int v1,int v2{
		v1=root(v1);
		v2=root(v2);
		if(v1!=v2){
			if(rank[v1]<rank[v2])
				swap(v1,v2);
			parent[v2]=v1;
			rank[v1]+=v2;
		}
	}

};
int main(){
	//freopen("TextFile2.txt","r",stdin);
	int n,m;
	cin>>n>>m;
	DSU a(n);
	for(int i=0;i<m;i++){
		int v1,v2;
		string s;
		cin>>s>>v1>>v2;
		if(s=="add")
			a.unite(v1-1,v2-1);
		else // s==check
			if(a.root(v1-1)!=a.root(v2-1))
				cout<<"No"<<endl;
			else
				cout<<"Yes"<<endl;
	}
	return 0;
}
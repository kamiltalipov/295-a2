#include<iostream>
#include<vector>
using namespace std;

class Tree_Segments{
public:
	vector < pair <int,int> > tree;
	Tree_Segments (int n)
	{
		tree.resize(4*n);
	}

	void build_for_min (vector <int> &Array, int v, int tl, int tr){
		if(tl==tr){
			tree[v].first=Array[tl];
			tree[v].second=0;
		}
		else{
			int tm=(tl+tr)/2;
			build_for_min(Array,2*v,tl,tm);
			build_for_min(Array,2*v+1,tm+1,tr);
			tree[v].first=min(tree[2*v].first,tree[2*v+1].first);
			tree[v].second=0;
		}
	}

	void push (int v){
		tree[2*v].second+=tree[v].second;
		tree[2*v+1].second+=tree[v].second;
		tree[v].first+=tree[v].second;
		tree[v].second=0;
	}

	void update_for_min (int v, int tl, int tr, int l, int r, int add){
		push(v);
		if(l>r)
			return;
		if(tl==l && r==tr)
			tree[v].second+=add;
		else{
			int tm=(tl+tr)/2;
			update_for_min(2*v, tl, tm, l, min(r,tm) , add);
			update_for_min(2*v+1,tm+1,tr, max(l,tm+1), r, add);
			tree[v].first=min(tree[2*v].first+tree[2*v].second,tree[2*v+1].first+tree[2*v+1].second);
		}
	}
	
	int min_element (int v, int tl, int tr, int l, int r){
		push(v);
		if(l>r)
			return numeric_limits<int>::max();
		if(l==tl && r==tr)
			return tree[v].first;
		int tm=(tl+tr)/2;
		return min( min_element (2*v, tl, tm, l, min(r,tm)) , min_element (2*v+1, tm+1, tr, max(tm+1,l), r));
	}
};
int main(){
	int n;
	cin>>n;
	vector <int> a(n);
	Tree_Segments tree(n);
	for(int i=0; i<n; ++i)
		cin>>a[i];
	tree.build_for_min(a, 1, 0, n-1);
	int m;
	cin>>m;
	for(int i=0; i<m; ++i)
	{
		int operation;
		cin>>operation;
		if(operation==0)
		{
			int l, r;
			cin>>l>>r;
			cout<<tree.min_element(1, 0, n-1, l-1, r-1)<<endl;
		}
		else
		{
			int l, r, add;
			cin>>l>>r>>add;
			tree.update_for_min(1, 0, n-1, l-1, r-1, add);
		}
	}
	return 0;
}
#include<iostream>
#include<vector>
using namespace std;

class Fenwick_tree{
public:
	vector <int> tree;
	int size;
	Fenwick_tree (int n)
	{
		tree.assign(n,0);
		size=n;
	}
	int f(int x){
		return x & (x+1);
	}
	int sum(int r){
		int result=0;
		while(r>=0){
			result+=tree[r];
			r=f(r) - 1;
		}
		return result;
	}
	void update (int i, int delta){
		for( ; i < size ; i= i | (i+1))
			tree[i]+=delta;
	}
	int sum (int l, int r){
		return sum(r) - sum(l-1);
	}
};

int main(){
	int n;
	cin>>n;
	vector <int> a(n);
	Fenwick_tree tree(n);
	for(int i=0; i<n; ++i)
	{
		cin>>a[i];
		tree.update(i, a[i]);
	}
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
			cout<<tree.sum(l-1, r-1)<<endl;
		}
		else
		{
			int x, delta;
			cin>>x>>delta;
			tree.update(x-1, delta);
		}
	}
	return 0;
}
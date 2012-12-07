#include<iostream>
#include<vector>

using namespace std;

class FenwickTree
{
public:
	vector<int> tree;
	FenwickTree(vector<int> &a);
	FenwickTree(int n);
	int sum(int r);
	int sum(int l,int r);
	void add(int i,int x);
};


FenwickTree::FenwickTree(vector<int> &a)
{
	tree.assign(a.size(),0);
	for(int i=0;i<a.size();i++)
		add(i,a[i]);
}
FenwickTree::FenwickTree(int n)
{
	tree.assign(n,0);
}

int FenwickTree::sum(int r)
{
	int result=0;
	while(r>=0)
	{
		result+=tree[r];
		r =(r&(r+1))-1;
	}
	/*for (; r >= 0; r = (r & (r+1)) - 1)
		result+=tree[r];*/
	return result;
}

void FenwickTree::add(int i, int x)
{
	while(i<tree.size())
	{
		tree[i]+=x;
		i=(i|(i+1));
	}
	/*for (; i < n; i = (i | (i+1)))
		tree[i]+=x;*/
}

int FenwickTree::sum (int l, int r)
{
	return sum(r)-sum(l-1);
}

int main()
{
	int n,ans=0;
	cin>>n;
	vector<int> a(n);
	FenwickTree T(n);
	for(int i=0;i<n;i++)
	{
		cin>>a[i];
		T.add(a[i]-1,1);
		ans+=T.sum(a[i],n-1);
	}
	cout<<ans;
	/*FenwickTree T(a);
	int m,l,r;
	cin>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>l>>r;
		cout<<T.sum(l-1,r-1)<<endl;
	}*/

	return 0;
}
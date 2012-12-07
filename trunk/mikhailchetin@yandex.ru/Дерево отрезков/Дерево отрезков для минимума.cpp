#include<iostream>
#include<vector>

using namespace std;

struct node
{
	int value;
	int toadd;
};

class SegmentTree
{
public:
	vector<node> tree;
	SegmentTree(vector<int> &a);
	void build(vector<int> &a,int v,int tl,int tr);
	int minimum(int v, int tl, int tr, int l, int r);
	void push(int v,int l,int r);
	void add(int v,int l,int r,int i,int j,int x);
	void print();
};

SegmentTree::SegmentTree(vector<int> &a)
{
	tree.resize(5*a.size());
	build(a,1,0,a.size()-1);
}

void SegmentTree::push(int v,int l,int r)
{
	tree[v].value+=tree[v].toadd;
	tree[2*v].toadd+=tree[v].toadd;
	tree[2*v+1].toadd+=tree[v].toadd;
	tree[v].toadd=0;
}

void SegmentTree::build (vector<int> &a, int v, int l, int r) 
{
	if (l == r)
	{
		tree[v].value = a[l];
		tree[v].toadd=0;
	}
	else 
	{
		int m=(l+r)/2;
		build(a,v*2,l,m);
		build(a,v*2+1,m+1,r);
		tree[v].value=min(tree[v*2].value,tree[v*2+1].value);
		tree[v].toadd=0;
	}
}

int SegmentTree::minimum (int v,  int l, int r,int i, int j)
{
	push(v,l,r);
	if(j<l || r<i)
		return INT_MAX;
	if(i<=l && r<=j)
		return tree[v].value;
	int m=(l+r)>>1;
	return min(minimum(2*v,l,m,i,j),minimum(2*v+1,m+1,r,i,j));
}

void SegmentTree::add(int v,int l,int r,int i,int j,int x)
{
	push(v,l,r);
	if(j<l || r<i)
		return;
	if(i<=l && r<=j)
	{
		tree[v].toadd+=x;
		return;
	}
	int m=(l+r)>>1;
	add(2*v,l,m,i,j,x);
	add(2*v+1,m+1,r,i,j,x);
	tree[v].value=min((tree[2*v].value+tree[2*v].toadd),(tree[2*v+1].value+tree[2*v+1].toadd));
}
void SegmentTree::print()
{
	for(int i=1;i<tree.size();i++)
		cout<<tree[i].value<<','<<tree[i].toadd<<' ';
}

int main()
{
	int n;
	cin>>n;
	vector<int> a(n);
	for(int i=0;i<n;i++)
		cin>>a[i];
	SegmentTree T(a);
	
	int m,l,r,x;
	bool query;

	cin>>m;
	
	for(int i=1;i<=m;i++)
	{
		cin>>query>>l>>r;
		if(query)
		{
			cout<<T.minimum(1,0,n-1,l-1,r-1)<<endl;
			T.print();
		}
		else
		{
			cin>>x;
			T.add(1,0,n-1,l-1,r-1,x);
			T.print();
		}
	}
	return 0;
}
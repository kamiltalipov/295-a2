#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

typedef pair<string,int> query;

class heap
{
public:
	vector<int> a;
	int size;
	void build();
	void siftdown(int i);
	void siftup(int i);
	void heapsort();
	void add(int x);
	void removemax();
	void print();
};
void heap::siftdown(int i)
{
	int l=2*i;
	int r=2*i+1;
	int m=i;
	if(l<=size && a[l]>a[m])
		m=l;
	if(r<=size && a[r]>a[m])
		m=r;
	if(m!=i) 
	{
		swap(a[m],a[i]);
		siftdown(m);
	}
}
void heap::siftup(int i)
{
	if(a[i]>a[i/2] && i!=1)
	{
		swap(a[i],a[i/2]);
		siftup(i/2);
	}
}
void heap::add(int x)
{
	size++;
	a.resize(size+1);
	a[size]=x;
	siftup(size);
}
void heap::removemax()
{
	swap(a[1],a[size]);
	size--;
	a.resize(size+1);
	siftdown(1);
}
void heap::build()
{
	for(int i=size/2;i>=1;i--)
		siftdown(i);
}


class SegmentTree
{
public:
	vector<int> tree;
	SegmentTree(vector<int> &a);
	void build(vector<int> &a,int v,int tl,int tr);
	int minimum(int v, int tl, int tr, int l, int r);
};
SegmentTree::SegmentTree(vector<int> &a)
{
	tree.resize(5*a.size());
	build(a,1,0,a.size()-1);
}
void SegmentTree::build (vector<int> &a, int v, int l, int r) 
{
	if (l == r)
		tree[v] = a[l];
	else 
	{
		int m=(l+r)/2;
		build(a,v*2,l,m);
		build(a,v*2+1,m+1,r);
		tree[v]=min(tree[v*2],tree[v*2+1]);
		
	}
}
int SegmentTree::minimum (int v,  int l, int r,int i, int j)
{
	if(j<l || r<i)
		return INT_MAX;
	if(i<=l && r<=j)
		return tree[v];
	int m=(l+r)>>1;
	return min(minimum(2*v,l,m,i,j),minimum(2*v+1,m+1,r,i,j));
}


class Search
{
	vector<query> *buffer;
	Search(vector<query> &a);
};

Search::Search(vector<query> &a)
{
	buffer=&a;
}
bool stringcompare(query s1,query s2)
{
	for(int i=0;i<min(s1.first.length(),s2.first.length());i++)
	{
		if(s1.first[i]<s2.first[i]) return true;
		if(s1.first[i]>s2.first[i]) return false;
	}
	return s1.first.length()<s2.first.length();
}

int main()
{
	vector<query> s;
	string a;
	int k;
	string prefix;
	cin>>prefix>>k;
	int i=0;
	freopen("dictionary.txt","r",stdin);
	while(cin>>a)
		s.push_back(make_pair(a,i++));

	sort(s.begin(),s.end(),stringcompare);
	
	
	//prefix="аба";
	
	vector<query>::iterator it,low,up;
	low=lower_bound(s.begin(),s.end(),make_pair(prefix,0),stringcompare);
	prefix[prefix.length()-1]++;
	up=upper_bound(s.begin(),s.end(),make_pair(prefix,0),stringcompare);
	vector<int> frequency;
	for(it=low;it<up;it++)
		frequency.push_back(it->second);
	n=frequence.size();
	SegmentTree T(frequency);
	heap H;
	H.size=0;
	return 0;
}
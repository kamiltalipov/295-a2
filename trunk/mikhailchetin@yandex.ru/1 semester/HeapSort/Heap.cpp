#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

class heap
{
public:
	vector<int> a;
	int size;
	void build();
	void siftdown(int i);
	void siftup(int i);
	void heapsort();

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

void heap::build()
{
	for(int i=size/2;i>=1;i--)
		siftdown(i);
}
void heap::heapsort()
{
	int size1=size;
	for(int i=size1;i>=1;i--)
	{
		swap(a[i],a[1]);
		size--;
		siftdown(1);
	}
}
int main()
{
	heap H;
	

	int n;
	cin>>n;
	int n1=n;

	H.a.resize(n+1);

	for(int i=1;i<=n;i++)
		cin>>H.a[i];
	H.size=n;
	H.build();
	H.heapsort();
	for(int i=1;i<=n1;i++)
		cout<<H.a[i]<<' ';
	return 0;
}
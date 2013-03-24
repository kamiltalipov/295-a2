#include<iostream>
#include<vector>

using namespace std;

void merge(int l1, int r1, int l2,int r2, vector<int> &a,vector<int> &b,int &inv)
{
	for(int i=l1;i<=r1;i++)
		b[i]=a[i];

	b[r1+1]=1<<32-2;

	for(int i=l2+1;i<=r2+1;i++)
		b[i]=a[i-1];

	b[r2+2]=1<<32-2;

	int p=l1;
	int q=l2+1;

	for(int i=l1;i<=r2;i++)
		if(b[q]<b[p])
		{
			a[i]=b[q];
			q++;
			inv+=r1-p+1;
		}
		else
		{
			a[i]=b[p];
			p++;
		}
}

void mergeSort(int l,int r, vector<int> &a, vector<int> &b, int &inv)
{
	int m=(l+r)/2;
	if(l!=m) mergeSort(l,m,a,b,inv);
	if(m+1!=r) mergeSort(m+1,r,a,b,inv);

	if(l!=r) merge(l,m,m+1,r,a,b,inv);
}

int main()
{
	int n,inv=0;
	cin>>n;

	vector<int> a(n+1),b(n+3);

	for(int i=1;i<=n;i++)
		cin>>a[i];

	int k=0;

	for(int i=1;i<n;i++)
		for(int j=i+1;j<=n;j++)
			if(a[i]>a[j])
				k++;

	mergeSort(1,n,a,b,inv);

	for(int i=1;i<=n;i++)
		cout<<a[i]<<' ';
	
	cout<<endl<<inv<<endl<<k;
	
	return 0;
}
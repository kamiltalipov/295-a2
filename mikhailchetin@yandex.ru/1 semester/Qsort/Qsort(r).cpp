#include<iostream>
#include<vector>

using namespace std;

void Qsort(int l,int r,vector<int> &a)
{
	int m=(l+r)/2;
	int i=l;
	int j=r;
	while(j>=i)
	{
		while(a[i]<a[m]) i++;
		while(a[j]>a[m]) j--;
		if(i<=j)
		{
			int rab=a[i];
			a[i]=a[j];
			a[j]=rab;
			i++;
			j--;
		}
	}
	if(l<j) Qsort(l,j,a);
	if(i<r) Qsort(i,r,a);
}
int main()
{
	int n;
	cin>>n;
	vector<int> a(n+1);
	for(int i=1;i<=n;i++)
		cin>>a[i];
	Qsort(1,n,a);
	for(int i=1;i<=n;i++) cout<<a[i]<<' ';
	return 0;
}
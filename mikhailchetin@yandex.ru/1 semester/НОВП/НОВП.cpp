#include <cstdio>
#include<iostream>
#include<vector>
using namespace std;

int main()
{
	int n,m,i,j,k;
	cin>>n;
	vector<int> a(n+1);
	for (i=1;i<=n;i++) cin>>a[i];
	cin>>m;
	vector<int> b(m+1),d(m+1),previous(m+1),ans(m+1);
	for (i=1;i<=m;i++) cin>>b[i];


	for (i=1;i<=n;i++)
	{
		k=0;
		for (j=1;j<=m;j++)
			if (a[i]==b[j] && d[k]+1>d[j]) 
			{
				d[j]=d[k]+1;
				previous[j]=k;
			}
			else
				if (b[j]<a[i] && d[j]>d[k]) 
					k=j;
	}

	k=0;
	j=0;
	for (i=1;i<=m;i++)
		if (d[i]>d[j]) j=i;
	for (i=j; i!=0; i=previous[i])
	{
		k++;
		ans[k]=b[i];
	}

	cout<<k;
	cout<<endl;
	for(i=k;i>=1;i--) cout<<ans[i]<<' ';
	//cin>>n;
	return 0;
}
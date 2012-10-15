#include<iostream>
#include<stack>

using namespace std;

int main()
{
	int n;
	cin>>n;
	int *a=new int[n+1];
	stack<pair<int,int>> st;
	st.push(make_pair(1,n));

	for(int i=1;i<=n;i++)
		cin>>a[i];

	while(!st.empty())
	{
		int l=st.top().first;
		int r=st.top().second;
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
		st.pop();
		if(l<j) st.push(make_pair(l,j));
		if(i<r) st.push(make_pair(i,r));
	}
	for(int i=1;i<=n;i++) cout<<a[i]<<' ';
	return 0;
}
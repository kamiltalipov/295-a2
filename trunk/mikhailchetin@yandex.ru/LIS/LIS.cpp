#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int main()
{
	int length=0;
	int n;
	cin>>n;
	vector<int> a(n+1);
	vector<int> d(n+1);
	vector<int> pos(n+1);
	vector<int> previous(n+1);

	previous[0]=-1;

	for(int i=0;i<n;i++)
		cin>>a[i];

	d[0]=-INT_MAX;
	for(int i=1;i<=n;i++) 
		d[i]=INT_MAX;

	for(int i=0;i<n;i++)
	{
		int j=int(upper_bound(d.begin(),d.begin()+n+1,a[i])-d.begin());
		if(d[j-1]<a[i] && a[i]<d[j])
		{	
			d[j]=a[i];
			pos[j]=i;
			previous[i]=pos[j-1];
			length=max(length,j);
		}
	}

	vector<int> ans;

	ans.push_back(a[pos[length]]);

	for(int i=pos[length];i!=0;i=previous[i])
		ans.push_back(a[previous[i]]);

	for(int i=length-1;i>=0;i--)
		cout<<ans[i]<<' ';

	//cin>>n;

	return 0;
}
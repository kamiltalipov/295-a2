#include<iostream>
#include<vector>

using namespace std;

int main()
{
	int n,cycle_begin=-1;
	double x;
	cin>>n;
	vector<int> p(n);
	vector<vector<double>> g(n);
	vector<double> d(n);
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			cin>>x;
			g[i].push_back(x);
		}
	}

	for(int i=0;i<n;i++)
		d[i]=0;
	d[0]=1;

	for(int k=0;k<n;k++)
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				if(d[j]<d[i]*g[i][j])
				{
					d[j]=d[i]*g[i][j];
					p[j]=i;
				}
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			if(d[j]<d[i]*g[i][j])
				{
					cycle_begin=j;
					break;
				}

	if(cycle_begin!=-1)
	{
		for(int i=0;i<n;i++)
			cycle_begin=p[cycle_begin];
		cout<<cycle_begin+1<<' ';
		for(int i=p[cycle_begin];i!=cycle_begin;i=p[i])
			cout<<i+1<<' ';
	}
	else
		cout<<"No halyava";
	return 0;
}
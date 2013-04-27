#include<iostream>
#include<vector>

using namespace std;

void print(vector<vector<int>> &p,int s,int t)
{
	if(p[s][t]==s)
	{
		if(s!=t)
			cout<<s+1<<' '<<t+1<<' ';
		return;
	}
	print(p,s,p[s][t]);
	print(p,p[s][t],t);
}

int main()
{
	int n;
	double x;
	cin>>n;
	vector<vector<double>> g(n);
	vector<vector<int>> p(n);
	for(int i=0;i<n;i++)
	{
		p[i].resize(n);
		for(int j=0;j<n;j++)
		{
			cin>>x;
			g[i].push_back(x);
			p[i][j]=i;
		}
	}
	for(int k=0;k<n;k++)
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				if(g[i][j]<g[i][k]*g[k][j])
				{
					g[i][j]=g[i][k]*g[k][j];
					if(i!=k && j!=k)
						p[i][j]=k;
				}

	for(int i=0;i<n;i++)
	{
		if(g[i][i]>1)
		{
			print(p,i,i);
			return 0;
		}
	}
	cout<<"No halyava";
	return 0;
}
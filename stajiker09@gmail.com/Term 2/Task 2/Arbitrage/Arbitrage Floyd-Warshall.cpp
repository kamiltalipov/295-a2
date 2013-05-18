#include <iostream>
#include <vector>
using namespace std;
void print_path(int v1, int v2, vector < vector <int> > &parent)
{
	if(parent[v1][v2]!=v1&&parent[v1][v2]!=v2)
	{
		print_path(v1, parent[v1][v2], parent);
		cout<<parent[v1][v2]+1<<' ';
		print_path(parent[v1][v2], v2, parent);
	}
}
int main()
{
	int n;
	cin>>n;
	vector < vector <double> > exchange_rate(n);
	vector < vector <int> > parent(n);
	for(int i=0; i<n; ++i)
	{
		exchange_rate[i].resize(n);
		parent[i].resize(n);
		for(int j=0; j<n; ++j)
		{
			cin>>exchange_rate[i][j];
			parent[i][j]=j;
		}
		if(exchange_rate[i][i]>1)
		{
			cout<<"YES\n"<<i+1<<' '<<i+1;
			return 0;
		}
	}
	bool check=false;
	for(int k=0; k<n; ++k)
	{
		for(int i=0; i<n; ++i)
		{
			for(int j=0; j<n; ++j)
				if(exchange_rate[i][j]<exchange_rate[i][k]*exchange_rate[k][j])
				{
					exchange_rate[i][j]=exchange_rate[i][k]*exchange_rate[k][j];
					parent[i][j]=k;
					if(i==j&&exchange_rate[i][j]>1)
					{
						check=true;
						break;
					}
				}
			if(check)
				break;
		}
		if(check)
			break;
	}
	for(int i=0; i<n; ++i)
		if(exchange_rate[i][i]>1)
		{
			cout<<"YES\n";
			cout<<i+1<<' ';
			print_path(i, i, parent);
			cout<<i+1;
			return 0;
		}
	cout<<"NO";
	return 0;
}
#include<iostream>
#include<vector>

using namespace std;

class DSU
{
public:
	vector<int> rank;
	vector<int> parent;
	DSU(int n)
	{
		parent.resize(n);
		rank.resize(n);
		for(int i=0;i<n;i++)
			MakeSet(i);
	}
	void MakeSet(int i)
	{
		rank[i]=1;
		parent[i]=i;
	}
	int GetRoot(int i)
	{
		if(parent[i]==i)
			return i;
		return parent[i]=GetRoot(parent[i]);
	}
	void Unite(int i,int j)
	{
		j=GetRoot(j);
		i=GetRoot(i);
		if(rank[i]>rank[j])
			parent[j]=i;
		else
		{
			parent[i]=j;
			if(rank[i]==rank[j])
				rank[j]++;
		}
	}

};


int main()
{
	int n,m,a,b,k,query;
	cin>>n>>m;
	DSU dsu(n);
	for(int i=0;i<m;i++)
	{
		cin>>a>>b;
		dsu.Unite(a-1,b-1);
	}
	cin>>k;
	for(int i=0;i<k;i++)
	{
		cin>>query>>a>>b;
		if(query==0)//Запрос на связность
		{
			if(dsu.GetRoot(a-1)==dsu.GetRoot(b-1))
				cout<<"YES";
			else
				cout<<"NO";
		}
		else
			dsu.Unite(a-1,b-1);
	}
	return 0;
}
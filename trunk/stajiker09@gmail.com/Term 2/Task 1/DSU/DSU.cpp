#include <iostream>
#include <vector>
using namespace std;
class DSU
{
public:
	DSU(int n)
	{
		parent.resize(n);
		size.resize(n);
		for(int i=0; i<n; ++i)
			make_set(i);
	}
	int find_set(int v)
	{
		if(v==parent[v])
			return v;
		return parent[v]=find_set(parent[v]);
	}
	void union_sets(int a, int b)
	{
		a=find_set(a);
		b=find_set(b);
		if(a!=b)
		{
			if(size[a]<size[b])
				swap(a, b);
			parent[b]=a;
			size[a]+=size[b];
		}
	}
private:
	vector <int> parent;
	vector <int> size;
	void make_set(int v)
	{
		parent[v]=v;
		size[v]=1;
	}
};
int main()
{
	int n, m, k;
	cin>>n>>m;
	DSU dsu(n);
	for(int i=0; i<m; ++i)
	{
		int a, b;
		cin>>a>>b;
		dsu.union_sets(a-1, b-1);
	}
	cin>>k;
	for(int i=0; i<k; ++i)
	{
		char c;
		int a, b;
		cin>>c>>a>>b;
		if(c=='0')
			if(dsu.find_set(a-1)==dsu.find_set(b-1))
				printf("YES\n");
			else
				printf("NO\n");
		else
			dsu.union_sets(a-1, b-1);
	}
	return 0;
}
#include<vector>
#include<iostream>
#include<algorithm>
#include<cstdlib>

using namespace std;

struct edge
{
	int n1,n2;//номера вершин
	double x1,y1,x2,y2;
	double weight;
	edge(int _n1, int _n2,double _x1, double _y1, double _x2, double _y2)
	{
		n1=_n1;
		n2=_n2;
		x1=_x1;
		y1=_y1;
		x2=_x2;
		y2=_y2;
		weight=sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
	}
	bool operator <(const edge &other) const
	{
		return weight<other.weight;
	}
};

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

void dfs_on_res(int v,vector<bool> &used,vector<int> &ans,vector<vector<int>> &res)
{
	ans.push_back(v);
	used[v]=true;
	for(int i=0;i<res[v].size();i++)
		if(!used[res[v][i]])
			dfs_on_res(res[v][i],used,ans,res);
}

int main()
{
	int m,n;
	double s1,s2;
	
	vector<int> ans;
	vector <edge> g;
	vector <pair<double,double>> points;
	int cost = 0;
	
	cin>>n>>m;
	vector<bool> used(n*m);
	vector<vector<int>> res(n*m);
	cin>>s1>>s2; 
	for (int i = 0; i < n; i++)
    {
        double x;
        double y;
        double s;
        do
        {
            x = (rand() - RAND_MAX / 2) / (double)RAND_MAX;
            y = (rand() - RAND_MAX / 2) / (double)RAND_MAX;
            s = x * x + y * y;
        } while (s == 0 || s > 1);
        s = sqrt(-2 * log(s) / s);
        x = s1 * x * s;
        y = s1 * y * s;
        for (int j = 0; j < m; j++)
        {
            double x2;
            double y2;
            do
            {
                x2 = (rand() - RAND_MAX / 2) / (double)RAND_MAX;
                y2 = (rand() - RAND_MAX / 2) / (double)RAND_MAX;
                s = x2 * x2 + y2 * y2;
            } while (s == 0 || s > 1);
            s = sqrt(-2 * log(s) / s);
            x2 = x + s2 * x2 * s;
            y2 = y + s2 * y2 * s;
            points.push_back(make_pair(x2, y2));
        }
    }

	DSU dsu(n*m);

	for(int i=0;i<points.size()-1;i++)
		for(int j=i+1;j<points.size();j++)
			g.push_back(edge(i,j,points[i].first,points[i].second,points[j].first,points[j].second));

	sort (g.begin(), g.end());
	for (int i=0; i<g.size(); ++i) 
	{
		int a = g[i].n1,  b = g[i].n2,  l = g[i].weight;
		if (dsu.GetRoot(a) != dsu.GetRoot(b)) 
		{
			cost += l;
			res[a].push_back(b);
			res[b].push_back(a);
			dsu.Unite(a,b);
		}
	}
	dfs_on_res(0,used,ans,res);
	for(int i=0;i<ans.size();i++)
		cout<<points[ans[i]].first<<' '<<points[ans[i]].second<<endl;
	return 0;
}
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
using namespace std;
struct point
{
	double x, y;
	point(double X, double Y)
	{
		x=X, y=Y;
	}
	point operator-(const point &b)
	{
		return point(x-b.x, y-b.y);
	}
	double len()
	{
		return sqrt(x*x+y*y);
	}
};
point BoxMuller_transform(point center, double sigma)
{
	const double eps=1e-9;
	double x, y, s;
	do
	{
		x=(double)2*rand()/RAND_MAX-1;
		y=(double)2*rand()/RAND_MAX-1;
		s=x*x+y*y;
	}
	while(s<eps||s>1);
	s=sqrt(-2*log(s)/s);
	return point(center.x+sigma*x*s, center.y+sigma*y*s);
}
void Prim_algo(vector <point> &points, vector < vector <int> > &min_spanning_tree)
{
	vector <bool> used(points.size(), false);
	vector <double> min_e(points.size(), 1e9);
	vector <int> sel_e(points.size(), -1);
	min_e[0]=0;
	for(int i=0; i<points.size(); ++i)
	{
		int v=-1;
		for(int j=0; j<points.size(); ++j)
			if(!used[j]&&(v==-1||min_e[j]<min_e[v]))
				v=j;
		used[v]=true;
		if(sel_e[v]!=-1)
		{
			min_spanning_tree[v].push_back(sel_e[v]);
			min_spanning_tree[sel_e[v]].push_back(v);
		}
		for(int to=0; to<points.size(); ++to)
		{
			double len=(points[to]-points[v]).len();
			if(len<min_e[to])
			{
				min_e[to]=len;
				sel_e[to]=v;
			}
		}
	}
}
void dfs(int v, vector < vector <int> > &g, vector <bool> &used, vector <int> &ans)
{
	ans.push_back(v);
	used[v]=true;
	for(int i=0; i<g[v].size(); ++i)
		if(!used[g[v][i]])
			dfs(g[v][i], g, used, ans);
}
int main()
{
	srand(time(NULL));
	double s1=100, s2=10;
	int n=100, m=100;
	vector <point> points;
	for(int i=0; i<n; ++i)
	{
		point center=BoxMuller_transform(point(0, 0), s1);
		for(int j=0; j<m; ++j)
			points.push_back(BoxMuller_transform(center, s2));
	}
	vector < vector <int> > min_spanning_tree(n*m);
	Prim_algo(points, min_spanning_tree);
	vector <bool> used(n*m, false);
	vector <int> ans;
	dfs(0, min_spanning_tree, used, ans);
	ans.push_back(0);
	double length=0;
	for(int i=1; i<ans.size(); ++i)
		length+=(points[ans[i]]-points[ans[i-1]]).len();
	printf("%.9lf\n", length);
	for(int i=0; i<ans.size(); ++i)
		cout<<ans[i]<<' ';
	return 0;
}
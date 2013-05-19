#include <iostream>
#include <vector>
#include<algorithm>
using namespace std;
const double INF = 1e9;
struct graph{
	int v1;
	int v2;
	double length;
};
int main(){
	//freopen("TextFile2.txt", "r", stdin);
	int n,m;
	cin>>n>>m;
	vector<graph> g(m);
	vector< vector<double> > dist(n+1);
	for(int i=0;i<m;i++){
		int v1,v2;
		double length;
		cin>>v1>>v2>>length;
		g[i].v1=v1-1;
		g[i].v2=v2-1;
		g[i].length=length;
	}
	dist[0].assign(n,INF);
	dist[0][0]=0;
	for(int i=0;i<n;i++){
		dist[i+1].assign(n,INF);
		for(int j=0; j<m; ++j)
			if(dist[i][g[j].v1]!=INF)
				dist[i+1][g[j].v2]=min(dist[i+1][g[j].v2], dist[i][g[j].v1]+g[j].length);
	}
	double min_length = INF;
	for(int i=0; i<n; i++)
		if(dist[n][i]!=INF){
			double check = 0;
			for(int j=0;j<n;j++)
				if(dist[j][i]!=INF)
					check=max(check,(dist[n][i]-dist[j][i])/((double)n-(double)j));
			min_length=min(check, min_length);
		}
	if(min_length!=INF)
		cout<<min_length;
	else
		cout<<"There isn't cycle";
	return 0;
}
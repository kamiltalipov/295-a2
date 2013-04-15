#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;
int main(){
	int n;
	cin>>n;
	vector <vector <pair <int,int>> > g(n);
	int k;
	cin>>k;
	for(int i=0;i<k;i++){
		int a,b,time;
		cin>>a>>b>>time;
		g[a].push_back(make_pair(b,time));
		g[b].push_back(make_pair(a,time));
	} // так как время проезда между станциями на метро не важно, то будем считать, что соединены линии метро, а не станции
	int INF=1e9;
	vector<int> d (n, INF), p(n);
	int begin_station,end_station;
	cin>>begin_station>>end_station;
	d[begin_station] = 0;
	vector <bool> used(n,0);
	for(int i=0;i<n;i++){
		int v=-1;
		for(int j=0;j<n;j++)
			if (!used[j] && (v == -1 || d[j] < d[v]))
				v=j;
		if (d[v]==INF)
			break;
		used[v] = true;
 
		for (int j=0;j<g[v].size();j++){
			int to = g[v][j].first, len = g[v][j].second;
			if (d[v] + len < d[to]) {
				d[to] = d[v] + len;
				p[to] = v;
			}
		}
	}
	vector<int> path;
	for (int v=end_station; v!=begin_station; v=p[v])
		path.push_back (v);
	path.push_back (begin_station);
	reverse (path.begin(), path.end());
	cout<<d[end_station]<<endl;
	for(int i=0;i<path.size();i++)
		cout<<path[i]<<" ";
	return 0;
}
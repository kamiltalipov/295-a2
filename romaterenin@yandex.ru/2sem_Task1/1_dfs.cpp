#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>
using namespace std;
int main(){
	int n, m; // количество вершин и ребер
	cin>>n>>m;
	vector < vector<int> > g(n); // граф
	for(int i=0;i<m;i++){
		int v1,v2;
		cin>>v1>>v2;
		g[v1-1].push_back(v2-1);
	}
	int dfs_timer = 0; // "таймер" для определения времён
	vector<int> color (n,0); // цвет вершины 
	stack < int> s;
	vector < pair<int,int> > ans;
	for(int v=0;v<n;v++){
		if(!color[v])
			s.push(v);
		while(!s.empty()){
			dfs_timer++;
			int x=s.top();
			color[x] = 1;
			int add=0;
			for(int i=0;i<g[x].size();i++){
				if(color[g[x][i]]==0){
					add++;
					s.push(g[x][i]);
				}
				else
					if(color[g[x][i]]==1){
						cout<<"Impossible";
						return 0;
					}
			}
			if(add==0){
				color[x]=2;
				ans.push_back(make_pair (dfs_timer,s.top()));
				s.pop();
			}
		}
	}
	sort(ans.begin(),ans.end());
	for(int i=ans.size()-1;i>=0;i--)
		cout<<ans[i].second + 1<<" ";
	return 0;
}
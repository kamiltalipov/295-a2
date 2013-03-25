#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>
using namespace std;
int main(){
	//freopen("TextFile2.txt", "r", stdin);
	int n, m; // количество вершин и ребер
	cin>>n>>m;
	vector < vector<int> > g(n); // граф
	for(int i=0;i<m;i++){
		int v1,v2;
		cin>>v1>>v2;
		g[v1-1].push_back(v2-1);
	}
	vector<int> color (n,0); // цвет вершины 
	stack < pair<int,int> > s;
	vector <int> ans;
	for(int v=0;v<n;v++){
		if(!color[v])
			s.push(make_pair(v,0));
		while(!s.empty()){
			int x=s.top().first;
			int i=s.top().second;
			if(i==0)
				color[x] = 1;
			for(;i<g[x].size();i++){
				if(color[g[x][i]]==0){
					s.pop();
					s.push(make_pair(x,i));
					s.push(make_pair(g[x][i],0));
					break;
				}
				else
					if(color[g[x][i]]==1){
						cout<<"Impossible";
						return 0;
					}
			}
			if(i == g[x].size()){
				color[x]=2;
				ans.push_back(s.top().first);
				s.pop();
			}
		}
	}
	for(int i=ans.size()-1;i>=0;i--)
		cout<<ans[i] + 1<<" ";
	return 0;
}
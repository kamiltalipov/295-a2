#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>
using namespace std;
int main(){
	//freopen("TextFile2.txt", "r", stdin);
	int n, m; // ���������� ������ � �����
	cin>>n>>m;
	vector < vector<int> > g(n); // ����
	for(int i=0;i<m;i++){
		int v1,v2;
		cin>>v1>>v2;
		g[v1-1].push_back(v2-1);
	}
	int dfs_timer = 0; // "������" ��� ����������� �����
	vector<int> color (n,0); // ���� ������� 
	stack < pair<int,int> > s;
	vector < pair<int,int> > ans;
	for(int v=0;v<n;v++){
		if(!color[v])
			s.push(make_pair(v,0));
		while(!s.empty()){
			dfs_timer++;
			int x=s.top().first;
			color[x] = 1;
			int i=s.top().second;
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
				ans.push_back(make_pair (dfs_timer,s.top().first));
				s.pop();
			}
		}
	}
	sort(ans.begin(),ans.end());
	for(int i=ans.size()-1;i>=0;i--)
		cout<<ans[i].second + 1<<" ";
	return 0;
}
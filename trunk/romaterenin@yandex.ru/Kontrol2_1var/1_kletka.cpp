#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;
int main(){
	int n,m;
	cin>>n>>m;
	vector <vector <bool> > g;
	vector <vector <bool> > used;
	g.resize(n);
	used.resize(n);
	for(int i=0;i<n;i++){
		g[i].resize(m);
		used[i].resize(m,0);
		for(int j=0;j<m;j++){
			char c;
			cin>>c;
			if(c=='1')
				g[i][j]=1;
			else
				g[i][j]=0;
		}
	}
	queue <pair <int,int> > q;
	int ans=0;
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++)
			if(g[i][j] && !used[i][j]){
				q.push(make_pair(i,j));
				while(!q.empty()){
					int a = q.front().first;
					int b = q.front().second;
					used[a][b]=true;
					q.pop();
					if(a!=0 && g[a-1][b] && !used[a-1][b])
						q.push(make_pair(a-1,b));
					if(a!=n-1 && g[a+1][b] && !used[a+1][b])
						q.push(make_pair(a+1,b));
					if(b!=0 && g[a][b-1] && !used[a][b-1])
						q.push(make_pair(a,b-1));
					if(b!=m-1 && g[a][b+1] && !used[a][b+1])
						q.push(make_pair(a,b+1));		
				}
				ans++;
			}
	}
	cout<<ans<<endl;
	return 0;
}
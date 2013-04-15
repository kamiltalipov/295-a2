#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;
int main(){
	int n,m;
	cin>>n;
	vector <vector <bool> > g;
	vector <bool > used;
	g.resize(n);
	used.resize(n);
	for(int i=0;i<n;i++){
		g[i].resize(n);
		for(int j=0;j<n;j++){
			char c;
			cin>>c;
			if(c=='1')
				g[i][j]=1;
			else
				g[i][j]=0;
		}
	}
	queue < int > q;
	vector <int> check(n,0);
	int ans=0;
	for(int i=0;i<n;i++)
		if(!used[i]){
			q.push(i);
			check[i]=1;
			while(!q.empty()){
				int a=q.front();
				used[a]=true;
				q.pop();
				for(int j=0;j<n;j++)
					if(g[a][j]){
						if(!used[j])
							q.push(j);
						if(check[j] == 0)
							if(check[a] == 1)
								check[j] = 2;
							else
								check[j] = 1;
						else
							if(check[a] == check[j]){
								cout<<"BAD"<<endl;
								return 0;
							}
					}
			}
		}
	cout<<"GOOD"<<endl;
	return 0;
}
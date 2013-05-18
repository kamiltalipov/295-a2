#include<iostream>
#include<vector>
using namespace std;

void ans(int v1, int v2, vector < vector <int> > &p){
	if(p[v1][v2]!=v1&&p[v1][v2]!=v2){
		ans(v1, p[v1][v2], p);
		cout<<p[v1][v2]+1<<" ";
		ans(p[v1][v2], v2, p);
	}
}
int main(){
	//freopen("TextFile2.txt", "r", stdin);
	int n;
	double cost;
	vector <vector <double> > g;
	vector <vector < int > > p;
	cin>>n;
	g.resize(n);
	p.resize(n);
	for(int i=0; i<n ; i++){
		g[i].resize(n);
		p[i].resize(n);
		for(int j=0;j<n;j++){
			cin>>cost;
			g[i][j] = cost;
			if(i == j && cost > 1){
				cout<<"All is good. We have free money"<<endl;
				cout<<i;
				return 0;
			}
			p[i][j] = j;
		}
	}
	for(int k=0; k<n; k++)
		for(int i=0; i<n; i++)
			for(int j=0; j<n; j++)
					if(g[i][j] < g[i][k] * g[k][j]){
						g[i][j] = g[i][k] * g[k][j];
						p[i][j]=k;
						if(i == j){
							cout<<"All is good. We have free money"<<endl;
							cout<<i+1<<" ";
							ans(i,i,p);
							cout<<i+1;
							return 0;
						}
							
					}
	for(int i=0; i<n; i++)
		if(g[i][i] > 1){
			cout<<"All is good. We have free money"<<endl;
			cout<<i+1<<" ";
			ans(i,i,p);
			cout<<i+1;
			return 0;
		}
	cout<<"No free money"<<endl;
	return 0;
}
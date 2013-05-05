#include<iostream>
#include<vector>
using namespace std;

int main(){
	//freopen("TextFile2.txt", "r", stdin);
	int n;
	double cost;
	vector <vector <double> > g;
	vector <double> d;
	cin>>n;
	d.resize(n,0);
	d[0]=1;
	g.resize(n);
	vector <int> prev;
	prev.resize(n);
	for(int i=0; i<n ; i++){
		g[i].resize(n);
		for(int j=0;j<n;j++){
			cin>>cost;
			g[i][j] = cost;
			if(i == j && cost > 1){
				cout<<"All is good. We have free money"<<endl;
				cout<<i;
				return 0;
			}
		}
	}
	for(int k=0; k<n-1; k++)
		for(int i=0; i<n; i++)
			for(int j=0; j<n; j++)
				if(d[j]<d[i]*g[i][j]){
					d[j]=d[i]*g[i][j];
					prev[j] = i;
				}
	int begin = -1;
	for(int i=0; i<n; i++)
		for(int j=0; j<n; j++)
			if(d[j] < d[i] * g[i][j]){
					begin=j;
					break;
				}

	if(begin==-1)
		cout<<"No free money";
	else{
		cout<<"All is good. We have free money"<<endl;
		for(int i=0; i<n; i++)
			begin=prev[begin];
		cout<<begin<<" ";
		for(int i=prev[begin]; i!=begin; i=prev[i])
			cout<<i<<" ";
	}
	return 0;
}
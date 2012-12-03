#include<iostream>
#include<vector>
using namespace std;
const int INF=1e9;
void read_Array (vector < int > &Array){
	int size;
	cin>>size;
	Array.resize(size);
	for(int i=0;i<size;i++)
		cin>>Array[i];
}

void write_answer(vector < int  > &Array, vector <int> &parent,int predok, int answer){
	cout<<answer<<endl;
	while(predok!=-1){
		cout<<Array[predok]<<" ";
		predok=parent[predok];
	}
	cout<<endl;
}

int bin_search(vector < pair <int, pair <int,int>  > > Array,int current){
	int left=0,right=Array.size()+1;
	while(left<right-1){
		int middle=(left+right)/2;
		if(Array[middle].first <= current)
			left=middle;
		else
			right=middle;
	}
	if(Array[right-1].first != current)
		return right;
	else
		return 0;
}

int main(){
	vector <int> Array;
	read_Array(Array);
	int n=Array.size();
	vector < pair <int, pair <int,int> > > count (n+1);
	vector <int> parent(n+1);
	int answer=1,predok=0;
	for(int i=0;i<n+1;i++){
		if(i==0)
			count[i].first=-INF;
		else
			count[i].first=INF;
		parent[i]=-1;
	}
	for(int i=0;i<n;i++){
		int x=Array[i];
		int poz=bin_search(count,x);
		if(!poz)
			continue;
		count[poz].first=x;
		if(answer <= poz){
			answer = poz;
			parent[count[poz-1].second.first]=i;
			predok=count[poz-1].second.second;
		}
		count[poz].second.first=i;
		count[poz].second.second=count[poz-1].second.second;
	}
	write_answer(Array,parent,predok,answer);
	return 0;
}
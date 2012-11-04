#include<iostream>
#include<vector>
using namespace std;
const int INF=1e9;
void read_Array (vector <int> &Array){
	int size;
	cin>>size;
	Array.resize(size);
	for(int i=0;i<size;i++)
		cin>>Array[i];
}

void write_answer(vector < pair <int,vector <int> > > &Array,int answer){
	cout<<answer<<endl;
	for(int i=0;i<Array[answer].second.size();i++)
		cout<<Array[answer].second[i]<<' ';
	cout<<endl;
}

int bin_search(vector < pair <int,vector <int> > > Array,int current){
	int left=0,right=Array.size()+1;
	while(left<right-1){
		int middle=(left+right)/2;
		if(Array[middle].first <= current)
			left=middle;
		else
			right=middle;
	}
	return right;
}

int main(){
	vector <int> Array;
	read_Array(Array);
	int n=Array.size();
	vector < pair <int,vector <int> > > count (n+1);
	int answer=1;
	for(int i=0;i<n+1;i++)
		if(i==0)
			count[i].first=-INF;
		else
			count[i].first=INF;
	for(int i=0;i<Array.size();i++){
		int x=Array[i];
		int poz=bin_search(count,x);
		count[poz].first=x;
		count[poz].second.clear();
		if(poz!=1)
			count[poz].second=count[poz-1].second;
		count[poz].second.push_back(x);
		if(answer < poz)
			answer = poz;
	}
	write_answer(count,answer);
	return 0;
}
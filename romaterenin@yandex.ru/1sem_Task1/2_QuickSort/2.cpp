#include<iostream>
#include<vector>
#include<algorithm>
#include<stdio.h>
#include<stack>
using namespace std;

void random_Array(vector <int> &Array){
	int size=100000;
	//cin>>size;
	Array.resize(size);
	for(int i=0;i<size;i++)
		Array[i]=rand();
}

bool check(vector <int> &Array){
	for(int i=0;i<Array.size()-1;i++)
		if(Array[i]>Array[i+1])
			return false;
	return true;
}

pair <int,int> partition(vector <int> &Array, int left, int right){ // exercise 2b, procedure "partition"
	int i=left,j=right,middle=(right+left)/2,opor=Array[middle];;
	do{
		while(Array[i]<opor) i++;
		while(Array[j]>opor) j--;
		if(i<=j){
			swap(Array[i],Array[j]); i++; j--;
		}
	}while(i<=j);
	return make_pair(i,j);
}

void recursive_quick_sort(vector <int> &Array, int left, int right){
	if(left<right){
		pair <int,int> middle=partition(Array,left,right);
		if(left<middle.second)
			recursive_quick_sort(Array,left,middle.second);
		if(right>middle.first)
			recursive_quick_sort(Array,middle.first,right);
	}
}

void unrecursive_quick_sort(vector <int> &Array){
	stack <pair <int,int> > Stack;
	Stack.push(make_pair(0,Array.size()-1));
	while(!Stack.empty()){
		int left=Stack.top().first,right=Stack.top().second;
		Stack.pop();
		if(left<right){
			pair <int,int> middle=partition(Array,left,right);
			if(left<middle.second)
				Stack.push(make_pair(left,middle.second));
			if(right>middle.first)
				Stack.push(make_pair(middle.first,right));
		}
	}
}

int main(){
	vector <int> sort_Array_for_qs;
	random_Array(sort_Array_for_qs);
	vector <int> sort_Array_for_UNqs=sort_Array_for_qs;
	recursive_quick_sort(sort_Array_for_qs,0,sort_Array_for_qs.size()-1);
	if(check(sort_Array_for_qs))
		cout<<"Recursive quick sort is correct"<<endl;
	else
		cout<<"Recursive quick sort is not correct"<<endl;
	unrecursive_quick_sort(sort_Array_for_UNqs);
	if(check(sort_Array_for_UNqs))
		cout<<"Unrecursive quick sort is correct"<<endl;
	else
		cout<<"Unrecursive quick sort is not correct"<<endl;
	return 0;
}
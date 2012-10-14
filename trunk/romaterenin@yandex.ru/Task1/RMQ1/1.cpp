#include<iostream>
#include<vector>
#include<algorithm>
#include<stdio.h>
#include<stack>
using namespace std;

vector <int> new_Array;
int number_of_inversion_ms,number_of_inversion_bs;

void read_Array (vector <int> &Array){
	int size;
	cin>>size;
	Array.resize(size);
	for(int i=0;i<size;i++)
		cin>>Array[i];
}

void bubble_sort(vector <int> &Array){
	for(int i=0;i<Array.size();i++)
		for(int j=i+1;j<Array.size();j++)
			if(Array[i]>Array[j]){
				swap(Array[i],Array[j]);
				number_of_inversion_bs++;
			}
}

void merge_sort(vector <int> &Array, int left,int right){
	if(left==right)
		return;
	if(left+1==right)
	{
		if(Array[left]>Array[right]){
			swap(Array[left],Array[right]);
			number_of_inversion_ms++;
		}
		return;
	}
	int middle=(left+right)/2;
	merge_sort(Array,left,middle);
	merge_sort(Array,middle+1,right);
	for(int i=left;i<=middle;i++)
		new_Array[i]=Array[i];
	int index1=left,index2=middle+1;
	for(int i=left;i<=right;i++){
		if(index1>middle)
			break;
		if(index2>right){
			for(int j=index1;j<=middle;j++)
				Array[j+middle-left]=new_Array[j];
			break;
		}
		if(new_Array[index1]>Array[index2])
			Array[i]=Array[index2],index2++;
		else
			Array[i]=new_Array[index1],index1++;
	}
}

int main(){
	vector <int> Array_for_ms,Array_for_bs;
	read_Array(Array_for_ms);
	Array_for_bs=Array_for_ms;
	new_Array.resize(Array_for_ms.size());
	merge_sort(Array_for_ms,0,Array_for_ms.size()-1);
	bubble_sort(Array_for_bs);
	if(number_of_inversion_bs>number_of_inversion_ms)
		cout<<"Number of inversion in bubble_sort MORE than numder of inversion in merge_sort"<<endl;
	else
		if(number_of_inversion_bs==number_of_inversion_ms)
			cout<<"Number of inversion in bubble_sort EQUAL numder of inversion in merge_sort"<<endl;
		else
			cout<<"Number of inversion in bubble_sort LESS than numder of inversion in merge_sort"<<endl;
	return 0;
}
#include<iostream>
#include<vector>
#include<algorithm>
#include<stdio.h>
#include<string>
using namespace std;

struct student{
	int nomer;
	string surname;
	int mark;
};
vector <pair <string,int> > answer[6];
void read_Array_couting_sort (vector <student> &Array){
	int size;
	cin>>size;
	Array.resize(size);
	for(int i=0;i<size;i++){
		cin>>Array[i].nomer>>Array[i].surname>>Array[i].mark;
		answer[Array[i].mark].push_back(make_pair(Array[i].surname,Array[i].nomer));
	}
}

void write_Array(){
	for(int i=2;i<6;i++)
		for(int j=0; j<answer[i].size(); j++)
			cout<<answer[i][j].second<<" "<<answer[i][j].first<<" "<<i<<endl;
}
void counting_sort_student();

int main(){
	vector <student> students;
	read_Array_couting_sort(students);
	write_Array();
	return 0;
}
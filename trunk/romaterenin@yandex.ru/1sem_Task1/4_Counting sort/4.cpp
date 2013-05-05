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

vector <student> read_Array_and_couting_sort (vector <student> &Array){
	int size;
	cin>>size;
	Array.resize(size);
	int kol_mark[6]={0,0,0,0,0,0};
	for(int i=0;i<size;i++){
		cin>>Array[i].nomer>>Array[i].surname>>Array[i].mark;
		kol_mark[Array[i].mark]++;
	}
	for(int i=3;i<=5;i++)
		kol_mark[i]+=kol_mark[i-1];
	vector <student> answer(size);
	for(int i=size-1;i>=0;i--){
		answer[kol_mark[Array[i].mark]-1]=Array[i];
		kol_mark[Array[i].mark]--;
	}
	return answer;

}

void write_Array(vector <student> &Array){
		for(int i=0; i<Array.size(); i++)
			cout<<Array[i].nomer<<" "<<Array[i].surname<<" "<<Array[i].mark<<endl;
}

int main(){
	vector <student> students;
	vector <student> sort_student=read_Array_and_couting_sort(students);
	write_Array(sort_student);
	return 0;
}
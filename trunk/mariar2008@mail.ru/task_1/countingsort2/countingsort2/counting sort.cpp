#include<vector>
#include<cstdio>
#include<stdio.h>
#include<ctime>
#include<cstdlib>
#include<iostream>
#include<string>

using namespace std;

struct myType{
	int id;
	string Name;
	int Mark;
};

void read(vector<myType>&Student){
	for (int i = 0; i < Student.size(); i++){
		cin >> Student[i].id >> Student[i].Name >> Student[i].Mark;
	}
}

void CountingSort(vector<myType>&Student){
	int Num[6] = {0};
	vector<myType>tmp(Student.size());
	tmp = Student;
	for (int i = 0; i < Student.size(); i++){
		Num[tmp[i].Mark]++;
	}

	for (int i = 3; i < 6; i++){
		Num[i] += Num[i - 1];
	}
	
	for (int i = Student.size() - 1; i >= 0; i--){
		int j = tmp[i].Mark;
		Student[Num[tmp[i].Mark] - 1] = tmp[i];
		Num[tmp[i].Mark]--;
	}

}

bool Check(const vector<myType>&Student){
	for (int i = 1; i < Student.size(); i++){
		if (Student[i].Mark < Student[i - 1].Mark){
			return false;
		}
	}
	return true;
}

void write(const vector<myType>&Student){
	if (!Check(Student)){
		cout << "FAIL";
	}   
	for (int i = 0; i < Student.size(); i++){
		cout << Student[i].id << " " << Student[i].Name << " " << Student[i].Mark << endl;
	}
}

int main( void ){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int n;
	cin >> n;
	vector<myType>Student(n);
	read(Student);
	CountingSort(Student);
	write(Student);
	return 0;
}
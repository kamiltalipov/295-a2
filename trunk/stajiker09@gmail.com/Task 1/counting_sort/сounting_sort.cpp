#include <iostream>
#include <vector>
#include <string>
using namespace std;
struct student
{
	int number, mark;
	string name;
};
void counting_sort(vector <student> &students, vector <student> &sorted_students)
{
	int marks[6];
	memset(marks, 0, sizeof(marks));
	for(int i=0; i<students.size(); ++i)
		marks[students[i].mark]++;
	for(int i=3; i<6; ++i)
		marks[i]+=marks[i-1];
	for(int i=students.size()-1; i>=0; --i)
	{
		sorted_students[marks[students[i].mark]-1]=students[i];
		marks[students[i].mark]--;
	}
}
int main()
{
	int n;
	cin>>n;
	vector <student> students(n), sorted_students(n);
	for(int i=0; i<n; ++i)
		cin>>students[i].number>>students[i].name>>students[i].mark;
	counting_sort(students, sorted_students);
	for(int i=0; i<n; ++i)
		cout<<sorted_students[i].number<<' '<<sorted_students[i].name<<' '<<sorted_students[i].mark<<endl;
	return 0;
}
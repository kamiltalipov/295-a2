#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int MAX_GRADE = 5;

struct Student
{
	int studentCardNumber;
	string lastName;
	int grade;
};

vector <Student> CountingSort(vector <Student> &students)
{
	int* count = new int[MAX_GRADE + 1];
	for (int i = 0; i < MAX_GRADE + 1; i++)
		count[i] = 0;

	vector <Student> sortedStudents;
	sortedStudents.resize(students.size());

	for (vector <Student>::iterator it = students.begin(); it != students.end(); it++)
	{
		count[(*it).grade]++;
	}

	for (int i = 1; i < MAX_GRADE + 1; i++)
	{
		count[i] = count[i - 1] + count[i];
	}
	
	int grade;
	vector <Student>::reverse_iterator it;
	for (it = students.rbegin(); it != students.rend(); it++)
	{
		grade = (*it).grade;
		sortedStudents[count[grade] - 1] = *it;
		count[grade]--;
	}

	delete[] count;
	return sortedStudents;
}

int main()
{
	vector <Student> students;
	int n;
	cin >> n;
	students.resize(n);
	for (int i = 0; i < n; i++)
	{
		cin >> students[i].studentCardNumber;
		cin >> students[i].lastName;
		cin >> students[i].grade;
	}
	
	students = CountingSort(students);
	vector <Student>::iterator it;
	for (it = students.begin(); it != students.end(); it++)
	{
		cout << (*it).studentCardNumber << " " << (*it).lastName << " " << (*it).grade << endl;
	}

	return 0;
}
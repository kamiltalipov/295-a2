#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>

using namespace std;

struct Student
{
	int Grade, Number;
	string Surname;
};


int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int n = 0;
	cin >> n;

	vector <Student> Main_Array;
	Student Temp;
	vector < vector <int> > Sorted_Array(5);

	for (int i = 0; i < n; i++)
	{
		cin >> Temp.Number >> Temp.Surname >> Temp.Grade;
		Main_Array.push_back(Temp);
		Sorted_Array[ Temp.Grade ].push_back(i);
	}

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < Sorted_Array[i].size(); j++)
		{
			int Temp = Sorted_Array[i].back();
			cout << Main_Array[Temp].Number << " " << Main_Array[Temp].Surname << " " << Main_Array[Temp].Grade << endl;
		}
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}
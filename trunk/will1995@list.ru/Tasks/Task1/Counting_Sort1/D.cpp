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

vector <Student> Sort(const vector <Student> Main_Array, const vector < vector <int> > Sorted_Array)
{
	vector <Student> Answer;
	for(int i = 0; i < 5; i++)
	{
		int Size = Sorted_Array[i].size();
		for(int j = 0; j  < Size; j++)
		{
			int Temp = Sorted_Array[i][j];
			Answer.push_back(Main_Array[Temp]);
		}
	}
	return Answer;
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int n = 0;
	cin >> n;

	vector <Student> Main_Array;
	vector < vector <int> > Sorted_Array;
	Sorted_Array.assign(5, vector <int>());

	for (int i = 0; i < n; i++)
	{
		Student Temp;
		cin >> Temp.Number >> Temp.Surname >> Temp.Grade;
		Main_Array.push_back(Temp);
		Sorted_Array[ Temp.Grade - 1 ].push_back(i);
	}

	vector <Student> Answer = Sort(Main_Array, Sorted_Array);

	for(int i = 0; i < Answer.size(); i++)
		cout << Answer[i].Number << " " << Answer[i].Surname << " " << Answer[i].Grade << endl;
	fclose(stdin);
	fclose(stdout);
	return 0;
}
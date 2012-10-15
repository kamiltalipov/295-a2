#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
using namespace std;

struct student {
	int mark;
	string format;
};

vector < student > lists[4];	

istream& operator>> (istream& in, student &st)
{
	string s;
	getline(in, s);
	st.format = "";
	int i = 0;
	for (int spaces = 2; spaces; ++i)
	{
		if (s[i] == ' ')
			--spaces;
		st.format += s[i];
	}
	sscanf(s.c_str() + i, "%d", &st.mark);
	return in;
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n; student stud;
	scanf("%d\n", &n);
	for (int i = 0; i < n; ++i)
	{
		cin >> stud;
		lists[stud.mark - 2].push_back(stud);
	}
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < lists[i].size(); ++j)
		{
			printf("%s%d\n", lists[i][j].format.c_str(), lists[i][j].mark);
		}
	}
	return 0;
}
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

ostream& operator<< (ostream& out, const student& st)
{
	out << st.format << " " << st.mark;
	return out;
}

vector < student >* counting_sort(const vector < student > arr)
{
	vector < int > indexes(4, 0);
	for (int i = 0; i < arr.size(); ++i)
		++indexes[arr[i].mark - 2];
	for (int i = 1; i < indexes.size(); ++i)
		indexes[i] += indexes[i - 1];
	indexes[0] = 0;
	for (int i = 1; i < indexes.size(); ++i)
		--indexes[i];
	vector < student > *ans = new vector < student > (arr.size());
	for (int i = 0; i < arr.size(); ++i)
		ans->at(indexes[arr[i].mark - 2]++) = arr[i];
	return ans;
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n; student stud;
	scanf("%d\n", &n);
	vector < student > studs, *ans;
	student st;
	for (int i = 0; i < n; ++i)
	{
		cin >> st;
		studs.push_back(st);
	}
	ans = counting_sort(studs);
	for (int i = 0; i < ans->size(); ++i)
		cout << ans->at(i) << endl;
	delete ans;
	return 0;
}
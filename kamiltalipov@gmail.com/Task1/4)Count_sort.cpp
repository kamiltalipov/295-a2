#include <iostream>
using std :: cin;
using std :: cout;
using std :: istream;
using std :: ostream;
#include <cstdio>
#include <string>
using std :: string;

const int FIRST_MARK = 2;
const int MAX_MARK = 5 + 1;

struct Student
{
public:
    Student ()
        :
        cardId (), mark (),
        name ()
    {
    }

    friend inline istream& operator >> (istream& input, Student& s);
    friend inline ostream& operator << (ostream& output, const Student& s);

    int cardId, mark;
    string name;
};

inline istream& operator >> (istream& input, Student& s)
{
    input >> s.cardId >> s.name >> s.mark;
    return input;
}

inline ostream& operator << (ostream& output, const Student& s)
{
    output << s.cardId << ' ' << s.name << ' ' << s.mark;
    return output;
}

Student* sort (Student s[], int size)
{
    int nMark[MAX_MARK] = {};
    for (int i = 0; i < size; ++i)
        ++nMark[s[i].mark];

	int sumPrefMark[MAX_MARK] = {};
	for (int i = FIRST_MARK + 1; i < MAX_MARK; ++i)
		sumPrefMark[i] = nMark[i - 1] + sumPrefMark[i - 1];

    Student* res = new Student[size];
    for (int i = 0; i < size; ++i)
    {
        res[sumPrefMark[s[i].mark]] = s[i];
        ++sumPrefMark[s[i].mark];
    }


    return res;
}

int main ()
{
    freopen ("input.txt", "r", stdin);

    int allStudents = 0;
    cin >> allStudents;
    Student* students = new Student[allStudents];
    for (int i = 0; i < allStudents; ++i)
        cin >> students[i];

    Student* res = sort (students, allStudents);

    for (int i = 0; i < allStudents; ++i)
        cout << res[i] << '\n';

    delete[] students;
    delete[] res;

    return 0;
}

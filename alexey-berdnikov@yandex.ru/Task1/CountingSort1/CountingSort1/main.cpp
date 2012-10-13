#include < iostream >
#include < string >
#include < cassert >

using namespace std;

const int MAX_MARK = 5;

struct student {
	int num, mark;
	string surname;
};

void counting_sort(student* students, int size)
{
	int c[MAX_MARK+1];
	for (int i = 1; i <= MAX_MARK; ++i) c[i] = 0;
	student* buf = new student[size];
	for (int i = 0; i < size; ++i) ++c[students[i].mark];
	for (int i = MAX_MARK-1; i > 0; --i) c[i] += c[i+1];
	for (int i = size-1; i >= 0; --i) {
		int& j = c[students[i].mark];
		--j;
		buf[j] = students[i];
	}
	for (int i = 0; i < size; ++i) students[i] = buf[i];

	delete[] buf;
}

int main()
{
	student* students;
	int n;

	cin >> n;
	students = new student[n];
	for (int i = 0; i < n; ++i) {
		cin >> students[i].num
			>> students[i].surname
			>> students[i].mark;
		assert(0<students[i].mark&&students[i].mark<=MAX_MARK);
	}

	counting_sort(students,n);
	for (int i = 0; i < n; ++i) {
		cout << students[i].num << ' '
			<< students[i].surname << ' '
			<< students[i].mark << endl;
	}

	delete[] students;
	_CrtDumpMemoryLeaks();
}
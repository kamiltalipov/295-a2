#include <stdio.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
	freopen("input.txt", "w", stdout);
	srand(time(NULL));
	int n;
	n = rand() % 10;
	cout << n << endl;
	for (int i = 0; i < n; i++)
	{
		cout << rand() << " ";
		string str[10];
		for (int j = 0; j < 10; j++)
			str[j] = rand() % 100 + 32;
		cout << str << " " << rand() % 5 + 1 << endl;
	}
	fclose(stdout);
	return 0;
}

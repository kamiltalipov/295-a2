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
	n = (rand() % 25000 + 1)*4;/*
	for(int i = 0; i < n / 4; i++)
	{
		cout << "+ ";
		int m = rand()%100;
		for(int j = 0; j < m; j++)
		{
			int x = rand()%10;
			cout << x;
		}
		cout << '\n';
	}
	
	for(int i = 0; i < n / 4; i++)
	{
		cout << "+ ";
		int m = rand()%10 + 1;
		for(int j = 0; j < m; j++)
		{
			int x = rand()%10;
			cout << x;
		}
		cout << '\n';
	}
	
	*/for(int i = 0; i < n / 2; i++)
	{
		cout << "+ " << rand()%10 << '\n';
	}
	for(int i = 0; i < n / 2; i++)
	{
		cout << "? " << rand()%10 << '\n';
	}
	
	cout << "#\n";
	fclose(stdout);
	return 0;
}

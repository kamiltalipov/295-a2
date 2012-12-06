#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <string>

using namespace std;

struct elem
{
	int min, add;
};

class RMQ
{
private:
	void build( vector <elem> &buff );

public:
	vector <elem> data;
	RMQ( vector <int> &buff );
};

RMQ::RMQ( vector <int> &buff )
{
	int len = buff.size() - 1;
	len = (-len & (len + len));
	data.resize(len * 2);

	for (int i = 0; i < buff.size(); i++)
		data[i + len].min = buff[i];

	for (int i = buff.size(); i < len; i++)
		data[i + len].min = INT_MAX;
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int n;

	cin >> n;
	vector <int> input(n);
	for (int i = 0; i < n; i++)
	{
		cin >> input[i];	
	}
	RMQ Tree(input);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
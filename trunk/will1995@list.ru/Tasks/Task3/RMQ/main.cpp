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
	void build( int len );
	void push ( int v );
	int min ( int l, int r, int lb, int rb, int v );
	vector <elem> data;

public:
	int size;
	RMQ( vector <int> &buff );
	int Get_Min ( int l, int r, int lb, int rb, int v );
};

void RMQ::push( int v )
{
	data[v * 2].add += data[v].add;
	data[v * 2 + 1].add += data[v].add;
	data[v].min += data[v].add;
	data[v].add = 0;
}

void RMQ::build( int len )
{
	for (int i = len - 1; i >= 1; i--)
	{
		if (data[i * 2].min < data[i * 2 + 1].min)
			data[i] = data[i * 2];
		else
			data[i] = data[i * 2 + 1];
	}
	data[0].min = INT_MAX;
}

int RMQ::min (int l, int r, int lb, int rb, int v)
{
	if ((l > rb) || (r < lb))
		return 0;

	if ((l >= lb) && (r <= rb))
		return v;

	push(v);
	
	int mid = (l + r) / 2;
	int a = min (l, mid, lb, rb, v * 2);
	int b = min (mid + 1, r, lb, rb, v * 2);
	if (data[a].min < data[b].min)
		return a;
	else
		return b;
}

int RMQ::Get_Min( int l, int r, int lb, int rb, int v )
{
	int ans = data[min ( l, r, lb, rb, v )].min;
	return ans;
}

RMQ::RMQ( vector <int> &buff )
{
	int len = buff.size() - 1;
	len = (-len & (len + len)); // it's a kind of magic, magic
	data.resize(len * 2);

	for (int i = 0; i < buff.size(); i++)
		data[i + len].min = buff[i];

	for (int i = buff.size(); i < len; i++)
		data[i + len].min = INT_MAX;

	build( len );
	size = len * 2;
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


	cout << Tree.Get_Min(1, Tree.size / 2, 1, 2, 1);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
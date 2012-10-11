#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

class Heap
{
public:
	bool Empty();
	Heap();

	void Heap_Sort(vector <int> &Array);
	int Pop();
	void Add( int n );

private:
	vector <int> Array;
	void Delete();
	void Sift_Down();
	void Sift_Up();
};

Heap::Heap()
{
	Array.push_back(1 << 32 - 1);
}

bool Heap::Empty()
{
	return Array.size() == 1;
}

void Heap::Sift_Up()
{

	int i = Array.size() - 1;
	while (Array[i] < Array[i / 2])
	{
		swap(Array[i], Array[i / 2]);
		i = i / 2;
	}
}

void Heap::Sift_Down()
{
	int i = 1;
	int Min = 1;

	while (((i * 2 + 1) < Array.size()) && ((i * 2) < Array.size()) && (i == Min))
	{
		if (Array[i * 2] < Array[i * 2 + 1])
			Min = i * 2;
		else
			Min = i * 2 + 1;
		
		if (Array[i] > Array[Min])
		{
			swap(Array[i], Array[Min]);
			i = Min;
		}
	}
	
	Min = i;
	if (((i * 2) < Array.size()) && (Array[i * 2] < Array[i]))
	{
		swap(Array[i], Array[i * 2]);
		Min = i * 2;
	}

	if (((i * 2 + 1) < Array.size()) && (Array[i * 2 + 1] < Array[Min]))
		swap(Array[Min], Array[i * 2 + 1]);
}

void Heap::Delete()
{
	swap(Array[1], Array[Array.size() - 1]);
	Array.pop_back();
	Sift_Down();
}

int Heap::Pop()
{
	int Temp = Array[1];
	Delete();
	return Temp;
}

void Heap::Heap_Sort (vector <int> &Array)
{
	while (!Empty())
		Array.push_back(Pop());
}

void Heap::Add( int n )
{
	Array.push_back(n);
	Sift_Up();
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int n, x;
	cin >> n;
	vector <int> Array;
	Heap Heap;
	for(int i = 0; i < n; i++)
	{
		cin >> x;
		Heap.Add(x);
	}

	Heap.Heap_Sort(Array);
	for(int i = 0; i < Array.size(); i++)
		cout << Array[i] << " ";
	cout << endl;
	fclose(stdin);
	fclose(stdout);
	return 0;
}
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

class Heap
{
public:
	bool Empty();
	vector <int> Array;
	Heap();

	void Heap_Sort();
	void Pop();
	void Add( int n );

private:
	int size;
	void Delete();
	void Sift_Down();
	void Sift_Up();
};

Heap::Heap()
{
	Array.push_back(1 << 31 - 1);
	size = 0;
}

bool Heap::Empty()
{
	return size == 0;
}

void Heap::Sift_Up()
{

	int i = size;
	while (Array[i] > Array[i / 2])
	{
		swap(Array[i], Array[i / 2]);
		i = i / 2;
	}
}

void Heap::Sift_Down()
{
	int i = 1;
	int Max = 1;

	while (((i * 2 + 1) <= size) && ((i * 2) < size) && (i == Max))
	{
		if (Array[i * 2] > Array[i * 2 + 1])
			Max = i * 2;
		else
			Max = i * 2 + 1;
		
		if (Array[i] < Array[Max])
		{
			swap(Array[i], Array[Max]);
			i = Max;
		}
	}
	
	Max = i;
	if (((i * 2) <= size) && (Array[i * 2] > Array[i]))
	{
		swap(Array[i], Array[i * 2]);
		Max = i * 2;
	}

	if (((i * 2 + 1) <= size) && (Array[i * 2 + 1] > Array[Max]))
		swap(Array[Max], Array[i * 2 + 1]);
}

void Heap::Delete()
{
	swap(Array[1], Array[size]);
	//Array.erase(Array.begin());
	size--;
	Sift_Down();
}

void Heap::Pop()
{
	//int Temp = Array[1];
	Delete();
	//return Temp;
}

void Heap::Heap_Sort ()
{
	while (!Empty())
		Pop();
}

void Heap::Add( int n )
{
	Array.push_back(n);
	size++;
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

	Heap.Heap_Sort();
	for(int i = 1; i < Heap.Array.size(); i++)
		cout << Heap.Array[i] << " ";
	cout << endl;
	fclose(stdin);
	fclose(stdout);
	return 0;
}
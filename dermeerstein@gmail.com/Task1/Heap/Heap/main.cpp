#include <iostream>
#include <vector>
#include <crtdbg.h>
#include <cassert>
#include <ctime>

using namespace std;

class Heap
{
public:
	Heap();
	Heap(vector <int>& outside_vector);
	//~Heap();
	void Add(int value);
	void Delete(int index);
	void Print();
	int Max();
	int Size();
private:
	vector <int>& heap;
	vector <int> buffer;
	int size;

	int parent(int index);
	int left_child(int index);
	int right_child(int index);
	void siftup(int index);
	void siftdown(int index);
};

Heap::Heap():heap(buffer)
{
	size = 0;
}

Heap::Heap(vector <int>& outside_vector):heap(outside_vector)
{
	size = outside_vector.size();
	
	for (int i = size - 1; i >= 0; i--)
	{
		siftdown(i);
	}
}

inline int Heap::parent(int index)
{
	return (index - 1) / 2;
}

inline int Heap::left_child(int index)
{
	return ((2 * index + 1 < size) ? 2 * index + 1 : -1);
}

inline int Heap::right_child(int index)
{
	return ((2 * index + 2 < size) ? 2 * index + 2 : -1);
}

void Heap::siftup(int index)
{
	while (index != 0 && heap[index] > heap[parent(index)])
	{
		swap(heap[index], heap[parent(index)]);
		index = parent(index);
	}
}

void Heap::siftdown(int index)
{
	int swap_ind, right_ind, left_ind;
	left_ind = left_child(index);
	right_ind = right_child(index);
	if (left_ind != -1 && right_ind != -1)
		swap_ind = (heap[left_ind] > heap[right_ind]) ? left_ind : right_ind;
	else if (left_ind != -1)
		swap_ind = left_ind;
	else if(right_ind != -1)
		swap_ind = right_ind;
	else
		return;

	while (heap[index] < heap[swap_ind])
	{
		swap(heap[index], heap[swap_ind]);
		index = swap_ind;
		left_ind = left_child(index);
		right_ind = right_child(index);
		if (left_ind != -1 && right_ind != -1)
			swap_ind = (heap[left_ind] > heap[right_ind]) ? left_ind : right_ind;
		else if (left_ind != -1)
			swap_ind = left_ind;
		else if(right_ind != -1)
			swap_ind = right_ind;
		else
			return;
	}
}

void Heap::Add(int value)
{
	if (heap.size() > size)
		heap[size] = value;
	else
		heap.push_back(value);
	++size;
	siftup(size - 1);
}

void Heap::Delete(int index)
{
	swap(heap[index], heap[size - 1]);
	--size;
	siftup(index);
	siftdown(index);
}

int Heap::Max()
{
	return heap[0];
}

int Heap::Size()
{
	return size;
}

void Heap::Print()
{
	for (int i = 0; i < size; i++)
		cout << heap[i] << " ";
	cout << endl;
}

void HeapSort(vector <int>& Array)
{
	Heap H(Array);
	int temp;
	for (int i = 0; i < Array.size(); i++)
	{
		temp = H.Max();
		H.Delete(0);
		Array[H.Size()] = temp;
	}
}

bool isSorted(const vector <int>& Array)
{
	for (int i = 0; i < Array.size() - 1; i++)
	{
		if (Array[i] > Array[i + 1])
			return 0;
	}
	return 1;
}

int main()
{
	{
		int n, t;
		/*vector <int> v;
		cin >> n;
		for (int i = 0; i < n; i++)
		{
			cin >> t;
			v.push_back(t);
		}
		HeapSort(v);
		for (int i = 0; i < v.size(); i++)
		{
			cout << v[i] << " ";
		}*/
		for (int j = 0; j < 10; j++)
		{
			vector <int> v;
			srand(time(NULL));
			n = rand();
			for (int i = 0; i < n; i++)
			{
				v.push_back(rand());
			}
			HeapSort(v);
			assert(isSorted(v));
		}
	}
	_CrtDumpMemoryLeaks();
	return 0;
}
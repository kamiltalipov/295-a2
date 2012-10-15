#include <iostream>
#include <vector>
using namespace std;
class Heap
{
public:
	Heap();
	Heap(vector <int> &array);
	void Push(int value);
	int Top();
	void Pop();
private:
	vector <int> heap;
	int size;
	void Heapify();
	void SiftUp(int index);
	void SiftDown(int index);
};
Heap::Heap()
{
	heap.resize(1);
	size=1;
}
Heap::Heap(vector <int> &array)
{
	heap=array;
	size=array.size()-1;
	Heapify();
}
void Heap::Heapify()
{
	for(int i=size; i>0; --i)
		SiftDown(i);
}
void Heap::SiftUp(int index)
{
	while(index!=1)
	{
		if(heap[index]>heap[index/2])
			swap(heap[index], heap[index/2]);
		else
			break;
		index/=2;
	}
}
void Heap::SiftDown(int index)
{
	int next_index=index;
	if(2*index<=size&&heap[2*index]>heap[next_index])
		next_index=2*index;
	if(2*index+1<=size&&heap[2*index+1]>heap[next_index])
		next_index=2*index+1;
	if(next_index!=index)
	{
		swap(heap[index], heap[next_index]);
		SiftDown(next_index);
	}
}
void Heap::Push(int value)
{
	++size;
	heap.push_back(value);
	SiftUp(size);
}
int Heap::Top()
{
	return heap[1];
}
void Heap::Pop()
{
	heap[1]=heap[size];
	heap.resize(size);
	--size;
	SiftDown(1);
}
void HeapSort(vector <int> &array)
{
	Heap heap(array);
	array.resize(array.size()-1);
	for(int i=array.size()-1; i>=0; --i)
	{
		array[i]=heap.Top();
		heap.Pop();
	}
}
bool IsSorted(vector <int> &array)
{
	for(int i=1; i<array.size(); ++i)
		if(array[i-1]>array[i])
			return false;
	return true;
}
int main()
{
	int n;
	cin>>n;
	vector <int> array(n+1);
	for(int i=1; i<=n; ++i)
		cin>>array[i];
	HeapSort(array);
	cout<<IsSorted(array);
	return 0;
}
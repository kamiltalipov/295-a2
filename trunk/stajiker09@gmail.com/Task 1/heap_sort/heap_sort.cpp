#include <iostream>
#include <vector>
using namespace std;
class Heap
{
public:
	Heap();
	Heap(vector <int> &array);
	void print();
	void Push(int value);
	int Top();
	void Pop();
	void HeapSort();
private:
	vector <int> *heap;
	vector <int> buffer;
	int size;
	void Heapify();
	void SiftUp(int index);
	void SiftDown(int index);
};
Heap::Heap()
{
	buffer.resize(1);
	heap=&buffer;
	size=0;
}
Heap::Heap(vector <int> &array)
{
	heap=&array;
	size=array.size()-1;
	Heapify();
}
void Heap::print()
{
	for(int i=1; i<=size; ++i)
		cout<<(*heap)[i]<<' ';
	cout<<endl;
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
		if((*heap)[index]>(*heap)[index/2])
			swap((*heap)[index], (*heap)[index/2]);
		else
			break;
		index/=2;
	}
}
void Heap::SiftDown(int index)
{
	int next_index=index;
	if(2*index<=size&&(*heap)[2*index]>(*heap)[next_index])
		next_index=2*index;
	if(2*index+1<=size&&(*heap)[2*index+1]>(*heap)[next_index])
		next_index=2*index+1;
	if(next_index!=index)
	{
		swap((*heap)[index], (*heap)[next_index]);
		SiftDown(next_index);
	}
}
void Heap::Push(int value)
{
	++size;
	heap->push_back(value);
	SiftUp(size);
}
int Heap::Top()
{
	return (*heap)[1];
}
void Heap::Pop()
{
	(*heap)[1]=(*heap)[size];
	heap->pop_back();
	--size;
	SiftDown(1);
}
void Heap::HeapSort()
{
	while(size)
	{
		swap((*heap)[1], (*heap)[size]);
		--size;
		SiftDown(1);
	}
	size=heap->size()-1;
}
bool IsSorted(vector <int> &array)
{
	for(int i=2; i<array.size(); ++i)
		if(array[i-1]>array[i])
			return false;
	return true;
}
int main()
{
	int n;
	cin>>n;
	vector <int> array(n+1);
	Heap heap1;
	for(int i=1; i<=n; ++i)
	{
		cin>>array[i];
		heap1.Push(array[i]);
	}
	heap1.HeapSort();
	heap1.print();
	Heap heap2(array);
	heap2.HeapSort();
	cout<<IsSorted(array);
	return 0;
}
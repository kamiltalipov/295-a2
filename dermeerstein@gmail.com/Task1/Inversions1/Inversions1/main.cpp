#include <iostream>
#include <crtdbg.h>
#include <assert.h>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MAX_SIZE = 10000;
const int MAX_VALUE = 2000000000;

class Array
{
public:
	Array(); // random
	Array(int n);
	~Array();
	void Add(int a);
	void Print();
	int Size();
	int InversionCount(int left, int right);

private:
	int* buffer;
	int* bufferCopy;
	int size;
	int allocatedSize;
	
	void merge(int left, int middle, int right, int &inversions);
	void mergeSortCount(int left, int right, int &inversions);
	void bubbleSortCount(int left, int right, int &inversions);

};


Array::Array()
{
	srand(time(NULL));
	allocatedSize = rand() % MAX_SIZE;
	buffer = new int[allocatedSize];
	size = allocatedSize;
	for (int i = 0; i < size; i++)
	{
		buffer[i] = rand() % MAX_VALUE * ((rand() % 2) ? -1 : 1);
	}
}

Array::Array(int n)
{
	allocatedSize = n;
	buffer = new int[allocatedSize];
	size = 0;
}

Array::~Array()
{
	delete[] buffer;
}

void Array::Add(int a)
{
	buffer[size++] = a;
}

void Array::Print()
{
	for (int i = 0; i < size; i++)
	{
		cout << buffer[i] << " ";
	}
	cout << endl;
}

int Array::Size()
{
	return size;
}

void Array::merge(int left, int middle, int right, int &inversions) // [left; middle) [middle; right)
{
	int* ext = new int[middle - left];
	for (int i = 0; i < middle - left; i++)
	{
		ext[i] = bufferCopy[left + i];
	}

	int j = 0, k = middle;
	for (int i = left; i < right; i++)
	{
		if ((j < middle - left) && (k < right))
		{
			if (ext[j] <= bufferCopy[k])
			{
				bufferCopy[i] = ext[j];
				++j;
			}
			else
			{
				bufferCopy[i] = bufferCopy[k];
				++k;
				inversions += middle - left - j;
			}
		}
		else if (j < middle - left)
		{
			bufferCopy[i] = ext[j];
			++j;
		}
		else
		{
			bufferCopy[i] = bufferCopy[k];
			++k;
		}
	}
	delete[] ext;
}

void Array::mergeSortCount(int left, int right, int &inversions) // [left; right)
{
	if (right - left > 1)
	{
		int middle = (left + right) / 2;
		mergeSortCount(left, middle, inversions);
		mergeSortCount(middle, right, inversions);
		merge(left, middle, right, inversions);
	}
}

void Array::bubbleSortCount(int left, int right, int &inversions)
{
	for (int i = left; i < right; i++)
	{
		for (int j = right - 1; j > 0; j--)
		{
			if (bufferCopy[j] < bufferCopy[j - 1])
			{
				swap(bufferCopy[j], bufferCopy[j - 1]);
				inversions++;
			}
		}
	}
}

int Array::InversionCount(int left, int right)
{
	int count1 = 0, count2 = 0;
	bufferCopy = new int[right - left];
	for (int i = left; i < right; i++)
	{
		bufferCopy[i] = buffer[i];
	}
	mergeSortCount(left, right, count1);

	for (int i = left; i < right; i++)
	{
		bufferCopy[i] = buffer[i];
	}
	bubbleSortCount(left, right, count2);
	delete[] bufferCopy;
	assert(count1 == count2);
	return count1;
}

int main()
{
	{
		int n, a;
		cin >> n;
		Array ourArray(n);
		for (int i = 0; i < n; i++)
		{
			cin >> a;
			ourArray.Add(a);
		}
		/*Array ourArray;*/
		cout << ourArray.InversionCount(0, ourArray.Size()) << endl;
	}
	_CrtDumpMemoryLeaks();
	return 0;
}
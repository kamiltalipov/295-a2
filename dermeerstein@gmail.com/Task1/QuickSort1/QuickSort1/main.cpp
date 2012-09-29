#include <iostream>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <crtdbg.h>
#include <assert.h>

using namespace std;

const int MAX_SIZE = 10000;
const int MAX_VALUE = 2000000000;

class Array
{
public:
	Array();
	Array(int n);
	~Array();
	void Add(int a);
	void Print(); 
	int Size();
	void QuickSort(int left, int right);
	void QuickSortNonrecursive(int left, int right);
	int NthElement(int left, int right, int n);
	
private:
	int* buffer;
	int allocatedSize;
	int size;

	int partition(int left, int right);
	void quickSort(int left, int right);
	int nthElement(int left, int right, int n);
	bool isSorted(int left, int right);
	bool check_nthElement(int left, int right, int n, int number);
};

Array::Array()
{
	srand(time(NULL));
	allocatedSize = 1 + rand() % MAX_SIZE;
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

int Array::partition(int left, int right)
{
	srand(time(NULL));
	int k = left + rand() % (right - left);
	int x = buffer[k];
	swap(buffer[k], buffer[right - 1]);
	int i = left - 1;
	for (int j = left; j < right - 1; j++)
	{
		if (buffer[j] <= x)
		{
			i++;
			swap(buffer[i], buffer[j]);
		}
	}
	swap(buffer[i + 1], buffer[right - 1]);
	return i + 1;
}

void Array::quickSort(int left, int right)
{
	if (right - left > 1)
	{
		int m;
		m = partition(left, right);
		quickSort(left, m);
		quickSort(m + 1, right);
	}
}

void Array::QuickSort(int left, int right)
{
	quickSort(left, right);
	assert(isSorted(left, right));
}

void Array::QuickSortNonrecursive(int left, int right)
{
	struct Segment
	{
		int left, right;
	};

	stack<Segment> st;
	Segment init, first, second;
	int m;
	init.left = left;
	init.right = right;
	st.push(init);
	while (!st.empty())
	{
		init = st.top();
		st.pop();
		m = partition(init.left, init.right);
		first.left = init.left;
		first.right = m;
		second.left = m + 1;
		second.right = init.right;
		if (first.right - first.left > second.right - second.left)
		{
			if (first.right - first.left > 1)
				st.push(first);
			if (second.right - second.left > 1)
				st.push(second);
		}
		else
		{
			if (second.right - second.left > 1)
				st.push(second);
			if (first.right - first.left > 1)
				st.push(first);
		}
	}
}


int Array::nthElement(int left, int right, int n) // n in [0, right)
{
	if (right - left > 1)
	{
		int m;
		m = partition(left, right);
		if (n < m)
			return nthElement(left, m, n);
		else if(n == m)
			return buffer[n];
		else
			return nthElement(m + 1, right, n);
	}
	else
		return buffer[left];
}

int Array::NthElement(int left, int right, int n)
{
	int result = nthElement(left, right, n);
	//assert(check_nthElement(left, right, n, result));
	return result;
}

bool Array::isSorted(int left, int right)
{
	bool res = 1;
	for (int i = left; i < right - 1; i++)
	{
		res = res && (buffer[i] <= buffer[i + 1]);
	}
	return res;
}

bool Array::check_nthElement(int left, int right, int n, int number)
{
	QuickSort(left, right);
	return (buffer[n] == number);
}

int main()
{
	{
		int n, a, k;

		/*cin >> n;
		Array ourArray(n);
		for (int i = 0; i < n; i++)
		{
			cin >> a;
			ourArray.Add(a);
		}*/

		Array ourArray;
		//ourArray.QuickSort(0, ourArray.Size());
		//ourArray.QuickSortNonrecursive(0, ourArray.Size());
		//ourArray.Print();

		/*cin >> k;
		k--;
		cout << ourArray.NthElement(0, ourArray.Size(), k);*/

		k = rand() % ourArray.Size();
		ourArray.NthElement(0, ourArray.Size(), k);
		
	}
	_CrtDumpMemoryLeaks();
	return 0;
}
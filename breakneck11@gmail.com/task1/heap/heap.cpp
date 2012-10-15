#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
using namespace std;

class heap
{
private:
	vector < int > *arr;
	inline void up_el(int el);
	inline void down_el(int el);
	inline int next_for_down(int el);
public:
	int size() { return arr->size(); }
	heap() : arr(new vector < int >()) {}
	heap(vector < int > *arr) : arr(arr)
	{
		for (int i = arr->size() - 1; i >= 0; down_el(i--));
	}
	inline void add(int new_el);
	int min_el() { assert(size()); return (*arr)[0]; }
	inline int del_min();
	inline heap(const heap& h) { *arr = *(h.arr); }
	inline void operator= (const heap& h) { *arr = *(h.arr); }
};

inline void heap::up_el(int el)
{
	for (; el && (*arr)[el] < (*arr)[(el - 1) >> 1]; el = (el - 1) >> 1)
		swap((*arr)[el], (*arr)[(el - 1) >> 1]);
}

inline int heap::next_for_down(int el)
{
	int to = el;
	if ((el << 1) + 1 < size() && (*arr)[el] > (*arr)[(el << 1) + 1])
		to = (el << 1) + 1;
	if ((el << 1) + 2 < size() && (*arr)[(el << 1) + 1] > (*arr)[(el << 1) + 2])
		to = (el << 1) + 2;
	return to;
}

inline void heap::down_el(int el)
{
	for (int to; (to = next_for_down(el)) != el; el = to)
	{
		swap((*arr)[el], (*arr)[to]);
	}
}

inline void heap::add(int new_el)
{
	(*arr).push_back(new_el);
	up_el(size() - 1);
}

inline int heap::del_min()
{
	int res = min_el();
	swap((*arr)[0], (*arr)[size() - 1]);
	arr->pop_back();
	down_el(0);
	return res;
}

inline bool is_sorted(const vector < int > &arr)
{
	int size = arr.size();
	if (size < 2) return true;
	for (int i = 1; i < size; ++i)
		if (arr[i] < arr[i - 1])
			return false;
	return true;
}

vector < int > arr;

heap mheap;

int main()
{
	for (int i = 0; i < 10; ++i)
		arr.push_back(i);
	random_shuffle(arr.begin(), arr.end());
	mheap = heap(&arr);
	for (int i = 0, sz = mheap.size(); i < sz; ++i)
	{
		cout << mheap.del_min() << endl;
	}
	system("pause");
	return 0;
}

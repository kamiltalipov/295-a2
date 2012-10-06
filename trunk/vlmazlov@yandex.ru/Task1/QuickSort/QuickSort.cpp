#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <stack>
#include <ctime>
#include <cassert>
using namespace std;

int* middle(int* a, int* b, int *c) { 
	if (*a < *b) {
		if (*b < *c) return b;
		else if (*a > *c) return a;
		else return c;
	} else {
		if (*a < *c) return a;
		else if (*b > *c) return b;
		else return c;
	}
}

int partition(int* arr, int l, int r) {
	int* p = middle(arr, arr + r - 1, arr + ((l + r) / 2)), x = *p;
	swap(*p, *(arr + r - 1));
	int i = l, j = r - 2;
	while (i < j) {
		if (*(arr + i) <= x) i++;
		else if (*(arr + j) > x) j--;
		else {
			swap(*(arr + i), *(arr + j));
			i++;
			j--;
		}
	}
	if (*(arr + i) < *(arr + r - 1)) {
		swap(*(arr + i + 1), *(arr + r - 1)); // i < r - 1 => i + 1 < r
		i++;
	}
	else swap(*(arr + r - 1), *(arr + i));
	return i;
}

void sort2(int* arr, int l, int r) {
	if (*(arr + l) > *(arr + r - 1)) swap(*(arr + l), *(arr + r - 1));
}

void recQuick_sort(int* arr, int l, int r) {
	if (l + 1 >= r) return;
	if (l + 2 == r) {
		sort2(arr, l, r);
		return;
	}
	int i = partition(arr, l, r);
	recQuick_sort(arr, l, i);
	recQuick_sort(arr, i, r);
}

void notRecQuick_sort(int* arr, int size) {
	stack <pair <int, int> > recCall;
	recCall.push(make_pair(0, size));
	int l, r, i;
	while (!recCall.empty()) {
		l = recCall.top().first;
		r = recCall.top().second;
		recCall.pop();
		if (l + 1 >= r) continue;
		if (l + 2 == r) {
			sort2(arr, l, r);
			continue;
		}
		int i = partition(arr, l, r);
		recCall.push(make_pair(l, i));
		recCall.push(make_pair(i, r));
	}
}

int nth_element(int* arr, int l, int r, int k) {
	if (l + 1 >= r) return *(arr + l);
	if (l + 2 == r) {
		if (k == 1) return *(arr + l);
		if (k == 2) return *(arr + l + 1);
	}
	int i = partition(arr, l, r);
	if (i - l >= k) return nth_element(arr, l, i, k);
	else return nth_element(arr, i, r, k - i + l);
}

bool is_sorted(int* arr, int size) {
	for (int i = 0;i < size - 1;++i) {
		if (*(arr + i) > *(arr + i + 1)) return false; 
	}
	return true;
}

int main() {
	freopen("input.txt", "r", stdin);
	srand(time(NULL));
	int n;
	
	cin >> n;
	int* arr = new int[n];
	for (int i = 0;i < n;i++) cin >> arr[i];	
	
	random_shuffle(arr, arr + n);
	recQuick_sort(arr, 0, n);// recursive quicksort
	if (is_sorted(arr, n)) cout << "sorted(recursive):" << endl;
	else cout << "error(recursive):" << endl;
	for (int i = 0;i < n;i++) cout << *(arr + i) << " ";  
	cout << endl;
	
	random_shuffle(arr, arr + n);
	for (int i = 0;i < n;i++) cout << *(arr + i) << " ";
	cout << endl;
	
	notRecQuick_sort(arr, n); // not recursive quicksort
	if (is_sorted(arr, n)) cout << "sorted(not recursive):" << endl;
	else cout << "error(not recursive):" << endl;
	for (int i = 0;i < n;i++) cout << *(arr + i) << " ";
	cout << endl;
	
	random_shuffle(arr, arr + n);
	for (int i = 0;i < n;i++) cout << *(arr + i) << " ";
	cout << endl;
	
	int k = (rand() % n) + 1; //nth_element
	cout << k << endl;
	cout << nth_element(arr, 0, n, k) << endl;
	delete arr;
	return 0;
}
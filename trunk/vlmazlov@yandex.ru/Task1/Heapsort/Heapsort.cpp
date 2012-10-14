#include <iostream>
#include <vector>
#include <deque>
#include <limits>
using namespace std;

const int INF = numeric_limits <int>::min();

class heap {
private:
	int left(int pos);
	int right(int pos);
	int left_pos(int pos);
	int right_pos(int pos);
	void siftDown(int pos);
	void siftUp(int pos);
	vector <int> buffer;
	int externalArraySize;
	int* externalArray;
	void buildHeap(int* arr, int size);
public:
	heap();
	void heapsort(int* arr, int size);
	void add(int new_element);
	void pop();
	int top();
};

heap::heap() {
	externalArraySize = 0;
	externalArray = 0;
}

int heap::left_pos(int pos) {
	if (2 * pos + 1 >= externalArraySize) return -1;
	else return 2 * pos + 1;
}

int heap::right_pos(int pos) {
	if (2 * pos + 2 >= externalArraySize) return -1;
	else return 2 * pos + 2;
}
int heap::left(int pos) {
	if (left_pos(pos) == -1) return INF;
	else return *(externalArray + left_pos(pos));
}

int heap::right(int pos) {
	if (right_pos(pos) == -1) return INF;
	else return *(externalArray + right_pos(pos));
}

void heap::siftUp(int pos) {
	int parent;
	while (pos != 0) {
		parent = (pos - 1) / 2;
		if (buffer[pos] > buffer[parent]) {
			swap(buffer[pos], buffer[parent]);
			pos = parent;
		} else break;
	}
}

void heap::add(int new_element) {
	buffer.push_back(new_element);
	siftUp(buffer.size() - 1);
}

int heap::top() {
	return buffer[0];
}

void heap::siftDown(int pos) {
	while ((left_pos(pos) != -1) || (right_pos(pos) != -1)) {
		if (right(pos) > left(pos)) {
			if (right(pos) > *(externalArray + pos)) {
				swap(*(externalArray + pos), *(externalArray + right_pos(pos)));
				pos = right_pos(pos);
			} else return;
		} else {
			if (left(pos) > *(externalArray + pos)) {
				swap(*(externalArray + pos), *(externalArray + left_pos(pos)));
				pos = left_pos(pos);
			} else return;
		}
	}
}

void heap::buildHeap(int* arr, int size) { 
	externalArraySize = size;
	externalArray = arr;
	for (int i = size / 2;i >= 0;i--) siftDown(i);
}

void heap::heapsort(int* arr, int size) {
	buildHeap(arr, size);
	for (int i = 0;i < size;i++) {
		siftDown(0);
		swap(*(arr), *(arr + externalArraySize - 1));
		externalArraySize--;
	}
}
 
bool is_sorted(int* arr, int size) {
	for (int i = 0;i < size - 1;i++) {
		if (*(arr + i) > *(arr + i + 1)) return false;
	}
	return true;
}

int main() {
	//freopen("input.txt", "r", stdin);
	int n;
	cin >> n;
	int* arr = new int[n];
	heap* h = new heap;
	for (int i = 0; i < n;i++) {
		cin >> arr[i];
		h->add(arr[i]);
	}
	h->heapsort(arr, n);
	if (is_sorted(arr, n)) {
		cout << "sorted:" << endl;
	} else cout << "error:" << endl;
	for (int i = 0;i < n;i++) cout << arr[i] << " ";
	cout << endl;
	delete arr;
	delete h;
	return 0;
}
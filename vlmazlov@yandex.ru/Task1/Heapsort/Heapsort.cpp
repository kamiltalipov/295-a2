#include <iostream>
#include <vector>
using namespace std;

class heap {
public:
	heap();
	int left(int pos);
	int right(int pos);
	void siftDown(int pos);
	void buildHeap(int* arr, int size);
	void insert(int new_element);
	vector <int> buffer;
	void heapsort(int* arr, int size);
};

heap::heap() {
	buffer.push_back(0); // Проще всего нумеровать элементы с 1, buffer[0] равен 0 для определенности 
}

int heap::left(int pos) {
	if (2 * pos >= buffer.size()) return 0;
	else return 2 * pos;
}

int heap::right(int pos) {
	if (2 * pos + 1 >= buffer.size()) return 0;
	else return 2 * pos + 1;
}

void heap::siftDown(int pos) {
	while (left(pos) || right(pos)) {
		if (left(pos) && right(pos) && ((buffer[pos] >= buffer[left(pos)]) && (buffer[pos] >= buffer[right(pos)]))) return;
		if (!left(pos) && (buffer[pos] >= buffer[right(pos)])) return;
		if (!right(pos) && (buffer[pos] >= buffer[left(pos)])) return;
		if ((buffer[left(pos)] < buffer[right(pos)]) || !left(pos)) {
			swap(buffer[pos], buffer[right(pos)]);
			pos = right(pos);
		} else {
			swap(buffer[pos], buffer[left(pos)]);
			pos = left(pos);
		}
	}
}

void heap::buildHeap(int* arr, int size) { 
	for (int i = 0;i < size;i++) buffer.push_back(*(arr + i));
	for (int i = buffer.size() / 2;i >= 1;i--) siftDown(i);
}

void heap::heapsort(int*  arr, int size) {
	buildHeap(arr, size);
	for (int i = 0;i < size;i++) {
		siftDown(1);
		swap(buffer[1], buffer[buffer.size() - 1]);
		*(arr + size - 1 - i) = buffer[buffer.size() - 1];
		buffer.pop_back();
	}
}
 
bool is_sorted(int* arr, int size) {
	for (int i = 0;i < size - 1;i++) {
		if (*(arr + i) > *(arr + i + 1)) return false;
	}
	return true;
}

int main() {
	freopen("input.txt", "r", stdin);
	int n;
	cin >> n;
	int* arr = new int[n];
	for (int i = 0; i < n;i++) cin >> arr[i];
	heap h;
	h.heapsort(arr, n);
	if (is_sorted(arr, n)) {
		cout << "sorted:" << endl;
	} else cout << "error:" << endl;
	for (int i = 0;i < n;i++) cout << arr[i] << " ";
	cout << endl;
	return 0;
}
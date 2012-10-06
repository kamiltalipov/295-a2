#include <iostream>
using namespace std;

typedef int* pArr;  
int inverse = 0;

int bubbleCount(int* v, int vsize) { //Подсчет кол-ва инверсий пузырьком
	int inv = 0;
	for (int i = 0;i < vsize;i++) {
		for (int j = i;j < vsize;j++) {
			if (v[i] > v[j]) {
				swap(v[i], v[j]);
				inv++;
			}
		}
	}
	return inv;
}

int* merge(int* v1, int* v2, int v1size, int v2size) { 
	int* res = new int[v1size + v2size];	
	int i1 = 0, i2 = 0, j = 0;
	while (i1 < v1size || i2 < v2size) {
		if (i1 >= v1size) {
			for (int i = i2;i < v2size;i++) {
				res[j] = v2[i];
				j++;
			}
			break;
		}
		if (i2 >= v2size) {
			for (int i = i1;i < v1size;i++) {
				res[j] = v1[i];
				j++;
			}
			break;
		}
		if (v1[i1] < v2[i2]) {
			res[j] = v1[i1];
			i1++;
		} else {
			res[j] = v2[i2];
			i2++;
			inverse += v1size - i1;
		}
		j++;
	}
	return res; 
}

void mergeSort(int* v, int vsize) {
	int b = 1, p, e; // Размер первого блока (b), размер второго блока (e)  
	while (b < vsize) {
		p = 0; //Начало очередного блока (p) 
		while (p + b < vsize) { 
			if (p + (b * 2) < vsize) {
				e = b;
			} else {
				e = vsize - (p + b);
			}
			int* tmp = merge(v + p, v + p + b, b, e);  
			for (int i = 0;i < b + e;i++) v[p + i] = tmp[i];
			delete tmp;
			p += 2 * b;
		}
		b *= 2;
	}
}

int main() {
	int n;
	cin >> n;
	int* v = new int[n];
	int* g = new int[n];
	int k;
	for (int i = 0;i < n;i++) {	
		cin >> k;
		v[i] = k;
		g[i] = k;
	}
	mergeSort(v, n);
	cout << inverse << endl;
	cout << bubbleCount(g, n) << endl;
	delete v;
	delete g;
	return 0;
}
#include <iostream>
#include <cassert>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <crtdbg.h>
#include <queue>


using namespace std;
int const MaxN = 10000;
int const MaxNumTests = 100;

class Array{
public:
	Array(int n);
	~Array();
	int KOrdinalStatic(int left, int right, int k);
	void QSort(int left, int right);
	void QSort2(); //нерекурсивный qsort
	void GenTests();
	void read();
	void write();
private:
	void partition(int left, int right, int& right_l, int& left_r);
	bool Check();
	int size;
	int* buffer;
};

Array::Array(int n){
	size = n;
	buffer = new int[size];
}

Array::~Array(){
	delete [] buffer;
}

bool Array::Check(){
	for (int i = 0; i < size - 1; i++){
		if (buffer[i] > buffer[i + 1]){
			return false;
		}
	}
	return true;
}

void Array::read(){
	for (int i = 0; i < size; i++){
		cin >> buffer[i];
	}
}

void Array::write(){
	for (int i = 0; i < size; i++){
		cout << buffer[i] << " ";
	}
	cout << endl << Check();
}

void Array::partition(int left, int right, int& right_l, int& left_r){
	int middle = buffer[(left + right)/2];
	left_r = left;
	right_l = right - 1;
	while (left_r <= right_l){
		if (buffer[left_r] < middle){
			left_r++;
		}
		else{
			if (buffer[right_l] > middle){
				right_l--;
			}
			else{
				swap(buffer[right_l], buffer[left_r]);
				right_l--;
				left_r++;
			}
		}
	}
}

int Array::KOrdinalStatic(int left, int right, int k){
	if (right - left <= 1){
		return buffer[left];
	}
	int right_l, left_r;
	partition(left, right, right_l, left_r);
	if ((left_r == right_l + 2)&&(k == right_l + 1)){
		return buffer[right_l + 1];
	}
	if (k >= left_r){
		return KOrdinalStatic(left_r, right, k);
	}
	else{
		return KOrdinalStatic(left, right_l + 1, k);
	}
}

void Array::QSort(int left, int right){
	if (right - left <= 1){
		return;
	}
	int right_l, left_r;
	partition(left, right, right_l, left_r);
	if	(left_r < right){
		QSort(left_r, right);
	}
	if (left < right_l){
		QSort(left, right_l + 1);
	}
}

void Array::QSort2(){
	queue<int>left;
	queue<int>right;
	left.push(0);
	right.push(size);

	int i = 0;

	while (left.size() > 0){
		int right_l, left_r;
		partition(left.front(), right.front(), right_l, left_r);

		if (left_r < right.front()){
			left.push(left_r);
			right.push(right.front());
		}
		if (left.front() < right_l){
			left.push(left.front());
			right.push(right_l + 1);
		}

		left.pop();
		right.pop();

	}

}

void Array::GenTests(){
	srand(time(NULL));
	Array tmp(MaxN);
	for (int k = 0; k < MaxNumTests; k++){
		for (int i = 0; i < size; i++){
			buffer[i] = rand();
			tmp.buffer[i] = buffer[i];
		}
		QSort(0, size);
		if (!Check()){
			/*for (int i = 0; i < size; i++){
				cout << tmp.buffer[i] << " ";
			}*/
			cout << k << endl;
		}
	}
}

int main( void ){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);

	//Array ourArray(MaxN);
	//ourArray.GenTests();
	
	int n, k;
	cin >> n >> k;

	Array ourArray(n);
	
	ourArray.read();
	ourArray.QSort2();
	//ourArray.QSort(0, n);
	ourArray.write();
	//cout << ourArray.KOrdinalStatic(0, n, k);
	return 0;
}
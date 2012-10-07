#include <cstdio>
#include <iostream>
#include <crtdbg.h>
#include <cassert>
#include <ctime>
#include <cstdlib>

using namespace std;

const int Maxn = 1000, MaxNumTests = 100;

class Array{
public:
	Array(int n);
	~Array();
//	void Add( int a );
	int MergeSort(int l, int r);
	int BubbleSort();
	int& operator[](int i){return buffer[i];};
	int GetSize() {return size;}
	void read();
	void compareInv();
private:
	int Merge(int l, int r);
	int* buffer;
	int size;
};

Array::Array(int n)
{
	size = n;
	buffer = new int[n];
}

Array::~Array(){
	delete [] buffer;
}

void Array::compareInv(){
	Array tmp(size);
	for (int i = 0; i < size; i++){
		tmp[i] = buffer[i];
	}
	int answer1 = MergeSort(0, size - 1);
	for (int i = 0; i < size; i++){
		buffer[i] = tmp[i];
	}
	int answer2 = BubbleSort();
	if (answer1 != answer2){
		cout << "Fail" << endl << size << endl;
		for (int i = 0; i < size; i++){
			cout << tmp[i] << " ";
		}
		cout << endl << "MergeSort answer = " << answer1 << "BubbleSort answer = " << answer2 << endl;
	}
	else{
		cout << "OK" << endl;
	}
	
}

void Array::read(){
	for (int i = 0; i < size; i++){
		cin >> buffer[i];
	}
}

int Array::Merge(int left, int right ){
	int middle = (left + right)/2;
	Array tmp(middle - left + 1);
	for (int i = left; i <= middle; i++){
		tmp[i - left] = buffer[i];
	}
	int cur = 0;

	int ind1 = left, ind2 = middle + 1;
	for (int i = left; i <= right; i++){
		if (ind1 > middle){
			buffer[i] = buffer[ind2];
			ind2++;
		}
		else{
			if (ind2 > right){
				buffer[i] = tmp[ind1 - left];
				ind1++;
			}
			else{
				if (tmp[ind1 - left] <= buffer[ind2]){
					buffer[i] = tmp[ind1 - left];
					ind1++;
				}
				else{
					buffer[i] = buffer[ind2];
					ind2++;
					cur += (middle - ind1 + 1);
				}
			}
		}
	}
	
	
	return cur;
}

int Array::MergeSort( int left, int right ){
	if (right - left == 0){  
		return 0;
	}
	int middle = (left + right)/2;
	int res = MergeSort(left, middle) + MergeSort(middle + 1, right);
	return (res + Merge(left, right));
}

int Array::BubbleSort(){
	int cur = 0;
	for (int i = 0; i < size; i++){
		for (int j = 0; j < size - 1; j++){
			if (buffer[j] > buffer[j + 1]){
				cur++;
				swap(buffer[j], buffer[j + 1]);
			}
		}
	}
	return cur;
}

void GenTests(){
	srand(time(NULL));
	Array ourArray(Maxn);
	for (int NumTests = 0; NumTests < MaxNumTests; NumTests++){
		
		for (int i = 0; i < Maxn; i++){
			ourArray[i] = rand();
		}

		ourArray.compareInv();
	}
}

int main(void){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
//	GenTests();
	int n;
	cin >> n;
	Array ourArray(n);
	ourArray.read();
	ourArray.compareInv();
	//_CrtDumpMemoryLeaks();
	return 0;
}
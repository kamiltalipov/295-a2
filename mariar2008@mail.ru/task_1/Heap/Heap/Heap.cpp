#include<vector>
#include<cstdio>
#include<stdio.h>
#include<ctime>
#include<cstdlib>
#include<iostream>

using namespace std;

class Heap{
public:
	Heap(int n);
	Heap(vector<int>&Array);
	void read();
	void write();
	void sort();
private:
	bool Check();
	void PushDown(int ind);
	void PushUp(int ind);
	void DoHeap();
	void DeleteMin();
	vector<int>ourArray;
	vector<int>&link;
	int size;
};

Heap::Heap(int n):link (ourArray)
{
	ourArray.resize(n);
	size = n;
}

Heap::Heap(vector<int>&Array):link (Array){
	size = link.size();
}

void Heap::read(){
	for (int i = 0; i < link.size(); i++){
		cin >> link[i];
	}
}

void Heap::write(){
	if (!Check()){
		cout << "FAIL" << endl;
	}
	for (int i = link.size() - 1; i >= 0; i--){
		cout << link[i] << " ";
	}
}

bool Heap::Check(){
	for (int i = link.size() - 1; i > 0; i--){
		if (link[i] > link[i - 1]){
			return false;
		}
	}
	return true;
}

void Heap::PushUp(int ind){
	int i = ind;
	while (i > 0){
			if (link[i] < link[(i - 1)/2]){
			swap(link[i], link[(i - 1)/2]);
		}
		i = (i - 1)/2;
	}
}

void Heap::PushDown(int ind){
	int parent = ind, left = (ind + 1)*2 - 1, right = (ind + 1)*2;
	while (right < size){
		if ((link[parent] > link[right])&&((link[parent] <= link[left])||(link[right] <= link[left]))){
			swap(link[parent], link[(parent + 1)*2]);
			parent = right;
			left = (parent + 1)*2 - 1;
			right = (parent + 1)*2;
		}
		else
			if ((link[parent] > link[left])&&((link[parent] <= link[right])||(left <= link[right]))){
				swap(link[parent], link[(parent + 1)*2 - 1]);
				parent = left;
				left = (parent + 1)*2 - 1;
				right = (parent + 1)*2;
			}
			else
				return;
	}
	if ((left < size)&&(link[parent] > link[left])){
		swap(link[parent], link[left]);
	}
}

void Heap::DoHeap(){
	for (int i = size - 1; i >= 0; i--){
		PushDown(i);
	}
}

void Heap::DeleteMin(){
	swap(link[0], link[size - 1]);
	size--;
	PushDown(0);
}

void Heap::sort(){
	DoHeap();
	for (int i = 0; i < link.size(); i++){
		DeleteMin();
	}
}

void HeapSortVector(int size){
	vector<int>ourArray(size);
	for (int i = 0; i < size; i++){
		cin >> ourArray[i];
	}
	Heap ourHeap(ourArray);
	ourHeap.sort();
	ourHeap.write();
}
void HeapSort(int size){
	Heap ourHeap(size);
	ourHeap.read();
	ourHeap.sort();
	ourHeap.write();
}

int main( void ){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int size;
	cin >> size;
	//HeapSortVector(size);
	HeapSort(size);
	return 0;
}

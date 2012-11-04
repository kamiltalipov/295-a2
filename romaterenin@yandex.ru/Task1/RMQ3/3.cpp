#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Heap{
public:
	//vector <int> tree;
	Heap() { }

	void heapify (vector<int> &Array,int pos, int size){
		while (2 * pos + 1 < size /*tree.size()*/){
			int t = 2 * pos +1;
			if (2 * pos + 2 < size /*tree.size()*/ && Array[2 * pos + 2] >= Array[t])
				t = 2 * pos + 2;
			if (Array[pos] < Array[t]) {
				swap(Array[pos], Array[t]);
				pos = t;
			} 
			else break;
		}
	}

	void heap_make(vector <int> &Array, int size){
		for (int i =size-1; i>=0; i--)
			heapify(Array,i,size);
	}
	void heap_sort(vector <int> &Array, int size){
		//tree = Array;
		heap_make(Array,size);
		//int n = tree.size();
		while(size>0){
			//Array[size-1] = tree[0];
			size--;
			swap(Array[0],Array[size]);
			//tree.pop_back();
			heapify(Array,0,size);
		}
	}
};

void read_Array (vector <int> &Array){
	int size;
	cin>>size;
	Array.resize(size);
	for(int i=0;i<size;i++)
		cin>>Array[i];
}
void random_Array(vector <int> &Array){
	int size;
	cin>>size;
	Array.resize(size);
	for(int i=0;i<size;i++)
		Array[i]=rand();
}
bool check(vector <int> &Array){
	for(int i=0;i<Array.size()-1;i++)
		if(Array[i]>Array[i+1])
			return false;
	return true;
}
void write_Array(vector <int> &Array, int size){
	for(int i=0;i<size;i++){
		cout<<Array[i];
		if(i!=size-1)
			cout<<' ';
	}
}
int main(){
	vector <int> sort_Array;
	//read_Array(sort_Array);
	random_Array(sort_Array);
	Heap heap;
	heap.heap_sort(sort_Array,sort_Array.size());
	//write_Array(sort_Array,sort_Array.size());
	//cout<<endl;
	if(check(sort_Array))
		cout<<"Correct";
	else
		cout<<"Uncorrect";
	cout<<endl;
	return 0;
}
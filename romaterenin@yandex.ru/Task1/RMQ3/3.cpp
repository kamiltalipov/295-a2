#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Heap{
public:
	vector <int> tree;
	Heap() { }

	void heapify (int pos){
		while (2 * pos + 1 < tree.size()){
			int t = 2 * pos +1;
			if (2 * pos + 2 < tree.size() && tree[2 * pos + 2] >= tree[t])
				t = 2 * pos + 2;
			if (tree[pos] < tree[t]) {
				swap(tree[pos], tree[t]);
				pos = t;
			} 
			else break;
		}
	}

	void heap_make(){
		for (int i =(int)tree.size()-1; i>=0; i--)
			heapify(i);
	}
	void heap_sort(vector <int> &Array){
		tree = Array;
		heap_make();
		int n = tree.size();
		while(n>0){
			Array[n-1] = tree[0];
			swap(tree[0],tree[n-1]);
			n--;
			tree.pop_back();
			heapify(0);
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
	heap.heap_sort(sort_Array);
	//write_Array(sort_Array,sort_Array.size());
	cout<<endl;
	if(check(sort_Array))
		cout<<"Correct";
	else
		cout<<"Uncorrect";
	return 0;
}
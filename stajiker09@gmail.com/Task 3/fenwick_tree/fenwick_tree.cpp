#include <iostream>
#include <vector>
using namespace std;
class fenwick_tree
{
public:
	fenwick_tree(int Size)
	{
		size=Size;
		buffer=new int[size];
		for(int i=0; i<size; ++i)
			buffer[i]=0;
	}
	~fenwick_tree()
	{
		delete[] buffer;
	}
	int sum(int left, int right)
	{
		return sum(right)-sum(left-1);
	}
	void update(int index, int delta)
	{
		while(index<size)
		{
			buffer[index]+=delta;
			index=index|(index+1);
		}
	}
private:
	int *buffer;
	int size;
	int sum(int right)
	{
		int result=0;
		while(right>=0)
		{
			result+=buffer[right];
			right=(right&(right+1))-1;
		}
		return result;
	}
};
int main()
{
	int n;
	cin>>n;
	vector <int> array(n);
	for(int i=0; i<n; ++i)
		cin>>array[i];
	fenwick_tree tree(array.size()+1);
	int inversions=0;
	for(int i=0; i<n; ++i)
	{
		inversions+=tree.sum(array[i]+1, n);
		tree.update(array[i], 1);
	}
	cout<<inversions;
}
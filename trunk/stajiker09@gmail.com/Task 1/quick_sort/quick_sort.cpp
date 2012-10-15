#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;
int partition(vector <int> &array, int left, int right)
{
	int pivot=array[right-1];
	int i=left, j=right-2;
	while(i<=j)
	{
		while(array[i]<pivot)
			++i;
		while(j>=0&&array[j]>=pivot)
			--j;
		if(i<=j)
		{
			swap(array[i], array[j]);
			++i, --j;
		}
	}
	return i;
}
void quick_sort_recursive(vector <int> &array, int left, int right)
{
	int middle=partition(array, left, right);
	swap(array[middle], array[right-1]);
	if(left<middle-1)
		quick_sort_recursive(array, left, middle);
	if(middle+1<right-1)
		quick_sort_recursive(array, middle+1, right);
}
void quick_sort_nonrecursive(vector <int> &array, int left, int right)
{
	stack < pair<int, int> > Stack;
	Stack.push(make_pair(left, right));
	while(Stack.size()!=0)
	{
		left=Stack.top().first, right=Stack.top().second;
		Stack.pop();
		int middle=partition(array, left, right);
		swap(array[middle], array[right-1]);
		if(left<middle-1)
			Stack.push(make_pair(left, middle));
		if(middle+1<right-1)
			Stack.push(make_pair(middle+1, right));
	}
}
int nth_element(vector <int> &array, int position, int left, int right)
{
	swap(array[position], array[right-1]);
	int new_position=partition(array, left, right);
	return new_position;
}
int main()
{
	int n;
	cin>>n;
	vector <int> array(n), array1, array2;
	for(int i=0; i<n; ++i)
		cin>>array[i];
	array1=array;
	array2=array;
	quick_sort_recursive(array, 0, n);
	for(int i=0; i<n; ++i)
		cout<<array[i]<<' ';
	cout<<endl;
	quick_sort_nonrecursive(array1, 0, n);
	for(int i=0; i<n; ++i)
		cout<<array1[i]<<' ';
	cout<<endl;
	cout<<nth_element(array2, 0, 0, n)+1;
	return 0;
}
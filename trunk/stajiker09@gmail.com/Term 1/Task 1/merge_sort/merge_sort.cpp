#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
void merge(vector <int> &array, int left, int right, int &inversions)
{
	vector <int> result(right-left);
	int middle=(left+right)/2, i=left, j=middle;
	while(i!=middle||j!=right)
		if(i==middle||j!=right&&array[i]>array[j])
			result[i-left+j-middle]=array[j], ++j, inversions+=middle-i;
		else
			result[i-left+j-middle]=array[i], ++i;
	for(int i=left; i<right; ++i)
		array[i]=result[i-left];
}
void merge_sort(vector <int> &array, int left, int right, int &inversions)
{
	int middle=(left+right)/2;
	if(middle-left>1)
		merge_sort(array, left, middle, inversions);
	if(right-middle>1)
		merge_sort(array, middle, right, inversions);
	merge(array, left, right, inversions);
}
void bubble_sort(vector <int> &array, int size, int &inversions)
{
	for(int j=1; j<size; ++j)
		for(int i=0; i<size-j; ++i)
			if(array[i]>array[i+1])
				swap(array[i], array[i+1]), inversions++;
}
int main()
{
	int n;
	cin>>n;
	vector <int> array(n), Array;
	for(int i=0; i<n; ++i)
		cin>>array[i];
	Array=array;
	int inversions_merge_sort=0, inversions_bubble_sort=0;
	merge_sort(array, 0, n, inversions_merge_sort);
	bubble_sort(Array, n, inversions_bubble_sort);
	cout<<inversions_merge_sort<<' '<<inversions_bubble_sort;
	return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main()
{
	int n;
	cin>>n;
	vector <int> array(n), elements(n+1), last(n+1), parents(n);
	for(int i=0; i<n; ++i)
		cin>>array[i];
	elements[0]=numeric_limits<int>::min();
	for(int i=1; i<=n; ++i)
		elements[i]=numeric_limits<int>::max();
	parents[0]=-1;
	for(int i=0; i<n; ++i)
	{
		int j=lower_bound(elements.begin(), elements.end(), array[i])-elements.begin();
		if(elements[j]!=array[i])
		{
			elements[j]=array[i];
			last[j]=i;
			parents[i]=last[j-1];
		}
	}
	int length;
	for(int i=n; i>=0; --i)
		if(elements[i]!=(1<<31)-1)
		{
			length=i;
			break;
		}
	vector <int> answer;
	for(int i=0, index=last[length]; i<length; ++i, index=parents[index])
		answer.push_back(array[index]);
	cout<<length<<endl;
	for(int i=length-1; i>=0; --i)
		cout<<answer[i]<<' ';
	return 0;
}
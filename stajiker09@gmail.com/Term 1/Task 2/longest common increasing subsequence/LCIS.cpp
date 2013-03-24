#include <iostream>
#include <vector>
using namespace std;
int main()
{
	int n, m;
	cin>>n;
	vector <int> array_n(n);
	for(int i=0; i<n; ++i)
		cin>>array_n[i];
	cin>>m;
	vector <int> array_m(m);
	for(int i=0; i<m; ++i)
		cin>>array_m[i];
	vector <int> dp(m), previous(m);
	for(int i=0; i<n; ++i)
		for(int j=0, current=0, last=-1; j<m; ++j)
		{
			if(array_n[i]>array_m[j]&&dp[j]>current)
			{
				current=dp[j];
				last=j;
			}
			if(array_n[i]==array_m[j]&&current+1>dp[j])
			{
				dp[j]=current+1;
				previous[j]=last;
			}
		}
	int answer=0, index=-1;
	for(int i=0; i<m; ++i)
		if(dp[i]>answer)
		{
			answer=dp[i];
			index=i;
		}
	cout<<answer<<endl;
	vector <int> LCIS(answer);
	for(int i=answer-1; i>=0; --i)
	{
		LCIS[i]=array_m[index];
		index=previous[index];
	}
	for(int i=0; i<answer; ++i)
		cout<<LCIS[i]<<' ';
	return 0;
}
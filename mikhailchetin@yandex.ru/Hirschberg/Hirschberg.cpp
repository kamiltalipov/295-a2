#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;
int leftcolumn1[100],leftcolumn2[100],rightcolumn1[100],rightcolumn2[100],k;
string a,b;
vector<pair<int,int>> ans;
void ld(int left,int up,int right,int down)
{
	int mid=(left+right+1)/2;
	for(int i=up;i<=down;i++)
		leftcolumn1[i]=i-up;
	for(int j=left+1;j<=mid;j++)
	{
		leftcolumn2[up]=j-left;
		for(int i=up+1;i<=down;i++)
			leftcolumn2[i]=min(min(leftcolumn1[i]+1,leftcolumn2[i-1]+1),leftcolumn1[i-1]+(int)(a[i-1]!=b[j-1]));
		for(int i=up;i<=down;i++)
			leftcolumn1[i]=leftcolumn2[i];
	}

	for(int i=up;i<=down;i++)
		rightcolumn1[i]=down-i;
	for(int j=right-1;j>=mid;j--)
	{
		rightcolumn2[down]=right-j;
		for(int i=down-1;i>=up;i--)
				rightcolumn2[i]=min(min(rightcolumn1[i]+1,rightcolumn2[i+1]+1),rightcolumn1[i+1]+(int)(a[i]!=b[j]));
		for(int i=up;i<=down;i++)
			rightcolumn1[i]=rightcolumn2[i];
	}
	int minimum=rightcolumn1[up]+leftcolumn1[up];
	int imin=up;
	for(int i=up+1;i<=down;i++)
		if(rightcolumn1[i]+leftcolumn1[i]<minimum)
		{
			minimum=rightcolumn1[i]+leftcolumn1[i];
			imin=i;
		}
	ans.push_back(make_pair(mid,imin));
	if(mid!=right && imin!=down) ld(mid,imin,right,down);
	if(left!=mid && up!=imin) ld(left,up,mid,imin);
}

int main()
{
	cin>>a>>b;
	ld(0,0,b.length(),a.length());

	sort(ans.begin(),ans.end());

	vector<pair<int,int>>::iterator it;

	for(it=ans.begin();it!=ans.end();it++)
		cout<<it->first<<' '<<it->second<<endl;

	//cout<<ans[0].first<<' '<<ans[0].second;
	//cin>>a;
	return 0;
}
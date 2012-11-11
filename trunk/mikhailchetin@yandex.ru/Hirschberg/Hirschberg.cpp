#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;



void finld(int left,int up,int right,int down,vector<pair<int,int>> &ans,string &a,string &b)
{
	if(down-up>1)
	for(int i=up+1;i<down;i++)
		if(a[i-1]!=b[right])
			ans.push_back(make_pair(left,i));
		else
		{
			ans.push_back(make_pair(right,i));
			for(int j=i+1;j<down;j++)
				ans.push_back(make_pair(right,j));
			break;
		}
}

void ld(int left,int up,int right,int down,int *leftcolumn1,int *leftcolumn2,int *rightcolumn1,int *rightcolumn2,vector<pair<int,int>> &ans,string &a,string &b)
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
	if(mid<right-1) ld(mid,imin,right,down,leftcolumn1,leftcolumn2,rightcolumn1,rightcolumn2,ans,a,b);
	if(left<mid-1) ld(left,up,mid,imin,leftcolumn1,leftcolumn2,rightcolumn1,rightcolumn2,ans,a,b);
	if(mid==right-1) finld(mid,imin,right,down,ans,a,b);
	if(mid==left+1) finld(left,up,mid,imin,ans,a,b);
	
}

int main()
{
	int k;
	string a,b;
	cin>>a>>b;
	vector<pair<int,int>> ans;
	int *leftcolumn1=new int[a.length()+1];
	int *leftcolumn2=new int[a.length()+1];
	int *rightcolumn1=new int[a.length()+1];
	int *rightcolumn2=new int[a.length()+1];

	ld(0,0,b.length(),a.length(),leftcolumn1,leftcolumn2,rightcolumn1,rightcolumn2,ans,a,b);
	ans.push_back(make_pair(0,0));
	ans.push_back(make_pair(b.length(),a.length()));
	sort(ans.begin(),ans.end());

	vector<pair<int,int>>::iterator it;

	for(it=ans.begin();it!=ans.end();it++)
		cout<<it->first<<' '<<it->second<<endl;

	delete[] leftcolumn1;
	delete[] leftcolumn2;
	delete[] rightcolumn1;
	delete[] rightcolumn2;

	//cout<<ans[0].first<<' '<<ans[0].second;
	//cin>>a;
	return 0;
}
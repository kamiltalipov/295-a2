#include<iostream>
#include<string>
#include<vector>

using namespace std;

string getAns(int l,int r,string &s, vector<vector<string>> &d)
{
	if(l>r) return "";
	if(d[l][r]!="") return d[l][r];
	string s1=getAns(l+1,r,s,d);
	string s2=getAns(l,r-1,s,d);
	if(s1.length()>=s2.length())
		d[l][r]=s1;
	else
		d[l][r]=s2;
	if(s[l]==s[r])
	{
		string s3=s[l]+getAns(l+1,r-1,s,d)+s[r];
		if(s3.length()>d[l][r].length())
			d[l][r]=s3;
	}
	return d[l][r];
}

int main()
{
	string s;
	cin>>s;
	int n=s.length();
	vector<vector<string>> d(n);
	for(int i=0;i<n;i++)
		d[i].resize(n);

	for(int i=0;i<s.length();i++)
				d[i][i]=s[i];

	cout<<getAns(0,s.length()-1,s,d);
	return 0;
}
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main()
{
	string s;
	cin>>s;
	vector < vector <int> > d;
	d.resize(s.length()+1);
	for(int i=0; i<=s.length(); ++i)
	{
		d[i].resize(s.length()+1-i);
		for(int j=0; j<=s.length()-i; ++j)
			if(i==0)
				d[i][j]=0;
			else
				if(i==1)
					d[i][j]=1;
				else
				{
					d[i][j]=max(d[i-1][j], d[i-1][j+1]);
					if(s[j]==s[j+i-1])
						d[i][j]=max(d[i][j], d[i-2][j+1]+2);
				}
	}
	cout<<d[s.length()][0]<<endl;
	string answer;
	answer.resize(d[s.length()][0]);
	for(int i=s.length(), j=0, left=0, rigth=answer.size()-1; i!=0; --i)
		if(i==1)
			answer[left]=s[j];
		else
			if(s[j]==s[j+i-1]&&d[i][j]==d[i-2][j+1]+2)
			{
				answer[left]=s[j], answer[rigth]=s[j];
				++left, --rigth;
				--i, ++j;
			}
			else
				if(d[i][j]==d[i-1][j+1])
					++j;
	cout<<answer;
	return 0;
}
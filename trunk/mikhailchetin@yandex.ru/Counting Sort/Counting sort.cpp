#include<iostream>
#include<string>
#include<vector>

using namespace std;

struct student
{
	int number;
	string surname;
	int mark;
};
int main()
{
	int c[6];
	vector<student> a;
	for(int i=2;i<=5;i++)
		c[i]=0;
	student s;
	int n;
	cin>>n;
	vector<student> b(n);
	for(int i=1;i<=n;i++)
	{
		cin>>s.number;
		cin>>s.surname;
		cin>>s.mark;
		a.push_back(s);
		c[s.mark]++;
	}
	for(int i=3;i<=5;i++)
		c[i]+=c[i-1];

	for(int i=n-1;i>=0;i--)
	{
		c[a[i].mark]--;
		b[c[a[i].mark]]=a[i];
	}
	for(int i=0;i<b.size();i++)
		cout<<b[i].number<<' '<<b[i].surname<<' '<<b[i].mark<<endl;
	//cin>>n;
	return 0;
}
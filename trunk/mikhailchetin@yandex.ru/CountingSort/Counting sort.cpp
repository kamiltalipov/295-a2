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
	vector<student> a[6];
	student s;
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>s.number;
		cin>>s.surname;
		cin>>s.mark;
		a[s.mark].push_back(s);
	}
	vector<student>::iterator j;
	for(int i=2;i<=5;i++)
		for(j=a[i].begin();j<a[i].end();j++)
			cout<<j->number<<' '<<j->surname<<' '<<j->mark<<endl;

	return 0;
}
#include <iostream>
#include <string>
#include <vector>
using namespace std;
void forwards(string &m, string &n, int left_m, int right_m, int left_n, int right_n, int *edit_dist)
{
	for(int i=0; i<right_m-left_m+1; ++i)
		if(i==0)
			edit_dist[i]=m[left_m]==n[left_n]?0:1;
		else
			edit_dist[i]=edit_dist[i-1]+1;
	for(int j=left_n+1; j<=right_n; ++j)
		for(int i=left_m, last; i<=right_m; ++i)
			if(i==left_m)
			{
				last=edit_dist[0];
				edit_dist[0]=last+1;
			}
			else
			{
				last=min(last+(m[i]==n[j]?0:1), min(edit_dist[i-left_m-1], edit_dist[i-left_m])+1);
				swap(last, edit_dist[i-left_m]);
			}
}
void backwards(string &m, string &n, int left_m, int right_m, int left_n, int right_n, int *edit_dist)
{
	for(int i=right_m-left_m; i>=0; --i)
		if(i==right_m-left_m)
			edit_dist[i]=0;
		else
			edit_dist[i]=edit_dist[i+1]+1;
	for(int j=right_n-1; j>=left_n; --j)
		for(int i=right_m, last; i>=left_m; --i)
			if(i==right_m)
			{
				last=edit_dist[right_m-left_m];
				edit_dist[right_m-left_m]=last+1;
			}
			else
			{
				last=min(last+(m[i+1]==n[j+1]?0:1), min(edit_dist[i-left_m+1], edit_dist[i-left_m])+1);
				swap(last, edit_dist[i-left_m]);
			}
}
void Hirschberg_algorithm(string &m, string &n, int left_m, int right_m, int left_n, int right_n, vector < pair <int, int> > &edit_operations, int &leven_dist)
{
	if(right_n-left_n<2)
	{
		int edit_dist[100][100];
		for(int i=0; i<right_m-left_m+1; ++i)
			for(int j=0; j<right_n-left_n+1; ++j)
				if(i==0)
					edit_dist[i][j]=j;
				else
					if(j==0)
						edit_dist[i][j]=i;
					else
						edit_dist[i][j]=min(edit_dist[i-1][j-1]+(m[left_m+i]==n[left_n+j]?0:1), min(edit_dist[i-1][j], edit_dist[i][j-1])+1);
		vector < pair <int, int> > path;
		int i=right_m-left_m, j=right_n-left_n;
		while(i!=0||j!=0)
		{
			path.push_back(make_pair(i+left_m, j+left_n));
			if(i==0)
				--j;
			else
				if(j==0)
					--i;
				else
					if(edit_dist[i][j]==edit_dist[i-1][j-1]+(m[left_m+i]==n[left_n+j]?0:1))
						--i, --j;
					else
						if(edit_dist[i][j]==edit_dist[i-1][j]+1)
							--i;
						else
							--j;
		}
		for(int i=path.size()-1; i>0; --i)
			edit_operations.push_back(path[i]);
		if(leven_dist==-1)
			leven_dist=edit_dist[right_m-left_m][right_n-left_n];
	}
	else
	{
		int middle_n=(left_n+right_n)/2;
		int *left=new int[right_m-left_m+1];
		forwards(m, n, left_m, right_m, left_n, middle_n, left);
		int *right=new int[right_m-left_m+1];
		backwards(m, n, left_m, right_m, middle_n, right_n, right);
		int index=0, min_sum=left[0]+right[0];
		for(int i=1; i<right_m-left_m+1; ++i)
			if(left[i]+right[i]<min_sum)
				index=i, min_sum=left[i]+right[i];
		delete[] left, right;
		if(leven_dist==-1)
			leven_dist=min_sum;
		Hirschberg_algorithm(m, n, left_m, left_m+index, left_n, middle_n, edit_operations, leven_dist);
		edit_operations.push_back(make_pair(left_m+index, middle_n));
 		Hirschberg_algorithm(m, n, left_m+index, right_m, middle_n, right_n, edit_operations, leven_dist);
	}
}
int main()
{
	string m, n;
	cin>>m>>n;
	m='#'+m;
	n='#'+n;
	int leven_dist=-1;
	vector < pair <int, int> > edit_operations;
	edit_operations.push_back(make_pair(0, 0));
	Hirschberg_algorithm(m, n, 0, m.size()-1, 0, n.size()-1, edit_operations, leven_dist);
	edit_operations.push_back(make_pair(m.size()-1, n.size()-1));
	cout<<leven_dist<<endl;
	for(int i=1; i<edit_operations.size(); ++i)
	{
		if(edit_operations[i].first==edit_operations[i-1].first)
			cout<<"Insert "<<n[edit_operations[i].second]<<" to 1st string after "<<edit_operations[i].first<<" position"<<endl;
		else
			if(edit_operations[i].second==edit_operations[i-1].second)
				cout<<"Delete from 1st string at "<<edit_operations[i].first<<" position"<<endl;
			else
				if(m[edit_operations[i].first]!=n[edit_operations[i].second])
					cout<<"Replace in 1st string at "<<edit_operations[i].first<<" position to "<<n[edit_operations[i].second]<<endl;
	}
	return 0;
}
#include<iostream>
#include<vector>
using namespace std;

int main(){
	int n,m;
	cin>>n;
	vector <int> arr1 (n);
	for(int i=0;i<n;i++)
		cin>>arr1[i];
	cin>>m;
	vector <int> arr2(m);
	for(int i=0;i<m;i++)
		cin>>arr2[i];
	vector <int> maxlength(m,0);
	vector <int> predok(m,-1);
	int ans=0,begin=-1;
	for(int i=0;i<n;i++){
		int last=-1,current=0;
		for(int j=0;j<m;j++){
			if(arr1[i]==arr2[j] && current+1 > maxlength[j]){
				maxlength[j]=current+1;
				if(maxlength[j]>ans){
					ans=maxlength[j];
					begin=j;
				}
				predok[j]=last;
			}
			if(arr1[i]>arr2[j] && current < maxlength[j]){
				current=maxlength[j];
				last=j;
			}
		}
	}
	if(ans){
		cout<<ans<<endl;
		vector <int> answer;
		while(begin!=-1){
			answer.push_back(arr2[begin]);
			begin=predok[begin];
		}
		for(int i=answer.size()-1;i>=0;i--)
			cout<<answer[i]<<" ";
	}
	else
		cout<<"There isn't LCIS";
	return 0;
}
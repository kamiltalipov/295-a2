#include<iostream>
#include<vector>
#include<string>
#include<string.h>
#include<algorithm>
using namespace std;

string ans(int left,int right, vector <vector <string> > &Array, string &s){
	if(Array[left][right]==""){
		int n1=0,n2=0,n3=0;
		if(left+1 <= right){
			if(Array[left+1][right]=="")
				Array[left+1][right]=ans(left+1,right,Array,s);
			n1 = Array[left+1][right].length();
		}
		if(left<=right-1){
			if(Array[left][right-1]=="")
				Array[left][right-1]=ans(left,right-1,Array,s);
			n2 = Array[left][right-1].length();
		}
		if(left+1<s.length() && left<s.length() && right-1>=0 && right<s.length() &&s[left]==s[right]){
			//if(Array[left+1][right-1]=="")
				//Array[left+1][right-1]=ans(left+1,right-1,Array,s);
			n3=Array[left+1][right-1].length()+2;
		}
		int n=max(n1,max(n2,n3));
		if(n==n1)
			return Array[left+1][right];
		else
			if(n==n2)
				return Array[left][right-1];
			else
				if(n==n3)
					return s[left]+Array[left+1][right-1]+s[right];
	}
	else
		return Array[left][right];
}

int main(){
	string s;
	cin>>s;
	vector <vector <string> > Array(s.length());
	for(int i=0;i<s.length();i++){
		Array[i].resize(s.length(),"");
		Array[i][i]=s[i];
	}
	string answer=ans(0,s.length()-1,Array,s);
	cout<<answer.length()<<endl<<answer;
	return 0;
}
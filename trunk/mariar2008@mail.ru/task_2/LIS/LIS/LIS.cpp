#include<stdio.h>
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int BinSearch(const vector<int>&MinValue, int x){
	int l = 1, r = MinValue.size() - 1;
	while (l + 1 < r){
		int m = (l + r)/2;
		if (x <= MinValue[m])
			r = m;
		else
			l = m;
	}
	int ans = r + 1;
	if (MinValue[r] >= x)
		ans = r;
	if (MinValue[l] >= x)
		ans = l;
	return ans;
	
}

void MakeLIS(const vector<int>&ourArray){
	int n = ourArray.size();
	vector<int>MaxLen(n), Parent(n), MinValue(2), Ind(2);
	MaxLen[0] = 1; Parent[0] = -1;

	MinValue[1] = ourArray[0]; 
	Ind[1] = 0; Ind[0] = -1;
	for (int i = 1; i < n; i++){
		int j = BinSearch(MinValue, ourArray[i]);
		if (j == MinValue.size()){
			MinValue.push_back(ourArray[i]);
			Ind.push_back(i);
		}
		MaxLen[i] = j;
		Parent[i] = Ind[j - 1];
		if (MinValue[j] > ourArray[i]){
			MinValue[j] = ourArray[i];
			Ind[j] = i;
		}
	}
	int Max = 0;
	for (int i = 1; i < n; i++){
		if (MaxLen[Max] < MaxLen[i]){
			Max = i;
		}
	}
	cout << MaxLen[Max] << endl;
	vector<int>ans;
	while (Max != -1){
		ans.push_back(ourArray[Max]);
		Max = Parent[Max];
	}
	for (int i = ans.size() - 1; i >= 0; i--)
		cout << ans[i] << " ";
}
int main( void ){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);

	int n;
	cin >> n;
	vector<int>ourArray(n);
	for (int i = 0; i < n; i++){
		cin >> ourArray[i];
	}

	MakeLIS(ourArray);

	return 0;
}
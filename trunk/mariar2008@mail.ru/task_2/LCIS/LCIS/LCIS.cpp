#include <stdio.h>
#include<iostream>
#include<vector>

using namespace std;
void MakeLCIS(const vector<int>& ArrOne, const vector<int>& ArrTwo, const int Min){
	int n = ArrOne.size(), m = ArrTwo.size();
	vector<vector<int>> MaxCurLCIS(n, m), link(n, m), MinLastEl(n, m);

	for (int i = 0; i < n; i++) 
		for (int j = 0; j < m; j++)
			MinLastEl[i][j] = Min - 1;
	
	for (int i = 1; i < n; i++){
		for (int j = 1; j < m; j++){
			if ((MaxCurLCIS[i][j - 1] > MaxCurLCIS[i - 1][j])||((MaxCurLCIS[i][j - 1] == MaxCurLCIS[i - 1][j])&&(MinLastEl[i][j - 1] < MinLastEl[i - 1][j]))){
				MaxCurLCIS[i][j] = MaxCurLCIS[i][j - 1];
				link[i][j] = -1;
				MinLastEl[i][j] = MinLastEl[i][j - 1];
			}
			else{
				MaxCurLCIS[i][j] = MaxCurLCIS[i - 1][j];
				link[i][j] = 1;
				MinLastEl[i][j] = MinLastEl[i - 1][j];
			}
			if ((ArrOne[i] == ArrTwo[j])&&(ArrOne[i] > MinLastEl[i - 1][j - 1])){
				if ((MaxCurLCIS[i - 1][j - 1] + 1 > MaxCurLCIS[i][j])||((MaxCurLCIS[i - 1][j - 1] + 1 == MaxCurLCIS[i][j])&&(MinLastEl[i][j] > ArrOne[i]))){
					MaxCurLCIS[i][j] = MaxCurLCIS[i - 1][j - 1]  + 1;
					link[i][j] = 0;
					MinLastEl[i][j] = ArrOne[i];
				}
			}
		}
	}
	int LenAns = MaxCurLCIS[n - 1][m - 1];
	cout << LenAns << endl;
	int x = n - 1, y = m - 1;
	vector<int> Ans;
	while ((x != 0)&&(y != 0)){
		if (link[x][y] == -1)
			y--;
		else
			if (link[x][y] == 1)
				x--;
			else{
				Ans.push_back(ArrOne[x]);
				x--;
				y--;
			}
	}
	for (int i = LenAns - 1; i >= 0; i--)
		 cout << Ans[i] << " ";
}
 int main( void ){
	 freopen("input.txt","r",stdin);
	 freopen("output.txt","w",stdout);
	 int LenOne, LenTwo, Min;
	 cin >> LenOne;
	 vector<int>ArrOne(LenOne + 1);
	 cin >> ArrOne[1];
	 Min = ArrOne[1];
	 for (int i = 2; i <= LenOne; i++){
		 cin >> ArrOne[i];
		 Min = min(Min, ArrOne[i]);
	 }
	 cin >> LenTwo;
	 vector<int>ArrTwo(LenTwo + 1);
	 for (int i = 1; i <= LenTwo; i++){
		 cin >> ArrTwo[i];
		 Min = min(Min, ArrTwo[i]);
	 }

	 MakeLCIS(ArrOne, ArrTwo, Min);
	 return 0;
 }
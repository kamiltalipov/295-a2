#include<stdio.h>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

void FindMaxPalindrome(const string& s){
	int LenS = s.size();
	vector<vector<int>>MaxP(LenS), link(LenS);
	for (int i = 0; i < LenS; i++){
		MaxP[i].resize(LenS);
		link[i].resize(LenS);
	}
	MaxP[LenS - 1][LenS - 1] = 1;
	link[LenS - 1][LenS - 1] = 0;
	for(int i = LenS - 2; i >= 0; i--){
		MaxP[i][i] = 1;
		link[i][i] = 0;
		for (int j = i + 1; j < LenS; j++){
			MaxP[i][j] = MaxP[i][j - 1];
			link[i][j] = -1;
			if (MaxP[i][j] < MaxP[i + 1][j]){
				MaxP[i][j] = MaxP[i + 1][j];
				link[i][j] = 1;
			}
			if (s[i] == s[j])
				if ((i + 1 == j)&&(MaxP[i][j] < 2)){
					MaxP[i][j] = 2;
					link[i][j] = 0;
				}
				else
					if ((i + 1 != j)&&(MaxP[i][j] < MaxP[i + 1][j - 1] + 2)){
						MaxP[i][j] = MaxP[i + 1][j - 1] + 2;
						link[i][j] = 0;
					}
			
		}
	}
	cout << MaxP[0][LenS - 1] << endl;
	int l = 0, r = LenS - 1;
	string ans;
	while (r - l > 1){
		if (link[l][r] == 0){
			ans +=s[l];
			l = l + 1;
			r = r - 1;
		}
		else{
			if (link[l][r] == -1)
				r = r - 1;
			else
				l = l + 1;
		}
	}
	if ((l + 1 == r)&&(s[l] == s[r])){
		ans += s[l];
		cout << ans;
	}
	else
		cout << ans << s[l];
	for (int i = ans.size() - 1; i >= 0; i--){
		cout << ans[i];
	}
}

int main( void ){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);

	string s;
	cin >> s;
	FindMaxPalindrome(s);

	return 0;
}
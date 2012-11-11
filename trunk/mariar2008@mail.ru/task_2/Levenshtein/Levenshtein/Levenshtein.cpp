#include<stdio.h>
#include<iostream>
#include<string>
#include<vector>

using namespace std;

void FindLev(const string& s, const string& t, int leftS, int rightS, int leftT, int rightT, bool write){
	int LenS = rightS - leftS, LenT = rightT - leftT, medium = LenT/2;
	
	if (LenS == 0){
		if (write) cout << LenT << endl;
		for (int i = leftT; i < rightT; i++)
			cout << "I";
		return;
	}
	if (LenT == 0){
		if (write) cout << LenS << endl;
		for (int i = leftS; i < rightS; i++)
			cout << "D";
		return;
	}
	if (LenS == 1){
		bool find = false;
		for (int i = leftT; i < rightT; i++)
			if (s[leftS] == t[i])
				find = true;
		if (write)
			if (find) cout << LenT - 1 << endl;
			else cout << LenT << endl;

		if (!find){
			for (int i = 0; i < LenT - 1; i++)
				cout << "I";
			cout << "R";
		}
		else{
			int j = rightT;
			for (int i = leftT; i < rightT; i++)
				if (s[leftS] == t[i]){
					cout << "M";
					j = i + 1;
					break;
				}
				else
					cout << "I";
			for (; j < rightT; j++)
				cout << "I";
		}
		return;
	}
	if (LenT == 1){
		bool find = false;
		for (int i = leftS; i < rightS; i++)
			if (s[i] == t[leftT])
				find = true;
		if (write)
			if (find) cout << LenS - 1 << endl;
			else cout << LenS;
		if (!find){
			for (int i = 0; i < LenS - 1; i++)
				cout << "D";
			cout << "R";
		}
		else{
			int j = rightS;
			for (int i = leftS; i < rightS; i++)
				if (s[i] != t[leftT])
					cout << "D";
				else{
					cout << "M";
					j = i + 1;
					break;
				}
			for (; j < rightS; j++)
				cout << "D";
		}
		return;
	}

	vector<int>forward_1(LenS), forward_2(LenS), back_1(LenS), back_2(LenS);
	forward_1[0] = 1;
	if (s[leftS] == t[leftT])
		forward_1[0]--;

	for (int i = 1; i < LenS; i++){
		forward_1[i] = i + 1;
		if (s[i + leftS] == t[leftT])
			forward_1[i]--;
		forward_1[i] = min(forward_1[i], forward_1[i - 1] + 1);

	}
	for (int j = 1; j < medium; j++){
		forward_2[0] = j + 1;
		if (s[leftS] == t[j + leftT])
			forward_2[0]--;
		forward_2[0] = min(forward_2[0], forward_1[0] + 1);
		
		for (int i = 1; i < LenS; i++){
			forward_2[i] = min(forward_2[i - 1], min(forward_1[i], forward_1[i - 1])) + 1;
			if (s[i + leftS] == t[j + leftT])
				forward_2[i] = min(forward_2[i], forward_1[i - 1]);
		}
		forward_1 = forward_2;
	}
	
	back_1[LenS - 1] = 1;
	if (s[rightS - 1] == t[rightT - 1])
		back_1[LenS - 1]--;

	for (int i = LenS - 2; i >= 0; i--){
		back_1[i] = LenS - i;
		if (s[i + leftS] == t[rightT - 1])
			back_1[i]--;
		back_1[i] = min(back_1[i], back_1[i + 1] + 1);
	}

	for (int j = LenT - 2; j >= medium; j--){
		back_2[LenS - 1] = LenT - j;
		if (s[rightS - 1] == t[j + leftT])
			back_2[LenS - 1]--;
		back_2[LenS - 1] = min(back_2[LenS - 1], back_1[LenS - 1] + 1);
		for (int i = LenS - 2; i >= 0; i--){
			back_2[i] = min(back_2[i + 1], min(back_1[i] , back_1[i + 1])) + 1;
			if (s[i + leftS] == t[j + leftT])
				back_2[i] = min(back_2[i], back_1[i + 1]);
		}
		back_1 = back_2;
	}

	int mincur = back_1[0] + medium, ind = 0;
	for (int i = 0; i < LenS - 1; i++){
		if (forward_1[i] + back_1[i + 1] < mincur){
			mincur = forward_1[i] + back_1[i + 1];
			ind = i + 1;
		}
	}
	if (forward_1[LenS - 1] + LenT - medium < mincur){
		mincur = forward_1[LenS - 1] + LenT - medium;
		ind = LenS;
	}
	if (write)	cout << mincur << endl;
	FindLev(s, t, leftS, ind + leftS, leftT, medium + leftT, false);
	FindLev(s, t, ind + leftS, rightS, medium + leftT, rightT, false);

}
int main( void ){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);

	string s, t;
	cin >> s >> t;
	FindLev(s, t, 0, s.size(), 0, t.size(), true);
	return 0;
}            
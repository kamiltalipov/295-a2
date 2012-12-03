#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void LevDist(string& s1, string& s2, vector <int>& res)
{
	vector <int> dp1(s2.size() + 1), dp2(s2.size() + 1);
	for (int i = 0; i < s2.size() + 1; i++)
		dp1[i] = i;
	for (int i = 1; i < s1.size() + 1; i++)
	{
		dp2[0] = i;
		for (int j = 1; j < s2.size() + 1; j++)
		{
			dp2[j] = min(dp2[j - 1], min(dp1[j], dp1[j - 1])) + 1;
			if (s1[i - 1] == s2[j - 1])
			{
				dp2[j] = min(dp2[j], dp1[j - 1]);
			}
		}
		swap(dp1, dp2);
	}
	swap(res, dp1);
}

void Hirschberg(string& s1, string& s2)
{
	if (!s2.size() && s1.size())
	{
		for (int i = 0; i < s1.size(); i++)
			cout << "D";
	}
	else if (s1.size() == 1 && s2.size())
	{
		bool done = false;
		for (int i = 0; i < s2.size() - 1; i++)
		{
			if (s1[0] == s2[i] && !done)
			{
				cout << "N";
				done = true;
			}
			else
				cout << "I";
		}
		if (s1[0] == s2[s2.size() - 1] && !done)
			cout << "N";
		else if (s1[0] != s2[s2.size() - 1] && !done)
			cout << "R";
		else
			cout << "I";
	}
	else if (s1.size() && s2.size())
	{
		int m = s1.size() / 2;
		vector <int> side1, side2;
		string s1_1(s1.begin(), s1.begin() + m);
		string s1_r, s2_r;
		s1_r.resize(s1.size() - m);
		s2_r.resize(s2.size());
		reverse_copy(s1.begin() + m, s1.end(), s1_r.begin());
		reverse_copy(s2.begin(), s2.end(), s2_r.begin());
		LevDist(s1_1, s2, side1);
		LevDist(s1_r, s2_r, side2);
		int min_ind = 0;
		for (int i = 0; i < s2.size() + 1; i++)
		{
			if (side1[i] + side2[s2.size() - i] < side1[min_ind] + side2[s2.size() - min_ind])
				min_ind = i;
		}
		string s2_1, s1_2, s2_2;
		s1_1.resize(m);
		copy(s1.begin(), s1.begin() + m, s1_1.begin());
		s2_1.resize(min_ind);
		copy(s2.begin(), s2.begin() + min_ind, s2_1.begin());
		Hirschberg(s1_1, s2_1);
		s1_2.resize(s1.size() - m);
		copy(s1.begin() + m, s1.end(), s1_2.begin());
		s2_2.resize(s2.size() - min_ind);
		copy(s2.begin() + min_ind, s2.end(), s2_2.begin());
		Hirschberg(s1_2, s2_2);
	}
}

int main()
{
	int n, m;
	string s1, s2;
	cin >> s1 >> s2;
	Hirschberg(s1, s2);
	return 0;
}
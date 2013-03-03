#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>


using namespace std;

struct elem
{
	string s;
	int freq;
};

class comparator
{
	friend class Suggestor;
public:
	comparator() {};
	bool operator() (elem& lhs, elem&rhs) 
	{
		return (lhs.freq < rhs.freq);
	}
};

class Suggestor
{
	friend class comparator;
public:
	vector <elem> data;
	elem pref;
	int k;

	Suggestor( vector <elem> &input, string s, int k):
		data(input), k(k) 
		{
			pref.s = s;
			pref.freq = 0;
		};

	vector<elem> Solve();
};

bool strcomp(const elem &a, const elem &b)
{
	for(int i = 0; i < min(a.s.size(), b.s.size()); i++)
	{
		if (a.s[i] < b.s[i])
			return true;
		if (a.s[i] > b.s[i])
			return false;
	}
	return(a.s.size() < b.s.size());
}

vector<elem> Suggestor::Solve()
{
	vector<elem> ans;
	vector<elem>::iterator l = lower_bound(data.begin(), data.end(), pref, strcomp);
	pref.s[pref.s.size() - 1]++;
	vector<elem>::iterator r = upper_bound(data.begin(), data.end(), pref, strcomp);

	priority_queue <elem, vector<elem>, comparator> heap(l, r);

	for(int i = 0; i < min(k, (int) heap.size()); i++)
	{
		ans.push_back(heap.top());
		heap.pop();
	}
	return ans;
}

int main()
{
	freopen("input.txt", "r", stdin); //input+dictionary+frequences.
	freopen("output.txt", "w", stdout);
	string s;
	int k;
	cin >> s;
	cin >> k;
	int fr;
	string tmp;
	vector <elem> a;
	while (cin >> tmp)
	{
		cin >> fr;
		elem t;
		t.s = tmp;
		t.freq = fr;
		a.push_back(t);
	}

	sort(a.begin(), a.end(), strcomp);
	Suggestor fn(a, s, k);
	vector<elem> ans;
	ans = fn.Solve();

	for(int i = 0; i < ans.size(); i++)
		cout << ans[i].s << endl;

	fclose(stdin);
	fclose(stdout);
	return 0;
}
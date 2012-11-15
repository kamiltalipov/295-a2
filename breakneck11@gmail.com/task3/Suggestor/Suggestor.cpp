#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits.h>
using namespace std;

struct Hstring {
private:
	typedef unsigned long long HT;
	static const HT P = 193, MOD = 12727198717778921;
public:
	string str;
	vector < HT > hashes;
	Hstring(const string& s)
	{
		str = s;
		hashes.resize(str.length() + 1);
		for (int i = 1; i <= str.length(); ++i)
			hashes[i] = (hashes[i - 1] * P + s[i - 1]) % MOD;
	}
	bool operator< (const Hstring& hs) const
	{
		int L = 0, R = min(hs.str.length(), str.length()) + 1, m;
		while (L + 1 < R)
		{
			m = (L + R) >> 1;
			if (hashes[m] == hs.hashes[m])
				L = m;
			else
				R = m;
		}
		if (L == min(hs.str.length(), str.length()))
			return str.length() < hs.str.length();
		return str[L] < hs.str[L];
	}
	bool has_pref(const Hstring& hs) { return str.length() >= hs.str.length() && hashes[hs.str.length()] == hs.hashes[hs.str.length()]; }
};

class Suggestor {
private:
	int lch(int v) { return (v << 1) + 1; }
	int rch(int v) { return (v << 1) + 2; }
	vector < pair < Hstring, int > > dict;
	vector < vector < int > > seg_tree;
	void build_sgt(int v, int tl, int tr);
	void get_sug(int v, int tl, int tr, int l, int r, vector < int > &sug, int len);
	int get_last_pref_pos(const Hstring& pref, int start_pref);
public:
	Suggestor(const vector < pair < string, int > >& strs)
	{
		for (int i = 0; i < strs.size(); ++i)
			dict.push_back(make_pair(Hstring(strs[i].first), strs[i].second));
		sort(dict.begin(), dict.end());
		seg_tree.resize(dict.size() << 2);
		build_sgt(0, 0, dict.size());
	}
	void Request(const string& pref, int len, vector < string > &ans);
};

void Suggestor::build_sgt(int v, int tl, int tr)
{
	if (tl >= tr)
		return;
	if (tl + 1 == tr)
		return void(seg_tree[v].push_back(tl));
	const int tm = (tl + tr) >> 1;
	build_sgt(lch(v), tl, tm), build_sgt(rch(v), tm, tr);
	int i = 0, j = 0, to = 0;
	seg_tree[v].resize(seg_tree[lch(v)].size() + seg_tree[rch(v)].size());
	for (; i < seg_tree[lch(v)].size() && j < seg_tree[rch(v)].size(); ++to)
	{
		if (dict[seg_tree[lch(v)][i]].second < dict[seg_tree[rch(v)][j]].second)
			seg_tree[v][to] = seg_tree[rch(v)][j++];
		else
			seg_tree[v][to] = seg_tree[lch(v)][i++];
	}
	for (; i < seg_tree[lch(v)].size(); ++i)
		seg_tree[v][to++] = seg_tree[lch(v)][i];
	for (; j < seg_tree[rch(v)].size(); ++j)
		seg_tree[v][to++] = seg_tree[rch(v)][j];
}

void Suggestor::get_sug(int v, int tl, int tr, int l, int r, vector < int > &sug, int len)
{
	if (tl == l && tr == r)
	{
		sug.resize(min((unsigned int)len, seg_tree[v].size()));
		for (int i = 0, n = min((unsigned int)len, seg_tree[v].size()); i < n; ++i)
			sug[i] = seg_tree[v][i];
		return;
	}
	const int tm = (tl + tr) >> 1;
	vector < int > la, ra;
	if (l < tm)
		get_sug(lch(v), tl, tm, l, min(tm, r), la, len);
	if (tm < r)
		get_sug(rch(v), tm, tr, max(l, tm), r, ra, len);
	int i = 0, j = 0, to = 0;
	sug.clear();
	for (; i < la.size() && j < ra.size() && to < len; ++to)
		if (dict[la[i]].second < dict[ra[j]].second)
			sug.push_back(ra[j++]);
		else
			sug.push_back(la[i++]);
	for (; i < la.size() && to < len; ++i, ++to)
		sug.push_back(la[i]);
	for (; j < ra.size() && to < len; ++j, ++to)
		sug.push_back(ra[j]);
}

int Suggestor::get_last_pref_pos(const Hstring &pref, int start_pref)
{
	int L = start_pref - 1, R = dict.size() - 1, m;
	while (L + 1 < R)
	{
		m = (L + R) >> 1;
		if (dict[m].first.has_pref(pref) || dict[m].first < pref)
			L = m;
		else
			R = m;
	}
	return R == dict.size() - 1 && dict[dict.size() - 1].first.has_pref(pref) ? R + 1 : R;
}

void Suggestor::Request(const string& pref, int len, vector < string > &ans)
{
	ans.clear();
	if (!len || !dict.size())
		return;
	Hstring hpref(pref);
	int L = lower_bound(dict.begin(), dict.end(), make_pair(hpref, INT_MIN)) - dict.begin(),
		R = get_last_pref_pos(hpref, L);
	if (L == R)
		return;
	vector < int > mans;
	get_sug(0, 0, dict.size(), L, R, mans, len);
	for (int i = 0; i < mans.size(); ++i)
		ans.push_back(dict[mans[i]].first.str);
}

int main()
{
	int n, v; char c; string s;
	ifstream inp("input.txt");
	ofstream out("output.txt");
	inp >> n;
	vector < pair < string, int > > dict;
	for (int i = 0; i < n; ++i)
	{
		inp >> v >> s;
		dict.push_back(make_pair(s, v));
	}
	Suggestor sg(dict);
	vector < string > ans;
	int m;
	inp >> m;
	for (int i = 0; i < m; ++i)
	{
		inp >> v >> s;
		sg.Request(s, v, ans);
		for (int j = 0; j < ans.size(); ++j)
			out << ans[j] << endl;
		out << endl;
	}
	inp.close();
	out.close();
	return 0;
}
#include <iostream>
using std :: cin;
using std :: cout;
using std :: istream;
#include <string>
using std :: string;
#include <vector>
using std :: vector;
#include <set>
using std :: set;
#include <utility>
using std :: pair;
using std :: make_pair;

struct Cube
{
	char edge[6];

	bool haveLetter (char c) const
	{
		for (size_t i = 0; i < 6; ++i)
			if (edge[i] == c)
				return true;
		return false;
	}
};

istream& operator >> (istream& input, Cube& cube)
{
	for (size_t i = 0; i < 6; ++i)
		input >> cube.edge[i];
	return input;
}

bool tryToImprove (const vector<vector<size_t> >& g, const size_t v, 
			   	   vector<bool>& used, vector<size_t>& pair_i)
{
	if (used[v])
		return false;
	used[v] = true;
	for (size_t i = 0; i < g[v].size (); ++i)
		if (pair_i[g[v][i]] == -1 || tryToImprove (g, pair_i[g[v][i]], used, pair_i))
		{
			pair_i[g[v][i]] = v;
			return true;
		}

	return false;
}

void getWord (const string& word, const vector<Cube>& cubes, vector<pair<size_t, char> >& getCubes)
{
	vector<vector<size_t> > g (word.size () + cubes.size ());
	for (size_t i = 0; i < word.size (); ++i)	
		for (size_t j = 0; j < cubes.size (); ++j)
			if (cubes[j].haveLetter (word[i]))
			{
				g[i].push_back (j + word.size ());
				g[j + word.size ()].push_back (i);
			}

	vector<size_t> pair_i (g.size (), -1);
	vector<bool> used (g.size (), false);
	for (size_t i = 0; i < g.size (); ++i)
	{
		used.assign (g.size (), false);
		tryToImprove (g, i, used, pair_i);
	}

	for (size_t i = 0; i < word.size (); ++i)
	{
		if (pair_i[i] == -1)
		{
			getCubes.clear ();
			return;
		}
		getCubes.push_back (make_pair (pair_i[i] - word.size (), word[i]));
	}
}

int main ()
{
	string word;
	cin >> word;
	size_t all_cubes = 0;
	cin >> all_cubes;
	vector<Cube> cubes (all_cubes);
	for (size_t i = 0; i < all_cubes; ++i)
		cin >> cubes[i];

	vector<pair<size_t, char> > ans;	
	getWord (word, cubes, ans);
	if (ans.empty ())
		cout << "Can't get word\n";
	else
		for (size_t i = 0; i < ans.size (); ++i)
			cout << ans[i].first << ' ' << ans[i].second << '\n';

	return 0;
}
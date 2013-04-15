#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cstdlib>
#include <cstdio>
using namespace std;
 
int d, awords = 0;
vector < vector < int > > gr(d);
map < string, int > dict;

inline int getWordIndex(const string& name)
{
	int res;
	if (dict.find(name) == dict.end())
		dict[name] = res = awords++;
	else
		res = dict[name];
	return res;
}

vector < unsigned char > marks;
const unsigned char WHITE = 0, GREY = 1, BLACK = 2;

void dfs(int v)
{
	marks[v] = GREY;
	for (int i = 0; i < gr[v].size(); ++i)
		if (marks[gr[v][i]] == GREY)
		{
			cout << "NOT CORRECT";
			exit(EXIT_SUCCESS);
		}
		else if (marks[gr[v][i]] == WHITE)
			dfs(gr[v][i]);
	marks[v] = BLACK;
}

int main()
{
    cin >> d;
    for (int iword = 0; iword < d; ++iword)
    {
    	string word, dep;
    	int ndeps, ciword;
    	cin >> word >> ndeps;
    	ciword = getWordIndex(word);
        gr.resize(max((int)gr.size(), ciword + 1));
        if (gr[ciword].size())
        {
            cout << "NOT CORRECT";
            exit(EXIT_SUCCESS);
        }
    	for (int i = 0; i < ndeps; ++i)
    	{
    		cin >> dep;
            int idep = getWordIndex(dep);
            gr.resize(max((int)gr.size(), idep + 1));
    		gr[ciword].push_back(getWordIndex(dep));
    	}
    }
    marks.resize(d);
    for (int i = 0; i < d; ++i)
    	if (marks[i] == WHITE)
    		dfs(i);
    cout << "CORRECT";
    return 0;
}
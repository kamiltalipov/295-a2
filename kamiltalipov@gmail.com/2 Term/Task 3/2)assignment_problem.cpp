#include <iostream>
using std :: cin;
using std :: cout;
#include <vector>
using std :: vector;
#include <utility>
using std :: pair;
using std :: make_pair;

const int INF = 1000000000;
const int NOT_SET = -1;

void findMaxPair (const vector<vector<int> >& g, vector<pair<size_t, size_t> >& max_pair)
{
   	vector<int> diffRow (g.size (), 0), diffColomn (g.size (), 0);
   	vector<int> markIndices (g.size (), NOT_SET);
   	for (size_t i = 0; i < g.size (); ++i) 
   	{
   		vector<int> links (g.size (), NOT_SET);
      	vector<int> mins (g.size (), INF);
      	vector<int> visited (g.size (), 0);
      
      	int markedI = i, markedJ = NOT_SET, j = NOT_SET;
      	while (markedI != NOT_SET) 
      	{
      		j = NOT_SET;
         	for (size_t j1 = 0; j1 < g.size (); ++j1)
           		if (!visited[j1]) 
           		{
               		if (g[markedI][j1] - diffRow[markedI] - diffColomn[j1] < mins[j1]) 
               		{
                  		mins[j1] = g[markedI][j1] - diffRow[markedI] - diffColomn[j1];
                  		links[j1] = markedJ;
               		}
               		if (j == NOT_SET || mins[j1] < mins[j])
                		j = j1;
            	}
            
         	int delta = mins[j];
         	for (size_t j1 = 0; j1 < g.size (); ++j1)
         	{
            	if (visited[j1]) 
            	{
               		diffRow[markIndices[j1]] += delta;
               		diffColomn[j1] -= delta;
            	} 
            	else 
            	{
               		mins[j1] -= delta;
            	}
            }
         	diffRow[i] += delta;
         
         	visited[j] = 1;
         	markedJ = j;
        	markedI = markIndices[j];   
      	}
      
      	while (links[j] != NOT_SET)
      	{
         	markIndices[j] = markIndices[links[j]];
         	j = links[j];
        }
      	markIndices[j] = i;
   	}
   
   	for (size_t j = 0; j < g.size (); ++j)
   		if (markIndices[j] != NOT_SET)
			max_pair.push_back (make_pair (markIndices[j], j));	
}

int main ()
{
	size_t all_v = 0;
	cin >> all_v;
	vector<vector<int> > g (all_v, vector<int> (all_v, INF));
	for (size_t v = 0; v < all_v; ++v)
		for (size_t u = 0; u < all_v; ++u)
			cin >> g[v][u];

	vector<pair<size_t, size_t> > max_pair;
	findMaxPair (g, max_pair);
	for (size_t i = 0; i < max_pair.size (); ++i)
		cout << max_pair[i].first << ' ' << max_pair[i].second << '\n';

	return 0;
}
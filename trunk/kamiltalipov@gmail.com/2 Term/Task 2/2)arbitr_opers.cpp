#include <cstdio>
#include <iostream>
using std :: cin;
using std :: cout;
#include <vector>
using std :: vector;
#include <algorithm>
using std :: reverse;

const size_t NOT_SET = -1;

void find_neg_cycle1 (const vector<vector<double> >& moneyMatrix, vector<size_t>& cycle)
{
    const size_t start_v = 0;
   
    vector<double> distance (moneyMatrix.size (), 0.0);
    vector<size_t> prev (moneyMatrix.size (), NOT_SET);
    distance[start_v] = 1.0;
    for (size_t i = 0; i < moneyMatrix.size (); ++i)
    {
        for (size_t v = 0; v < moneyMatrix.size (); ++v)
            for (size_t u = 0; u < moneyMatrix.size (); ++u)
            {
                if (moneyMatrix[v][u] < 0.0)
                    continue;

                if (distance[u] < distance[v] * moneyMatrix[v][u])
                {
                    distance[u] = distance[v] * moneyMatrix[v][u];
                    prev[u] = v;
                }
            }
    }

    vector<bool> in_cycle (moneyMatrix.size (), false);
    for (size_t i = 0; i < moneyMatrix.size (); ++i)
        if (distance[i] > 1.0)
        {
            cycle.push_back (i);
            in_cycle[i] = true;
            size_t cur_v = prev[i];
            while (cur_v != i && !in_cycle[cur_v])
            {
                cycle.push_back (cur_v);
                in_cycle[cur_v] = true;
                cur_v = prev[cur_v];
            }

            reverse (cycle.begin (), cycle.end ());

            break;
        }
}

void getCycle (const vector<vector<size_t> >& mid, size_t from, size_t to,
               vector<bool>& in_cycle, vector<size_t>& cycle)
{
    if (mid[from][to] == NOT_SET)
		return;
	if (in_cycle[mid[from][to]])
		return;
	in_cycle[mid[from][to]] = true;

	vector<size_t> cycle1, cycle2;
	getCycle (mid, from, mid[from][to], in_cycle, cycle);
	getCycle (mid, mid[from][to], to, in_cycle, cycle);
	cycle.reserve (cycle1.size () + 1 + cycle2.size ());
	cycle.insert (cycle.end (), cycle1.begin (), cycle1.end ());
	cycle.push_back (mid[from][to]);
	cycle.insert (cycle.end (), cycle1.begin (), cycle1.end ());
	
	//reverse (cycle.begin (), cycle.end ());
}

void find_neg_cycle2 (vector<vector<double> >& moneyMatrix, vector<size_t>& cycle)
{
    vector<vector<size_t> > mid (moneyMatrix.size (), vector<size_t> (moneyMatrix.size (), NOT_SET));
	for (size_t i = 0; i < moneyMatrix.size (); ++i)
		for (size_t j = 0; j < moneyMatrix.size (); ++j)
			mid[i][j] = i;
    for (size_t i = 0; i < moneyMatrix.size (); ++i)
        for (size_t v = 0; v < moneyMatrix.size (); ++v)
            for (size_t u = 0; u < moneyMatrix.size (); ++u)
            {
                if (moneyMatrix[v][u] < moneyMatrix[v][i] * moneyMatrix[i][u])
                {
                    moneyMatrix[v][u] = moneyMatrix[v][i] * moneyMatrix[i][u];
                    mid[v][u] = mid[i][u];
                }
            }
   
	for (size_t v = 0; v < moneyMatrix.size (); ++v)
		if (moneyMatrix[v][v] > 1.0)
		{
			vector<bool> in_cycle (moneyMatrix.size (), false);
			getCycle (mid, v, v, in_cycle, cycle);
			return;
		}
}

int main ()
{
	size_t all_money = 0;
    cin >> all_money;
    vector<vector<double> > moneyMatrix (all_money, vector<double> (all_money, 1.0));
    for (size_t i = 0; i < all_money; ++i)
        for (size_t j = 0; j < all_money; ++j)
            cin >> moneyMatrix[i][j];

    vector<size_t> ans;
    find_neg_cycle2 (moneyMatrix, ans);
    if (ans.empty ())
        cout << "No way to get more money\n";
    else
    {
        cout << "Way to get money:\n";
        for (size_t i = 0; i < ans.size (); ++i)
            cout << ans[i] << ' ';
        cout << '\n';
    }
    //find_neg_cycle2 (moneyMatrix, ans);

    return 0;
}

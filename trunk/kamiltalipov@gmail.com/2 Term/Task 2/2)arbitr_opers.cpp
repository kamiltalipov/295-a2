#include <iostream>
using std :: cin;
using std :: cout;
#include <vector>
using std :: vector;
#include <algorithm>
using std :: reverse;

void find_neg_cycle1 (const vector<vector<double> >& moneyMatrix, vector<size_t>& cycle)
{
    const size_t start_v = 0;
    const double INF = 1000000000.0;
    const size_t NOT_SET = -1;

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

void find_neg_cycle2 (vector<vector<double> >& moneyMatrix, vector<size_t>& cycle)
{
    const size_t NOT_SET = -1;

    vector<vector<size_t> > next (moneyMatrix.size (), vector<size_t> (moneyMatrix.size (), NOT_SET));
    for (size_t i = 0; i < moneyMatrix.size (); ++i)
        for (size_t v = 0; v < moneyMatrix.size (); ++v)
            for (size_t u = 0; u < moneyMatrix.size (); ++u)
            {
                if (moneyMatrix[v][u] < moneyMatrix[v][i] * moneyMatrix[i][u])
                {
                    moneyMatrix[v][u] = moneyMatrix[v][i] * moneyMatrix[i][u];
                    next[v][u] = i;
                }
            }



    vector<bool> in_cycle (moneyMatrix.size (), false);
    for (size_t i = 0; i < moneyMatrix.size (); ++i)
        if (moneyMatrix[i][i] > 1.0)
        {
            cycle.push_back (i);
            in_cycle[i] = true;
            size_t cur_v = next[i][i];
            while (cur_v != i && !in_cycle[cur_v])
            {
                cycle.push_back (cur_v);
                in_cycle[cur_v] = true;
                cur_v = next[cur_v][i];
            }

            reverse (cycle.begin (), cycle.end ());

            break;
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

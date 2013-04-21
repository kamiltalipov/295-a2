#include <iostream>
#include <vector>

using namespace std;

void print_route(vector< vector<int> > &prev, int start, int finish)
{
    if (prev[start][finish] == start)
    {
        if (start != finish)
            cout << start + 1 << "-->" << finish + 1 << endl;
        return;
    }
    print_route(prev, start, prev[start][finish]);
    print_route(prev, prev[start][finish], finish);
}

int main()
{
    int n;
    cin >> n;
    vector< vector<double> > rate(n);
    vector< vector<int> > prev(n);
    for (int i = 0; i < n; i++)
    {
        prev[i].resize(n);
        for (int j = 0; j < n; j++)
        {
            double k;
            cin >> k;
            rate[i].push_back(k);
            prev[i][j] = i;
        }
        if (rate[i][i] > 1)
        {
            cout << i + 1 << "-->" << i + 1;
            return 0;
        }
    }
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (rate[i][j] < rate[i][k] * rate[k][j])
                {
                    rate[i][j] = rate[i][k] * rate[k][j];
                    if (i != k && j != k)
                        prev[i][j] = k;
                }
    for (int i = 0; i < n; i++)
        if (rate[i][i] > 1)
        {
            print_route(prev, i, i);
            break;
        }
    return 0;
}

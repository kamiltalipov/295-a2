#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector< vector<double> > rate(n);
    vector< int > prev(n);
    vector< double > dist(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            double k;
            cin >> k;
            rate[i].push_back(k);
        }
        dist[i] = rate[0][i];
        if (rate[i][i] > 1)
        {
            cout << i + 1 << "-->" << i + 1;
            return 0;
        }
    }
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (dist[j] < dist[i] * rate[i][j])
                {
                    dist[j] = dist[i] * rate[i][j];
                    if (i != j)
                        prev[j] = i;
                }
    int start = -1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            if (dist[j] < dist[i] * rate[i][j])
            {
                start = j;
                break;
            }
        if (start != -1)
            break;
    }
    if (start != -1)
    {
        for (int i = 0; i < n; i++)
            start = prev[start];
        stack<int> ans;
        ans.push(start);
        int c = prev[start];
        while (c != start)
        {
            ans.push(c);
            c = prev[c];
        }
        while (!ans.empty())
        {
            int v = ans.top();
            ans.pop();
            cout << c + 1 << " --> " << v + 1 << endl;
            c = v;
        }
    }
    return 0;
}

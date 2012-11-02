#include<iostream>
using std :: cin;
using std :: cout;
#include<vector>
using std :: vector;
#include <algorithm>
using std :: reverse;

void LCIS (const vector<int>& a, const vector<int>& b,
           vector<int>& res)
{
    vector<size_t> lcisLen (b.size (), 0);
    vector<size_t> prev (b.size (), 0);

    for (size_t i = 0; i < a.size (); ++i)
    {
        size_t curLen = 0, lastUpd = -1;
        for (size_t j = 0; j < b.size (); ++j)
        {
            if (a[i] == b[j] && curLen + 1 > lcisLen[j])
            {
                lcisLen[j] = curLen + 1;
                prev[j] = lastUpd;
            }
            if (b[j] < a[i] && curLen < lcisLen[j])
            {
                curLen = lcisLen[j];
                lastUpd = j;
            }
        }
    }

    size_t length = 0, index = -1;
    for (size_t i = 0; i < b.size (); ++i)
        if (lcisLen[i] > length)
        {
            length = lcisLen[i];
            index = i;
        }

    if (length > 0)
    {
       while (index != -1)
       {
           res.push_back (b[index]);
           index = prev[index];
       }

       reverse (res.begin (), res.end ());
    }
}


int main()
{
    size_t n;
    cin >> n;
    vector<int> a (n);
    for (size_t i = 0; i < n; ++i)
        cin >> a[i];
    size_t m;
    cin >> m;
    vector<int> b (m);
    for (size_t i = 0; i < m; ++i)
        cin >> b[i];

    vector<int> res;
    LCIS (a, b, res);
    for (size_t i = 0; i < res.size (); ++i)
        cout << res[i] << ' ';

    return 0;
}


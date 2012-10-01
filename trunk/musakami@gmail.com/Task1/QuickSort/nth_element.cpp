#include <iostream>
#include <vector>

using namespace std;

int partition(vector<int> &data, int l, int r)
{
    int i = l;
    int j = r - 2;
    int x = data[r - 1];
    while (i <= j)
    {
        while (data[i] < x) i++;
        while (j >= 0 && data[j] >= x) j--;
        if (i <= j)
        {
            swap(data[i], data[j]);
            i++;
            j--;
        }
    }
    return i;
}

int nth_element(vector<int> &data, int l, int r, int &k)
{
    if (k > r)
        return -1;
    int i = partition(data, l, r);
    swap(data[r - 1], data[i]);
    if (i == k - 1)
        return data[i];
    if (i >= k)
        return nth_element(data, l, i, k);
    else
        return nth_element(data, i + 1, r, k);
}

int main()
{
    vector<int> first;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int readable;
        cin >> readable;
        first.push_back(readable);
    }
    int k;
    cin >> k;
    cout << nth_element(first, 0, first.size(), k);
    return 0;
}

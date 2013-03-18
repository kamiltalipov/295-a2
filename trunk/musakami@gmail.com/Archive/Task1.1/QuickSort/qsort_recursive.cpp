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

void qsort(vector<int> &data, int l, int r)
{
    if (l < r)
    {
        int i = partition(data, l, r);
        swap(data[r - 1], data[i]);
        qsort(data, l, i);
        qsort(data, i + 1, r);
    }
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
    qsort(first, 0, first.size());
    for (int i = 0; i < n; i++)
    {
        cout << first[i] << " ";
    }
    bool sorted = true;
    for (int i = 0; i < n - 1; i++)
        if (first[i] > first[i + 1])
        {
            sorted = false;
            break;
        }
    cout << endl << (sorted ? "Sorted" : "Not sorted");
    return 0;
}

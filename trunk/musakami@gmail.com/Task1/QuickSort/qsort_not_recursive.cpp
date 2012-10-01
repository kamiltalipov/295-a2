#include <iostream>
#include <vector>
#include <stack>

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

void qsort(vector<int> &data)
{
    stack<pair<int, int> > taskStack;
    taskStack.push(make_pair(0, data.size()));
    while (!taskStack.empty())
    {
        pair<int, int> range = taskStack.top();
        taskStack.pop();
        int l = range.first;
        int r = range.second;
        if (l < r)
        {
            int i = partition(data, l, r);
            swap(data[r - 1], data[i]);
            if (i - l > r - i - 1)
            {
                taskStack.push(make_pair(l, i));
                taskStack.push(make_pair(i + 1, r));
            }
            else
            {
                taskStack.push(make_pair(i + 1, r));
                taskStack.push(make_pair(l, i));
            }
        }
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
    qsort(first);
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

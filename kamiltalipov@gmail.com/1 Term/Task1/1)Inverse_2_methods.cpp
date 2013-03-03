#include <iostream>
using std :: cin;
using std :: cout;
#include <algorithm>
using std :: swap;
#include <cassert>


inline int merge (int a[], int left, int right, int buffer[])
{
    int middle = left + (right - left) / 2;
    int posA = left, posB = middle + 1, posRes = 0;
    int cur_inv = 0;
    while (posA <= middle && posB <= right)
    {
        if (a[posA] <= a[posB])
        {
            buffer[posRes] = a[posA];
            ++posA;
        }
        else
        {
            buffer[posRes] = a[posB];
            ++posB;
            cur_inv += middle - posA + 1;
        }
        ++posRes;
    }
    while (posA <= middle)
    {
        buffer[posRes] = a[posA];
        ++posA;
        ++posRes;
    }
    while (posB <= right)
    {
        buffer[posRes] = a[posB];
        ++posB;
        ++posRes;
    }

    assert (posRes == right - left + 1);
    for (int i = left; i <= right; ++i)
        a[i] = buffer[i - left];

    return cur_inv;
}

int merge_sort (int a[], int left, int right, int buffer[])
{
    assert (left <= right);
    if (left == right)
        return 0;

    int middle = left + (right - left) / 2;

    int cur_inv = 0;
    cur_inv += merge_sort (a, left, middle, buffer);
    cur_inv += merge_sort (a, middle + 1, right, buffer);

    return cur_inv + merge (a, left, right, buffer);
}

int bubble_sort (int a[], int n)
{
    assert (n >= 0);
    int all_inv = 0;
    for (int i = 0; i < n; ++i)
        for (int j = i; j < n; ++j)
            if (a[j] < a[i])
            {
                swap (a[j], a[i]);
                ++all_inv;
            }

    return all_inv;
}

int main ()
{
    int n = 0;
    cin >> n;
    assert (n >= 0);
    int* a = new int[n],
	   * copyA = new int[n];
    for (int i = 0; i < n; ++i)
	{
        cin >> a[i];
		copyA[i] = a[i];
	}

    int* buffer = new int[n];
    cout << merge_sort (a, 0, n - 1, buffer) << ' ' << bubble_sort (copyA, n);


    delete[] a;
	delete[] copyA;
    delete[] buffer;

    return 0;
}

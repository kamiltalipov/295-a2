#include <iostream>
using std :: cin;
using std :: cout;
#include <stack>
using std :: stack;
#include <utility>
using std :: pair;
using std :: make_pair;
#include <algorithm>
using std :: sort;
using std :: swap;
using std :: min;
using std :: max;
#include <cassert>

inline int get_middle (int a, int b, int c)
{
    return max (min (a, b), min (b, c));
}

int partition (int a[], int left, int right)
{
    int x = get_middle (a[left], a[right - 1], a[(right + left) / 2]);
    int i = left, j = right - 1;
    while (i < j)
    {
        while (a[i] <= x && i < j)
            ++i;
        while (a[j] > x && j > i)
            --j;

        if (i < j)
        {
            swap (a[i], a[j]);
            ++i;
            --j;
        }
    }

    while (a[i] > x)
        --i;
    int k;
    for (k = left; k <= i; ++k)
        if (a[k] == x)
            break;
    swap (a[k], a[i]);

    return i;
}

void qsort (int a[], int left, int right)
{
    assert (left <= right);

	if (right - left < 2)
		return;
	if (right - left == 2)
	{
		if (a[left] > a[right - 1])
			swap (a[left], a[right - 1]);
		return;
	}

    int i = partition (a, left, right);
    qsort (a, left, i);
    qsort (a, i, right);
}

void qsort_non_rec (int a[], int left, int right)
{
    assert (left <= right);

    stack<pair<int, int> > st;
    st.push (make_pair (left, right));
    pair<int, int> cur;
    while (!st.empty ())
    {
        cur = st.top ();
        st.pop ();
        if (cur.second - cur.first < 2)
            continue;
        if (cur.second - cur.first == 2)
        {
            if (a[cur.first] > a[cur.second - 1])
                swap (a[cur.first], a[cur.second - 1]);
            continue;
        }

        int i = partition (a, cur.first, cur.second);
        st.push (make_pair (cur.first, i));
        st.push (make_pair (i, cur.second));
    }
}

int nth_elementh (int a[], int k, int size)
{
    assert (size >= 0);
    assert (k >= 0);
    assert (k < size);

    stack<pair<int, int> > st;
    st.push (make_pair (0, size));
    pair<int, int> cur;
    while (!st.empty ())
    {
        cur = st.top ();
        st.pop ();
        if (cur.second - cur.first < 2)
            continue;
        if (cur.second - cur.first == 2)
        {
            if (a[cur.first] > a[cur.second - 1])
                swap (a[cur.first], a[cur.second - 1]);
            continue;
        }

        int i = partition (a, cur.first, cur.second);
        if (k < i)
            st.push (make_pair (cur.first, i));
        else
            st.push (make_pair (i, cur.second));
    }

    return a[k];
}

int main ()
{
    int n = 0;
    cin >> n;
    assert (n >= 0);
    int* a = new int[n];
    for (int i = 0; i < n; ++i)
        cin >> a[i];

    qsort (a, 0, n);
    //qsort_non_rec (a, 0, n);
    for (int i = 0; i < n; ++i)
        cout << a[i] << ' ';
    //cout << nth_elementh (a, 1, n);


    delete[] a;

    return 0;
}

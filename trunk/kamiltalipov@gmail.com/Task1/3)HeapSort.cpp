#include <iostream>
using std :: cin;
using std :: cout;
#include <vector>
using std :: vector;
#include <algorithm>
using std :: swap;
using std :: sort;
#include <cassert>

class Heap
{
public:
    Heap () :
        h ()
    {
        h.push_back (0);
    }

    Heap (const vector<int>& v) :
        h ()
    {
        h.push_back (0);
        for (int i = 0; i < v.size (); ++i)
            add (v[i]);
    }

    void add (int x);
    int top () const
    {
        if (empty ())
            return -1;

        return h[1];
    }
    void pop ();
    bool empty () const
    {
        return h.size () == 1;
    }
    int size () const
    {
        return h.size () - 1;
    }

private:
    vector<int> h;

    void siff_up (int i)
    {
        int parent = i / 2;
        while (parent > 0 && h[i] < h[parent])
        {
            swap (h[i], h[parent]);

            i = parent;
            parent = i / 2;
        }
    }

    void siff_down (int i)
    {
        int child = 2 * i;
        if (child + 1 < h.size () && h[child] > h[child + 1])
            ++child;
        while (child < h.size () && h[i] > h[child])
        {
            swap (h[i], h[child]);
            i = child;
            child = 2 * i;

            if (child + 1 < h.size () && h[child] > h[child + 1])
                ++child;
        }
    }
};

void Heap :: add (int x)
{
    h.push_back (x);
    siff_up (h.size () - 1);
}

void Heap :: pop ()
{
    if (empty ())
        return;

    swap (h[1], h[h.size () - 1]);
    h.pop_back ();
    siff_down (1);
}

void heap_sort (vector<int>& a)
{
    Heap heap (a);
    for (int i = 0; i < a.size (); ++i)
    {
        a[i] = heap.top ();
        heap.pop ();
    }
}

bool is_sorted (const vector<int>& a, const vector<int>& trueSorted)
{
    if (a.size () != trueSorted.size ())
        return false;

    for (int i = 0; i < a.size (); ++i)
        if (a[i] != trueSorted[i])
            return false;

    return true;
}

int main ()
{
    int n;
    cin >> n;
    vector<int> a (n), copyA (n);
    for (int i = 0; i < n; ++i)
    {
        cin >> a[i];
        copyA[i] = a[i];
    }

    heap_sort (a);
    sort (copyA.begin (), copyA.end ());
    for (int i = 0; i < n; ++i)
        cout << a[i] << ' ';
    if (!is_sorted (a, copyA))
        cout << " - Unsorted!\n";

    return 0;
}

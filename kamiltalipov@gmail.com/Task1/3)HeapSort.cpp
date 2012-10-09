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
    }

    Heap (const vector<int>& v) :
        h ()
    {
        for (int i = 0; i < v.size (); ++i)
            add (v[i]);
    }

    void add (int x);
    int top () const
    {
        if (empty ())
            return -1;

        return h[0];
    }
    void pop ();
    bool empty () const
    {
        return h.empty ();
    }
    int size () const
    {
        return h.size ();
    }

private:
    vector<int> h;

    void sift_up (int i)
    {
        int parent = (i - 1) / 2;
        while (parent >= 0 && h[i] < h[parent])
        {
            swap (h[i], h[parent]);

            i = parent;
            parent = (i - 1) / 2;
        }
    }

    void sift_down (int i)
    {
        int child = 2 * i + 1;
        if (child + 1 < h.size () && h[child] > h[child + 1])
            ++child;
        while (child < h.size () && h[i] > h[child])
        {
            swap (h[i], h[child]);
            i = child;
            child = 2 * i + 1;

            if (child + 1 < h.size () && h[child] > h[child + 1])
                ++child;
        }
    }
};


void Heap :: add (int x)
{
    h.push_back (x);
    sift_up (h.size () - 1);
}

void Heap :: pop ()
{
    if (empty ())
        return;

    swap (h[0], h[h.size () - 1]);
    h.pop_back ();
    sift_down (0);
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

class HeapSort
{
public:
    static void sort (vector<int>& a)
    {
        make_heap (a);
        for (int i = 0; i < a.size (); ++i)
        {
            swap (a[0], a[a.size () - i - 1]);
            sift_down (a, 0, a.size () - i - 1);
        }
    }

private:
    static void make_heap (vector<int>& a)
    {
       for (int i = a.size () - 1; i >= 0; --i)
            sift_down (a, i, a.size ());
    }

    static void sift_down (vector<int>& a, int i, int realSize)
    {
        int child = 2 * i + 1;
        if (child + 1 < realSize && a[child] < a[child + 1])
            ++child;
        while (child < realSize && a[i] < a[child])
        {
            swap (a[i], a[child]);
            i = child;
            child = 2 * i + 1;

            if (child + 1 < realSize && a[child] < a[child + 1])
                ++child;
        }
    }
};


bool is_sorted (const vector<int>& a)
{
    for (int i = 1; i < a.size (); ++i)
        if (a[i] < a[i - 1])
            return false;

    return true;
}

int main ()
{
    int n;
    cin >> n;
    vector<int> a (n);
    for (int i = 0; i < n; ++i)
    {
        cin >> a[i];
    }

    HeapSort :: sort (a);
    for (int i = 0; i < n; ++i)
        cout << a[i] << ' ';
    if (!is_sorted (a))
        cout << " - Unsorted!\n";

    return 0;
}

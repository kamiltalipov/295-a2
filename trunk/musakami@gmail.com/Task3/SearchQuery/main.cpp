#include <iostream>
#include <vector>
#include <limits>
#include <string>
#include <string.h>
#include <algorithm>

using namespace std;

template<typename Value_Type>
class Heap
{
private:
    vector<Value_Type > data;
    int size;

    void MemoryCheck()
    {
        if (size > data.size())
            data.resize(data.size() * 2 + 1);
        if (size != 0 && size <= data.size() / 4)
        {
            data.resize(data.size() / 2);
            vector<Value_Type > temp = data;
            data.swap(temp);
        }
    }
public:
    Heap()
    {
        size = 0;
        data.resize(1);
    }

    Heap(vector<Value_Type> initializer)
    {
        data = initializer;
        size = data.size();
        if (size == 0)
            data.resize(1);
        Heapify(data);
    }

    void Clear()
    {
        size = 0;
        data.resize(1);
        vector<Value_Type> temp = data;
        data.swap(temp);
    }

    static void SeefDown(int index, vector<Value_Type> &data, int size)
    {
        index++;
        bool check = true;
        while (index << 1 <= size && check)
        {
            check = false;
            index <<= 1;
            if (data[index - 1] > data[(index >> 1) - 1])
                if (index == size || data[index - 1] >= data[index])
                {
                    swap(data[index - 1], data[(index >> 1) - 1]);
                    check = true;
                }
            if (index < size && data[index] > data[(index >> 1) - 1])
                if (data[index] > data[index - 1])
                {
                    swap(data[index], data[(index >> 1) - 1]);
                    index++;
                    check = true;
                }
        }
    }

    static void Heapify(vector<Value_Type> &v)
    {
        for (int i = v.size(); i >= 0; i--)
        {
            SeefDown(i, v, v.size());
        }
    }

    void Add(Value_Type value)
    {
        size++;
        MemoryCheck();
        data[size - 1] = value;
        int index = size;
        while (index != 1 && data[(index >> 1) - 1] < data[index - 1])
        {
            swap(data[(index >> 1) - 1], data[index - 1]);
            index >>= 1;
        }
    }

    Value_Type Top()
    {
        if (size > 0)
            return data[0];
        return -1;
    }

    void Pop()
    {
        if (size > 0)
        {
            size--;
            swap(data[0], data[size]);
            SeefDown(0, data, size);
            MemoryCheck();
        }
    }

    void ToSorted(vector<int> &result)
    {
        result.clear();
        result.reserve(size);
        int n = size;
        for (int i = 0; i < n; i++)
        {
            result.push_back(Top());
            Pop();
        }
    }

    bool Empty()
    {
        return size == 0;
    }
};

class Tree
{
    struct HeapInformation
    {
        int value;
        int index;
        int position;
        int left;
        int right;

        HeapInformation(int value = 0, int index = 0, int position = 0, int left = 0, int right = 0):
            value(value), index(index), position(position), left(left), right(right) {};

        bool operator <(const HeapInformation &other) const
        {
            return value < other.value;
        }

        bool operator >(const HeapInformation &other) const
        {
            return value > other.value;
        }

        bool operator >=(const HeapInformation &other) const
        {
            return value > other.value;
        }
    };

    HeapInformation MakeInfo(int value, int index, int position, int left, int right)
    {
        HeapInformation result(value, index, position, left, right);
        return result;
    }

    int size;
    int size_2;
    vector<int> data;
    vector<int> values;
    vector<int> left, right;

    int findmax(int index, int l, int r, int &lq, int &rq)
    {
        if (r < lq || l > rq)
            return numeric_limits<int>::min();
        if (l >= lq && r <= rq)
            return data[index];
        else
        {
            int maxleft = findmax(index << 1, l, (l + r) / 2, lq, rq);
            int maxright = findmax((index << 1) + 1, (l + r) / 2 + 1, r, lq, rq);
            if (values[maxleft] >= values[maxright])
                return maxleft;
            else
                return maxright;
        }
    }

    void part(int index, int l, int r, int &lq, int &rq, Heap<HeapInformation> &h)
    {
        if (r < lq || l > rq)
            return;
        if (l >= lq && r <= rq)
            h.Add(MakeInfo(values[data[index]], index, data[index], l, r));
        else
        {
            part(index << 1, l, (l + r) / 2, lq, rq, h);
            part((index << 1) + 1, (l + r) / 2 + 1, r, lq, rq, h);
        }
    }

public:

    Tree(int n)
    {
        int k = 1;
        for (; k < n; k <<= 1);
        size_2 = k;
        size = k << 1;
        data.resize(size);
        for (int i = size_2; i < size; i++)
            data[i] = i - size_2;
        values.resize(size_2);
        for (int i = size_2 - 1; i > 0; i--)
        {
            if (values[data[i << 1]] >= values[data[(i << 1) + 1]])
                data[i] = data[i << 1];
            else
                data[i] = data[(i << 1) + 1];
        }
    }

    int Max(int lq, int rq)
    {
        return findmax(1, 0, size_2 - 1, lq, rq);
    }

    int Max_k(int lq, int rq, int k, vector<int> &ans)
    {
        Heap<HeapInformation> h;
        part(1, 0, size_2 - 1, lq, rq, h);
        for (int i = 0; i < k && !h.Empty(); i++)
        {
            HeapInformation result = h.Top();
            h.Pop();
            ans.push_back(result.position);
            int rqnew = result.position - 1;
            int lqnew = result.position + 1;
            part(result.index, result.left, result.right, lq, rqnew, h);
            part(result.index, result.left, result.right, lqnew, rq, h);
        }
    }

    void Set(int index, int value)
    {
        values[index] = value;
        index = size_2 + index;
        while (index != 1)
        {
            index >>= 1;
            if (values[data[index << 1]] >= values[data[(index << 1) + 1]])
                data[index] = data[index << 1];
            else
                data[index] = data[(index << 1) + 1];
        }
    }
};

struct Compare
{
    int l;

    bool operator ()(const string &a, const string &b) const
    {
        for (int i = 0; i < l; i++)
        {
            if (i >= a.length())
                return true;
            if (i >= b.length())
                return false;
            if (a[i] < b[i])
                return true;
            if (a[i] > b[i])
                return false;
        }
        return false;
    }
};

int main()
{
    vector<pair<string, int> > v;
    int n;
    cin >> n;
    Tree t(n);
    for (int i = 0; i < n; i++)
    {
        string s;
        int k;
        cin >> s >> k;
        v.push_back(make_pair(s, k));
    }
    sort(v.begin(), v.end());
    for (int i = 0; i < n; i++)
    {
        t.Set(i, v[i].second);
    }
    int m;
    cin >> m;
    string s;
    cin >> s;
    Compare comp;
    comp.l = s.length();
    int l = -1;
    int r = n;
    while (r - l > 1)
    {
        int j = (l + r) / 2;
        if (comp(v[j].first, s))
            l = j;
        else
            r = j;
    }
    int lq = l + 1;
    l = -1;
    r = n;
    while (r - l > 1)
    {
        int j = (l + r) / 2;
        if (comp(s, v[j].first))
            r = j;
        else
            l = j;
    }
    int rq = r - 1;
    vector<int> answer;
    t.Max_k(lq, rq, m, answer);
    for (int i = 0; i < answer.size(); i++)
    {
        cout << v[answer[i]].first << endl;
    }
    return 0;
}

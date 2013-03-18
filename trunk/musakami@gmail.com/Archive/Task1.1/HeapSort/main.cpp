#include <iostream>
#include <vector>

using namespace std;

class Heap
{
private:
    vector<int> data;
    int size;

    void MemoryCheck()
    {
        if (size > data.size())
            data.resize(data.size() * 2 + 1);
        if (size != 0 && size <= data.size() / 4)
        {
            data.resize(data.size() / 2);
            vector<int> temp = data;
            data.swap(temp);
        }
    }
public:
    Heap()
    {
        size = 0;
        data.resize(1);
    }

    Heap(vector<int> initializer)
    {
        data = initializer;
        size = data.size();
        if (size == 0)
            data.resize(1);
        Heapify(data);
    }

    static void SeefDown(int index, vector<int> &data, int size)
    {
        index++;
        bool check = true;
        while (index << 1 <= size && check)
        {
            check = false;
            index <<= 1;
            if (data[index - 1] < data[(index >> 1) - 1])
                if (index == size || data[index - 1] <= data[index])
                {
                    swap(data[index - 1], data[(index >> 1) - 1]);
                    check = true;
                }
            if (index < size && data[index] < data[(index >> 1) - 1])
                if (data[index] < data[index - 1])
                {
                    swap(data[index], data[(index >> 1) - 1]);
                    index++;
                    check = true;
                }
        }
    }

    static void Heapify(vector<int> &v)
    {
        for (int i = v.size(); i >= 0; i--)
        {
            SeefDown(i, v, v.size());
        }
    }

    void Add(int value)
    {
        size++;
        MemoryCheck();
        data[size - 1] = value;
        int index = size;
        while (index != 1 && data[(index >> 1) - 1] > data[index - 1])
        {
            swap(data[(index >> 1) - 1], data[index - 1]);
            index >>= 1;
        }
    }

    int Top()
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

void HeapSort(vector<int> &data)
{
    Heap::Heapify(data);
    for (int i = 1; i < data.size(); i++)
    {
        swap(data[0], data[data.size() - i]);
        Heap::SeefDown(0, data, data.size() - i);
    }
    for (int i = 0; i < data.size() / 2; i++)
        swap(data[i], data[data.size() - i - 1]);
}

int main()
{
    int n;
    vector<int> v;
    Heap h;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int readable;
        cin >> readable;
        v.push_back(readable);
        h.Add(readable);
    }
    HeapSort(v);
    for (int i = 0; i < n; i++)
        cout << v[i] << " ";
    cout << endl;
    while (!h.Empty())
    {
        cout << h.Top() << " ";
        h.Pop();
    }
    return 0;
}

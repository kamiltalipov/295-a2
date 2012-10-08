#include <iostream>
#include <vector>
#include <list>

using namespace std;

class HashTable
{
#define lists list<string>
private:
    lists *data;
    int m;
    int size;
    unsigned long long hashpow;

    void Reallocate(int newm)
    {
        lists *fresh = new lists[newm];
        for (int i = 0; i < m; i++)
            for (lists::iterator j = data[i].begin(); j != data[i].end(); j++)
            {
                unsigned long long h = hash(*j);
                fresh[h].push_back(*j);
            }
        m = newm;
        delete [] data;
        data = fresh;
    }

    void MemoryCheck()
    {
        if (size > 3 * m / 4)
        {
            Reallocate(m << 1);
        }
        if (m != 1 << 7 && size < m >> 3)
        {
            Reallocate(m >> 1);
        }
    }

    unsigned long long hash(string &s)
    {
        unsigned long long result = 1;
        for (int i = 0; i < s.length(); i++)
        {
            result = result * hashpow + s[i];
        }
        return result % m;
    }

public:

    class iterator
    {
    private:
        HashTable *table;
        int index;
        lists::iterator object;

        void next()
        {
            object++;
            if (object == table -> data[index].end())
            {
                do
                    index++;
                while (index < table -> m && table -> data[index].size() == 0);
                if (index < table -> m)
                    object = table -> data[index].begin();
                else
                    object = table -> data[index - 1].begin();
            }
        }

    public:
        iterator(HashTable *p, int i, lists::iterator o)
        {
            index = i;
            table = p;
            object = o;
        }

        iterator operator++(int)
        {
            iterator returnvalue = *this;
            next();
            return returnvalue;
        }

        iterator operator++()
        {
            next();
            return *this;
        }

        string operator *()
        {
            return *object;
        }

        bool operator ==(const iterator &other)const
        {
            if (other.table == table && other.index == index && other.object == object)
                return true;
            else
                return false;
        }

        bool operator !=(const iterator &other)const
        {
            if (other.table == table && other.index == index && other.object == object)
                return false;
            else
                return true;
        }
    };

    HashTable()
    {
        m = 1 << 7;
        hashpow = 37;
        data = new lists[m];
        size = 0;
    }

    void Add(string &s)
    {
        unsigned long long h = hash(s);
        int check = true;
        for (lists::iterator i = data[h].begin(); i != data[h].end(); i++)
        {
            if (s == *i)
            {
                check = false;
                break;
            }
        }
        if (check)
        {
            data[h].push_back(s);
            size++;
            MemoryCheck();
        }
    }

    void Erase(string &s)
    {
        unsigned long long h = hash(s);
        for (lists::iterator i = data[h].begin(); i != data[h].end(); i++)
        {
            if (s == *i)
            {
                size--;
                data[h].erase(i);
                MemoryCheck();
                break;
            }
        }
    }

    bool Find(string &s)
    {
        unsigned long long h = hash(s);
        for (lists::iterator i = data[h].begin(); i != data[h].end(); i++)
        {
            if (s == *i)
            {
                return true;
            }
        }
        return false;
    }

    int CountCollision()
    {
        int mcollide = 0;
        for (int i = 0; i < m; i++)
            if (data[i].size() > mcollide)
                mcollide = data[i].size();
        return max(0, mcollide - 1);
    }

    iterator begin()
    {
        int index = 0;
        while (index < m && data[index].size() == 0)
            index++;
        if (index < m)
        {
            iterator result(this, index, data[index].begin());
            return result;
        }
        else
        {
            iterator result(this, index, data[index - 1].begin());
            return result;
        }
    }

    iterator end()
    {
        iterator result(this, m, data[m - 1].begin());
        return result;
    }

};

int main()
{
    HashTable table;
    int n;
    cout << "n:";
    cin >> n;
    cout << "0 - Add 1 - Erase 2 - Find\n";
    for (int i = 0; i < n; i++)
    {
        int readable1;
        string readable2;
        cin >> readable1 >> readable2;
        if (readable1 == 0)
            table.Add(readable2);
        if (readable1 == 1)
            table.Erase(readable2);
        if (readable1 == 2)
            cout << (table.Find(readable2) ? "Yes": "No") << endl;
    }
    cout << table.CountCollision() << endl;
    for (HashTable::iterator i = table.begin(); i != table.end(); i++)
    {
        cout << *i << endl;
    }
    return 0;
}


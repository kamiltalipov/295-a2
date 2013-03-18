#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>
#include <algorithm>
#include <list>

using namespace std;

class BloomFilter
{
#define ull unsigned long long
private:
    vector<bool> data;
    ull hashpow1, hashpow2;
    int hashcount;
    int m;

    pair<ull, ull> hash(string &s)
    {
        ull first = 1;
        ull second = 1;
        for (int i = 0; i < s.length(); i++)
        {
            first = first * hashpow1 + s[i];
            second = second * hashpow2 + s[i];
        }
        return make_pair(first, second);
    }
public:

    BloomFilter(int m, int k):
        m(m), data(m), hashcount(k), hashpow1(23), hashpow2(41) {};

    void Add(string &s)
    {
        pair<ull, ull> h = hash(s);
        for (int i = 0; i < hashcount; i++)
        {
            ull position = (h.first + i * h.second) % m;
            data[position] = true;
        }
    }

    bool Find(string &s)
    {
        pair<ull, ull> h = hash(s);
        for (int i = 0; i < hashcount; i++)
        {
            ull position = (h.first + i * h.second) % m;
            if (!data[position])
                return false;
        }
        return true;
    }
};

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
        int oldm = m;
        m = newm;
        lists *fresh = new lists[newm];
        for (int i = 0; i < oldm; i++)
            for (lists::iterator j = data[i].begin(); j != data[i].end(); j++)
            {
                unsigned long long h = hash(*j);
                fresh[h].push_back(*j);
            }
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
    BloomFilter bf(1000000, 10);
    HashTable ht;
    ifstream input;
    input.open("text.txt");
    string s;
    while (input >> s)
    {
        int i = 0;
        int j = s.length() - 1;
        while (i < s.length() && (s[i] < 'a' || s[i] > 'z') && (s[i] < 'A' || s[i] > 'Z'))
            i++;
        while (j >= 0 && (s[j] < 'a' || s[j] > 'z') && (s[j] < 'A' || s[j] > 'Z'))
            j--;
        if (j >= i)
        {
            s = s.substr(i, j - i + 1);
            for (int k = 0; k < s.length(); k++)
                s[k] = tolower(s[k]);
            bf.Add(s);
            ht.Add(s);
        }
    }
    input.close();
    input.open("text2.txt");
    int count = 0, notfound = 0;
    while (input >> s)
    {
        int i = 0;
        int j = s.length() - 1;
        while (i < s.length() && (s[i] < 'a' || s[i] > 'z') && (s[i] < 'A' || s[i] > 'Z'))
            i++;
        while (j >= 0 && (s[j] < 'a' || s[j] > 'z') && (s[j] < 'A' || s[j] > 'Z'))
            j--;
        if (j >= i)
        {
            s = s.substr(i, j - i + 1);
            for (int k = 0; k < s.length(); k++)
                s[k] = tolower(s[k]);
            bool bloomcheck = bf.Find(s);
            bool hashcheck = ht.Find(s);
            if (!bloomcheck)
            {
                cout << s << endl;
                notfound++;
            }
            if (bloomcheck != hashcheck)
                count++;
        }
    }
    cout << count << endl << notfound;
    return 0;
}

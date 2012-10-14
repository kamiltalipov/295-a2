#include <fstream>
using std :: ifstream;
#include <iostream>
using std :: cin;
using std :: cout;
#include <utility>
using std :: pair;
using std :: make_pair;
#include <string>
using std :: string;
#include <vector>
using std :: vector;
#include <list>
using std :: list;
#include <cassert>


class BloomFiltr
{
public:
    BloomFiltr (size_t tableSize, size_t allHashFunc)
        :
        a (tableSize),
        allHashFunc (allHashFunc)
    {
    }

    void add (const string& s);
    bool find (const string& s) const;

private:
    vector<bool> a;
    size_t allHashFunc;

	BloomFiltr ()
	{
	}

    unsigned int hash (const string& s, int base) const
    {
        unsigned int res = 0;
        for (size_t i = 0; i < s.size (); ++i)
        {
            res *= base;
            res += s[i] - 'A';
        }

        return res % a.size ();
    }

};

void BloomFiltr :: add (const string& s)
{
    unsigned int h1 = hash (s, 37),
                  h2 = hash (s, 31);
    unsigned int cur_h = h1;
    for (size_t i = 0; i < allHashFunc; ++i)
    {
        a[cur_h] = true;
        cur_h = (cur_h + h2) % a.size ();
    }

    return;
}

bool BloomFiltr :: find (const string& s) const
{
    bool res = true;
    unsigned int h1 = hash (s, 37),
                  h2 = hash (s, 31);
    unsigned int cur_h = h1;
    for (size_t i = 0; i < allHashFunc; ++i)
    {
        res = res && a[cur_h];
        cur_h = (cur_h + h2) % a.size ();
    }

    return res;
}

unsigned int hash (const string& s, unsigned int base = 37)
{
    unsigned int res = 0;
    for (size_t i = 0; i < s.size (); ++i)
    {
        res *= base;
        res += s[i] - 'a';
    }

    return res;
}

class HashTable
{
public:
    HashTable (size_t size = 100)
        :
        table (size),
        begin_ (make_pair (table.begin (), table[0].begin ()), table.begin ()),
        end_ (make_pair (table.begin (), table[0].end ()), table.begin ()),
        allAddElem (0)
    {
    }

    class iterator
    {
    public:
        friend class HashTable;

        iterator ()
        {
        }

        iterator& operator ++ ()
        {
            if (pos.second != pos.first->end ())
                ++pos.second;
            if (pos.second == pos.first->end ())
            {
                while (pos.first != endTable && pos.first->empty ())
                    ++pos.first;

                if (pos.first != endTable)
                    pos.second = pos.first->begin ();
                else
                    pos.second = endTable->end ();
            }

            return *this;
        }

        iterator& operator ++ (int)
        {
            if (pos.second != pos.first->end ())
                ++pos.second;
            if (pos.second == pos.first->end ())
            {
                while (pos.first != endTable && pos.first->empty ())
                    ++pos.first;

                if (pos.first != endTable)
                    pos.second = pos.first->begin ();
                else
                    pos.second = endTable->end ();
            }

            return *this;
        }

        bool operator == (const iterator& it)
        {
            return pos == it.pos && endTable == it.endTable;
        }

        bool operator != (const iterator& it)
        {
            return pos != it.pos || endTable != it.endTable;
        }

        string& operator* ()
        {
            return *pos.second;
        }

        string* operator -> ()
        {
            return &(*pos.second);
        }

    private:
        pair<vector<list<string> >::iterator, list<string>::iterator> pos;
        vector<list<string> > :: iterator endTable;

        iterator (const pair<vector<list<string> >::iterator, list<string>::iterator >& p,
                  const vector<list<string> > :: iterator& end)
            :
            pos (p),
            endTable (end)
        {
        }
    };

    iterator begin ()
    {
        return begin_;
    }

    iterator end ()
    {
        return end_;
    }

    iterator add (const string& s)
    {
        ++allAddElem;
        return findAndAdd (s, true, table.size ());
    }

    iterator find (const string& s)
    {
        return findAndAdd (s, false, table.size ());
    }

    iterator remove (const string& s)
    {
        iterator where = find (s);
        if (where == end_)
            return end_;

        --allAddElem;
        if (allAddElem <  table.size () / 2 && allAddElem > 20)
            resize (table.size () / 2);
        where = find (s);
        where.pos.second = where.pos.first->erase (where.pos.second);
        if (where.pos.second == where.pos.first->end ())
            ++where;

        return where;
    }

private:
    vector<list<string> > table;
    iterator begin_, end_;
    size_t allAddElem;

    void resize (size_t newSize)
    {
        assert (newSize > 0);
        string tmp;
        unsigned int realAllAddElem = allAddElem;
        allAddElem = 0;
        for (vector<list<string> > :: iterator i = table.begin (); i != table.end (); ++i)
                for (list<string> :: iterator j = i->begin (); j != i->end (); ++j)
                {
                    tmp = *j;
                    i->erase (j);
                    findAndAdd (tmp, true, newSize);
                }

        table.resize (newSize);
        allAddElem = realAllAddElem;
        end_.pos = make_pair (table.end (), table.end ()->end ());
        end_.endTable = table.end ();
    }

    iterator findAndAdd (const string& s, bool needAdd, unsigned int realSize);
};

HashTable :: iterator HashTable :: findAndAdd (const string& s, bool needAdd, unsigned int realSize)
{
    unsigned int curHash = hash (s) % realSize;
    if (needAdd && allAddElem >= 4 * realSize)
        resize (4 * realSize);

    list<string> :: iterator where;
    if (table[curHash].empty ())
    {
        if (!needAdd)
            return end_;

        table[curHash].push_front (s);
        where = table[curHash].begin ();
    }
    else
    {
        for (where = table[curHash].begin (); where != table[curHash].end (); ++where)
            if ((*where) == s)
                break;
        if (where == table[curHash].end ())
        {
            if (!needAdd)
                return end_;

            table[curHash].push_front (s);
            where = table[curHash].begin ();
            --allAddElem;
        }
    }

    return iterator (make_pair (table.begin () + curHash, where), table.end ());
}

inline bool is_not_sep (char c)
{
	return c != '!' && c != '?' && c != ',' && c != '-' && 
		   c != ':' && c != '.' && c != ';';
}

void split (const string& str, vector<string>& v)
{
	v.clear ();
	string sep_char ("!?,-:.;");
	size_t begin = 0, end = str.find_first_of (sep_char);
	while (begin < str.size ())
	{
		while (begin < str.size () && !is_not_sep (str[begin]))
			{
				if (end != string :: npos)
					begin = end + 1;
				else
					begin = str.size ();

				end = str.find_first_of (sep_char, begin);
			}

		if (begin < str.size () && is_not_sep (str[begin]))
		{
			v.push_back (str.substr (begin, end - begin));
			if (end != string :: npos)
				begin = end + 1;
			else
				begin = str.size ();
			end = str.find_first_of (sep_char, begin);
		}
	}
}

int main ()
{	
	ifstream input ("dict.txt");
	
	string str;
	vector<string> res;
	BloomFiltr b (10000, 5);
	HashTable h;
	while (input >> str)
	{
		split (str, res);
		for (size_t i = 0; i < res.size (); ++i)
		{
			b.add (res[i]);
			h.add (res[i]);
		}
	}
	
	ifstream input2 ("input.txt");
	unsigned int allDictWordBloom = 0, allDictWordHash = 0,
				 allWord = 0;
	while (input2 >> str)
	{
		split (str, res);
		allWord += res.size ();
		for (size_t i = 0; i < res.size (); ++i)
		{
			if (b.find (res[i]))
				++allDictWordBloom;
			if (h.find (res[i]) != h.end ())
				++allDictWordHash;
		}
	}
	
	cout << "All word: " << allWord << '\n';
	cout << "By Bloom filtr: " << allDictWordBloom << '\n';
	cout << "By HashTable: " << allDictWordHash << '\n';
	cout << "Bloom filtr errors: " << allDictWordHash - allDictWordBloom << '\n';
	
	cin.get ();

    return 0;
}

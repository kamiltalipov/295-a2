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
        allAddElem (0), maxCollision (1),
		begin_ (make_pair (table.end (), table[size - 1].end ()), table.end ()),
		end_ (make_pair (table.end (), table[size - 1].end ()), table.end ())
    {
    }

    class iterator
    {
		friend class HashTable;
    public:

        iterator ()
        {
        }

        iterator& operator ++ ()
        {
            if (pos.second != pos.first->end ())
                ++pos.second;
            if (pos.second == pos.first->end ())
            {
				++pos.first;
                while (pos.first < endTable && pos.first->empty ())
                    ++pos.first;
			
                if (pos.first < endTable)
                    pos.second = pos.first->begin ();
            }

            return *this;
        }

        iterator& operator ++ (int)
        {
            if (pos.second != pos.first->end ())
                ++pos.second;
            if (pos.second == pos.first->end ())
            {
				++pos.first;
                while (pos.first < endTable && pos.first->empty ())
                    ++pos.first;
			
                if (pos.first < endTable)
                    pos.second = pos.first->begin ();
            }

            return *this;
        }

        bool operator == (const iterator& it)
        {
			if (pos.first == endTable)
				return pos.first == it.pos.first;
            return pos == it.pos;
        }

        bool operator != (const iterator& it)
        {
			if (pos.first == endTable)
				return pos.first != it.pos.first;
            return pos != it.pos;
        }

        string& operator * ()
        {
            return *pos.second;
        }

        string* operator -> ()
        {
            return &(*pos.second);
        }

    private:
        pair<vector<list<string> > :: iterator, list<string> :: iterator> pos;
        vector<list<string> > :: iterator endTable;

        iterator (const pair<vector<list<string> > :: iterator, list<string> :: iterator >& p,
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

	unsigned int getMaxCollision () const
	{
		return maxCollision - 1;
	}

private:
    vector<list<string> > table;
    iterator begin_, end_;
    size_t allAddElem;
	unsigned int maxCollision;

    void resize (size_t newSize)
    {
        assert (newSize > 0);
        string tmp;
        unsigned int realAllAddElem = allAddElem;
        allAddElem = 2;
		table.resize (newSize);
		begin_.pos.first = table.end ();
		begin_.endTable = table.end ();
        for (vector<list<string> > :: iterator i = table.begin (); i != table.end (); ++i)
                for (list<string> :: iterator j = i->begin (); j != i->end ();)
                {
                    tmp = *j;
                    j = i->erase (j);
                    findAndAdd (tmp, true, newSize);
                }

        
        allAddElem = realAllAddElem;
		end_.pos.first = table.end ();
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
			{
                break;
				--allAddElem;
			}
        if (where == table[curHash].end ())
        {
            if (!needAdd)
                return end_;

            table[curHash].push_front (s);
            where = table[curHash].begin ();
        }
    }
	
	if (needAdd && (allAddElem == 1 || table.begin () + curHash <= begin_.pos.first))
	{
			begin_.pos.first = table.begin () + curHash;
			begin_.pos.second = (table.begin () + curHash)->begin ();
			
			if (allAddElem == 1)
			{
				end_.pos.first = table.end ();
			}
	}
	if (needAdd)
	{
		unsigned int curCollision = table[curHash].size ();
		if (maxCollision < curCollision)
			maxCollision = curCollision;
	}
	

    return iterator (make_pair (table.begin () + curHash, where), table.end ());
}

int main ()
{
    HashTable h;
    h.add ("123");
    h.add ("1234");
    h.add ("1214324");
    h.add ("gggg");
    if (h.find ("1234") != h.end ())
        cout << "YES\n";
    if (h.find ("fsdfsdfsdf") == h.end ())
		cout << "NO\n";
	
    for (HashTable :: iterator i = h.begin (); i != h.end (); ++i)
        cout << *i << '\n';

	cout << h.getMaxCollision () << '\n';
	cin.get ();

    return 0;
}

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cassert>
#include <crtdbg.h>

using namespace std;

class HashTable
{
public:
	HashTable();
	//~HashTable();
	void Add(string &s);
	void Remove(string &s);
	bool Find(string& s);
	
	class iterator
	{
		vector < list <pair <string, int> > >::iterator vector_it;
		list < pair <string, int> >::iterator list_it;
		HashTable* container;
	public:
		iterator(iterator& other_it)
		{
			container = other_it.container;
			vector_it = other_it.vector_it;
			list_it = other_it.list_it;
		}
		iterator(HashTable* HT, vector < list <pair <string, int > > >::iterator v_it, list <pair <string, int> >::iterator l_it)
		{
			container = HT;
			vector_it = v_it;
			list_it = l_it;
		}

		iterator& operator++()
		{
			if (list_it != (*vector_it).end())
				++list_it;
			if (list_it == (*vector_it).end())
			{
				for (vector_it = vector_it + 1; vector_it != (container->table).end(); vector_it++)
				{
					if ((*vector_it).size() > 0)
					{
						list_it = (*vector_it).begin();
						return *this;
					}

				}
				if (vector_it == (container->table).end())
					list_it = (*(vector_it - 1)).end();
			}
			return *this;
		}

		iterator& operator--()
		{
			if (vector_it == (container->table).end() || list_it == (*vector_it).begin())
			{
				for (vector_it = vector_it - 1; vector_it != (container->table).begin(); vector_it--)
				{
					if ((*vector_it).size() > 0)
						break;
				}
				if ((*vector_it).size() > 0)
					list_it = --(*vector_it).end();
				else
					list_it = (*vector_it).begin();
			}
			else
				--list_it;

			return *this;
		}

		bool operator!=(iterator other_it)
		{
			return !(vector_it == other_it.vector_it && list_it == other_it.list_it);
		}

		pair <string, int>& operator*()
		{
			return (*list_it);
		}

		pair <string, int>* operator->()
		{
			return &(*list_it);
		}
	};

	iterator begin();
	iterator end();


private:
	
	void realloc(int new_size);
	bool is_prime(int number);
	unsigned long long hash(string &s);

	static const int INITSIZE = 3;
	static const unsigned long long POWER = 37;
	int size;
	int number_of_elements;
	vector < list <pair <string, int> > > table;
};

HashTable::HashTable()
{
	number_of_elements = 0;
	size = INITSIZE;
	table.resize(size);
}

HashTable::iterator HashTable::begin()
{
	for (vector < list <pair <string, int> > >::iterator it = table.begin(); it != table.end(); it++)
	{
		if ((*it).size() > 0)
			return iterator(this, it, (*it).begin());
	}
	return iterator(this, table.end(), (*--table.end()).end());
}

HashTable::iterator HashTable::end()
{
	return iterator(this, table.end(), (*--table.end()).end());
}

unsigned long long HashTable::hash(string& s)
{
	unsigned long long h = 0;
	for (int i = 0; i < s.size(); i++)
		h += h * POWER + s[i];
	return h;
}

bool HashTable::is_prime(int number)
{
	for (int i = 2; i * i <= number; i++)
	{
		if (number % i == 0)
			return 0;
	}
	return 1;
}

void HashTable::realloc(int new_size)
{	
	while (!is_prime(new_size))
		++new_size;
	vector < list <pair <string, int> > > copy_table;
	copy_table.resize(new_size);
	size = new_size;
	for (HashTable::iterator it = begin(); it != end(); it++)
	{
		copy_table[hash((*it).first) % size].push_back(*it);
	}
	swap(table, copy_table);
}

void HashTable::Add(string& s)
{
	unsigned long long h = hash(s);
	int index = h % size;
	for (list <pair <string, int> >::iterator it = table[index].begin(); it != table[index].end(); it++)
	{
		if ((*it).first == s)
		{
			++(*it).second;
			return;
		}
	}
	table[index].push_back(make_pair(s, 1));
	++number_of_elements;
	if (number_of_elements > 4 * size)
		realloc(8 * size);
}

void HashTable::Remove(string& s)
{
	unsigned long long h = hash(s);
	int index = h % size;
	for (list <pair <string, int> >::iterator it = table[index].begin(); it != table[index].end(); it++)
	{
		if ((*it).first == s)
		{
			table[index].erase(it);
			--number_of_elements;
			return;
		}
	}
}

bool HashTable::Find(string& s)
{
	unsigned long long h = hash(s);
	int index = h % size;
	for (list <pair <string, int> >::iterator it = table[index].begin(); it != table[index].end(); it++)
	{
		if ((*it).first == s)
			return true;
	}
	return false;
}
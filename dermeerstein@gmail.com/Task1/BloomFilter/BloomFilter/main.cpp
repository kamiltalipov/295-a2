#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <iterator>
#include <cassert>
#include <crtdbg.h>
#include <cstdio>
#include <cctype>

using namespace std;

class HashTable
{
public:
	HashTable();
	//~HashTable();
	void Add(string &s);
	bool Find(string& s);
	
	class iterator:public std::iterator<bidirectional_iterator_tag, vector < list <string> > >
	{
		vector < list <string> >::iterator vector_it;
		list <string>::iterator list_it;
		HashTable* container;
	public:
		iterator(iterator& other_it)
		{
			container = other_it.container;
			vector_it = other_it.vector_it;
			list_it = other_it.list_it;
		}
		iterator(HashTable* HT, vector < list <string> >::iterator v_it, list <string>::iterator l_it)
		{
			container = HT;
			vector_it = v_it;
			list_it = l_it;
		}

		iterator& operator++()
		{
			++list_it;
			for (;list_it != (*vector_it).end(); ++list_it)
			{
				return *this;
			}
			++vector_it;
			for (;vector_it != (container->table).end(); ++vector_it)
			{
				for (list_it = (*vector_it).begin(); list_it != (*vector_it).end(); ++list_it)
				{
					return *this;
				}
			}
			return *this;
		}

		iterator& operator--()
		{
			if (vector_it == (container->table).end() || list_it == (*vector_it).begin())
			{
				--vector_it;
				for (;vector_it != (container->table).begin(); --vector_it)
				{
					if ((*vector_it).size() > 0)
					{
						for (list_it = --(*vector_it).end(); list_it != (*vector_it).begin(); --list_it)
						{
							return *this;
						}
						return *this;
					}
				}
				if ((*vector_it).size() > 0)
				{
					for (list_it = --(*vector_it).end(); list_it != (*vector_it).begin(); --list_it)
					{
						return *this;
					}
					return *this;
				}
			}
			else
				--list_it;
		}

		bool operator!=(iterator other_it)
		{
			return !(vector_it == other_it.vector_it && list_it == other_it.list_it);
		}

		string& operator*()
		{
			return (*list_it);
		}

		string* operator->()
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
	vector < list <string> > table;
	vector < list <string> > copy_table;
};

HashTable::HashTable()
{
	number_of_elements = 0;
	size = INITSIZE;
	table.resize(size);
}

HashTable::iterator HashTable::begin()
{
	for (vector < list <string> >::iterator it = table.begin(); it != table.end(); it++)
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
	copy_table.resize(new_size);
	size = new_size;
	for (HashTable::iterator it = begin(); it != end(); it++)
	{
		copy_table[hash(*it) % size].push_back(*it);
	}
	table =	copy_table;
	copy_table.clear();
}

void HashTable::Add(string& s)
{
	unsigned long long h = hash(s);
	int index = h % size;
	for (list <string>::iterator it = table[index].begin(); it != table[index].end(); it++)
	{
		if (*it == s)
			return;
	}
	table[index].push_back(s);
	++number_of_elements;
	if (number_of_elements > 4 * size)
		realloc(8 * size);
}

bool HashTable::Find(string& s)
{
	unsigned long long h = hash(s);
	int index = h % size;
	for (list <string>::iterator it = table[index].begin(); it != table[index].end(); it++)
	{
		if (*it == s)
			return true;
	}
	return false;
}


class BloomFilter
{
public:
	BloomFilter();
	void Add(string& s);
	bool Find(string &s);
private:
	static const int SIZE = 1e+7 + 7;
	static const int HASH_NUM = 7;
	static const unsigned long long POWER1 = 37;
	static const unsigned long long POWER2 = 29;
	vector <bool> filter;
	
	unsigned long long hash1(string& s);
	unsigned long long hash2(string& s);
};


BloomFilter::BloomFilter()
{
	filter.resize(SIZE);
}


unsigned long long BloomFilter::hash1(string& s)
{
	unsigned long long h = 0;
	for (int i = 0; i < s.size(); i++)
	{
		h += h * POWER1 + s[i];
	}
	return h;
}

unsigned long long BloomFilter::hash2(string& s)
{
	unsigned long long h = 0;
	for (int i = 0; i < s.size(); i++)
	{
		h += h * POWER2 + s[i];
	}
	return h;
}

/*unsigned long long BloomFilter::hash_i(string& s, int i)
{
	return (hash1(s) + i * hash2(s)) % (unsigned long long) SIZE;
}*/

void BloomFilter::Add(string& s)
{
	unsigned long long h1 = hash1(s);
	unsigned long long h2 = hash2(s);
	int index;
	for (int i = 0; i < HASH_NUM; i++)
	{
		index = (h1 + i * h2) % SIZE;
		filter[index] = 1;
	}
}

bool BloomFilter::Find(string& s)
{
	unsigned long long h1 = hash1(s);
	unsigned long long h2 = hash2(s);
	int index;
	for (int i = 0; i < HASH_NUM; i++)
	{
		index = (h1 + i * h2) % SIZE;
		if (!filter[index])
			return 0;
	}
	return 1;
}

string lower(string &s)
{
	string result;
	for (int i = 0; i < s.size(); i++)
		result += (islower(s[i]) ? s[i] : tolower(s[i]));
	return result;
}

int main()
{
	BloomFilter* BF = new BloomFilter;
	HashTable* HT = new HashTable;
	freopen("Tolstoy.txt", "r", stdin);
	string s;
	while(getline(cin, s))
	{
		int i = 0, j;
		while (i < s.size())
		{
			while (i < s.size() && !isalpha(s[i]))
				i++;
			if (i < s.size() && isalpha(s[i]))
			{
				j = i;
				while (i < s.size() && isalpha(s[i]))
					i++;
				BF->Add(lower(s.substr(j, i - j)));
				HT->Add(lower(s.substr(j, i - j)));
			}
		}
	}
	fclose(stdin);
	ifstream fin("Dostoevsky.txt", ifstream::in);
	
	int in = 0, not_in = 0, wrong = 0;
	while(getline(fin, s))
	{
		int i = 0, j;
		while (i < s.size())
		{
			while (i < s.size() && !isalpha(s[i]))
				i++;
			if (i < s.size() && isalpha(s[i]))
			{
				j = i;
				while (i < s.size() && isalpha(s[i]))
					i++;
				bool ans1 = BF->Find(lower(s.substr(j, i - j)));
				bool ans2 = HT->Find(lower(s.substr(j, i - j)));
				if (!ans2)
					++not_in;
				else
					++in;
				if (ans1 != ans2)
					wrong++;
			}
		}
	}
	cout << in << " " << not_in << " " << wrong << endl;
	delete BF;
	delete HT;
	return 0;
}
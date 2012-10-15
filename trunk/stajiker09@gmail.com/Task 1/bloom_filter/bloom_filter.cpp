#include <iostream>
#include <math.h>
#include <algorithm>
#include <vector>
#include <string>
#include <list>
#include <assert.h>
using namespace std;
class hash_table
{
public:
	hash_table()
	{
		table=new list <string>[4];
		size_hash_table=4;
		size=0;
	}
	~hash_table()
	{
		delete[] table;
	}
	class iterator
	{
	public:
		int index;
		iterator(hash_table *Table, int Index, list <string>::iterator It)
		{
			HashTable=Table, index=Index, it=It;
		}
		bool operator==(iterator &other)
		{
			return HashTable==other.HashTable&&index==other.index&&it==other.it;
		}
		bool operator!=(iterator &other)
		{
			return !operator==(other);
		}
		iterator operator++()
		{
			++it;
			if(it==HashTable->table[index].end())
			{
				++index;
				while(index<HashTable->size_hash_table&&HashTable->table[index].size()==0)
					++index;
				if(index==HashTable->size_hash_table)
					it=HashTable->table[index-1].end();
				else
					it=HashTable->table[index].begin();
			}
			return *this;
		}
		iterator operator--()
		{
			assert(*this!=HashTable->begin());
			if(it==HashTable->table[index].begin())
			{
				--index;
				while(index>=0&&HashTable->table[index].size()==0)
					--index;
				it=HashTable->table[index].end();
			}
			--it;
			return *this;
		}
		string operator*()
		{
			return *it;
		}
		iterator* operator->()
		{
			return this;
		}
	private:
		hash_table *HashTable;
		list <string>::iterator it;
	};
	iterator begin()
	{
		int index=0;
		list <string>::iterator it;
		while(index<size_hash_table&&table[index].size()==0)
			++index;
		if(index==size_hash_table)
			return end();
		else
		{
			iterator it(this, index, table[index].begin());
			return it;
		}
	}
	iterator end()
	{
		iterator it(this, size_hash_table, table[size_hash_table-1].end());
		return it;
	}
	bool find(string &key)
	{
		unsigned int value=hash(key);
		for(list <string>::iterator it=table[value].begin(); it!=table[value].end(); ++it)
			if(*it==key)
				return true;
		return false;
	}
	void insert(string &key)
	{
		unsigned int value=hash(key);
		for(list <string>::iterator it=table[value].begin(); it!=table[value].end(); ++it)
			if(*it==key)
				return ;
		table[value].push_back(key);
		++size;
		check_load_factor();
	}
	void erase(string &key)
	{
		unsigned int value=hash(key);
		for(list <string>::iterator it=table[value].begin(); it!=table[value].end(); ++it)
			if(*it==key)
			{
				table[value].erase(it);
				--size;
				check_load_factor();
				break;
			}
	}
	int max_collision()
	{
		int collision=0;
		for(int i=0; i<size_hash_table; ++i)
			collision=max(collision, (int)table[i].size());
		return collision;
	}
private:
	list <string> *table;
	int size;
	int size_hash_table;
	unsigned int hash(string &key)
	{
		unsigned int value=0, pow=53;
		for(int i=0; i<key.length(); ++i)
			value=value*pow+key[i];
		return value%size_hash_table;
	}
	void check_load_factor()
	{
		double load_factor=size/size_hash_table;
		if(load_factor>0.75)
			reallocation(2*size_hash_table);
		if(size_hash_table>4&&load_factor<0.25)
			reallocation(size_hash_table/2);
	}
	void reallocation(int new_size_hash_table)
	{
		int old_size_hash_table=size_hash_table;
		size_hash_table=new_size_hash_table;
		list <string> *new_table=new list <string>[size_hash_table];
		for(int i=0; i<old_size_hash_table; ++i)
			for(list <string>::iterator it=table[i].begin(); it!=table[i].end(); ++it)
			{
				unsigned int value=hash(*it);
				new_table[value].push_back(*it);
			}
		delete[] table;
		table=new_table;
	}
};
class bloom_filter
{
public:
	bloom_filter(double &chance, int number_of_elements)
	{
		number_of_hash_functions=-log(chance)/log((double)2)+1;
		filter.resize(-number_of_elements*log(chance)/log((double)2)/log((double)2));
	}
	~bloom_filter()
	{
		filter.clear();
	}
private:
	vector <bool> filter;
	int number_of_bits, number_of_hash_functions;
	pair <unsigned int, unsigned int> hash(string &key)
	{
		unsigned int hash1=0, pow1=31, hash2=0, pow2=53;
		for(int i=0; i<key.length(); ++i)
		{
			hash1=hash1*pow1+key[i];
			hash2=hash2*pow2+key[i];
		}
		return make_pair(hash1, hash2);
	}
	void add(string &key)
	{
		pair <unsigned int, unsigned int> value=hash(key);
		for(int i=0; i<number_of_hash_functions; ++i)
			filter[(value.first+i*value.second)%number_of_bits]=true;
	}
	bool find(string &key)
	{
		pair <unsigned int, unsigned int> value=hash(key);
		for(int i=0; i<number_of_hash_functions; ++i)
			if(filter[(value.first+i*value.second)%number_of_bits]==false)
				return false;
		return true;
	}
};
int main()
{
	double chance;
	cin>>chance;
	bloom_filter BloomFilter(chance, 100000);
	hash_table HashTable;
	string s;
	while(cin>>s)
	{
		for(int i=s.length()-1; i>=0; --i)
			if(!(s[i]>='a'&&s[i]<='z'||s[i]>='A'||s[i]<='Z'))
				s.pop_back();
		BloomFilter.add(s);
		HashTable.insert(s);
	}
	int word_in_bloom_filter=0, word_in_hash_table=0, all_word, no_word=0, errors_in_bloom_filter;
	while(cin>>s)
	{
		for(int i=s.length()-1; i>=0; --i)
			if(!(s[i]>='a'&&s[i]<='z'||s[i]>='A'||s[i]<='Z'))
				s.pop_back();
		++all_word;
		if(BloomFilter.find(s))
			++word_in_bloom_filter;
		if(HashTable.find(s))
			++word_in_hash_table;
	}
	no_word=all_word-word_in_hash_table;
	errors_in_bloom_filter=word_in_hash_table-word_in_bloom_filter;
	cout<<word_in_hash_table<<' '<<no_word<<' '<<errors_in_bloom_filter;
	return 0;
}
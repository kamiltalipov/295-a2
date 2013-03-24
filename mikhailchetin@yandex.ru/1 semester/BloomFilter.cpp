#include<iostream>
#include<vector>
#include<math.h>
#include<string>
#include<stdio.h>
#include<list>
using namespace std;

class BloomFilter
{
public:
	BloomFilter(double wantedP);
	vector<bool> filter;
	unsigned long long hashFunction1(string a);
	unsigned long long hashFunction2(string a);
	void add(string a);
	bool find(string a);
	int size;
	double p;
	int k;
};
BloomFilter::BloomFilter(double wantedP)
{
	p=wantedP;
	size=(int)(-100000*log(p)/log(2.0)/log(2.0));
	k=(int)(-log(p)/log(2.0));
	filter.resize(size);
	filter.assign(size,0);
}
unsigned long long BloomFilter::hashFunction1(string a)
{
	const int p = 31;
	unsigned long long hash = 0, p_pow = 1;
	for (int i=0; i<a.length(); i++)
	{
		hash += (a[i]) * p_pow;
		p_pow *= p;
	}
	//hash%=size;
	return hash;
}
unsigned long long BloomFilter::hashFunction2(string a)
{
	const int p = 53;
	unsigned long long hash = 0, p_pow = 1;
	for (int i=0; i<a.length(); i++)
	{
		hash += (a[i]) * p_pow;
		p_pow *= p;
	}
	//hash%=size;
	return hash;
}
void BloomFilter::add(string a)
{
	for(int i=0;i<k;i++)
		filter[(hashFunction1(a)+i*hashFunction2(a))%size]=1;
}
bool BloomFilter::find(string a)
{
	for(int i=0;i<k;i++)
		if(!filter[(hashFunction1(a)+i*hashFunction2(a))%size])
		{
			return false;
		}
	return true;
}

const int initialSize=11;

class HashTable
{
public:
	/*class Iterator
	{
	public:
		Iterator(HashTable* curr):current(curr)
		{
		}
	  	Iterator& operator =(const Iterator &other)
		{
			if (this != &other)
			{
				current = other.current;
			}
			return *this;
		}
		Iterator& operator ++()
		{
			++current;
			return *this;
		}
		Iterator operator ++(int i)
		{
			Iterator tmp(current);
			++current;
			return tmp;
		}
		HashTable operator *()
		{
			return *current;
		}
		HashTable* operator ->()
		{
			return current;
		}
	private:
		HashTable* current;
	};*/
	HashTable();
	bool find(string a);
	void add(string a);
	void remove(string a);
	void realloc(int newSize);
	unsigned long long hashFunction(string a);
	int size;
	int allsize;
	vector<list<string>> table;
};
HashTable::HashTable()
{
	size=initialSize;
	allsize=0;
	table.resize(size);
}
unsigned long long HashTable::hashFunction(string a)
{
	const int p = 31;
	unsigned long long hash = 0, p_pow = 1;
	for (int i=0; i<a.length(); i++)
	{
		hash += (a[i]) * p_pow;
		p_pow *= p;
	}
	hash%=size;
	return hash;
}
void HashTable::add(string a)
{
	
	int b=hashFunction(a);
	list<string>::iterator i;
	for(i=table[b].begin();i!=table[b].end();i++)
	{
		if(*i==a)
		{
			return;
		}
	}
	table[b].push_back(a);
	allsize++;
	if(allsize>size)
		realloc(size*2);

}
void HashTable::remove(string a)
{
	int b=hashFunction(a);
	list<string>::iterator i;
	for(i=table[b].begin();i!=table[b].end();i++)
		if(*i==a)
			break;
	if(i!=table[b].end())
	{
		table[b].erase(i);
		allsize--;
	}
	if(allsize<size/4 && allsize!=0)
		realloc(size/2);
}
bool HashTable::find(string a)
{
	int b=hashFunction(a);
	list<string>::iterator i;
	for(i=table[b].begin();i!=table[b].end();i++)
		if(*i==a)
		{
			return true;
		}
	return false;
}
void HashTable::realloc(int newSize)
{
	vector<list<string>> copy=table;
	table.clear();
	table.resize(newSize);
	
	list<string>::iterator i;
	int size1=size;
	size=newSize;
	allsize=0;
	for(int b=0;b<size1;b++)
		for(i=copy[b].begin();i!=copy[b].end();i++)
			add(*i);
}

int main()
{
	double p;
	cin>>p;
	BloomFilter F(p);
	HashTable T;
	int n,k=0;
	string s;
	freopen("dictionary+text.txt","r",stdin);
	for(int i=1;i<=99431;i++)
	{
		cin>>s;
		F.add(s);
		T.add(s);
	}
	cin>>k;
	int rightF=0,rightT=0,wrongF=0,wrongT=0,BloomLies=0;
	for(int i=1;i<=k;i++)
	{
		cin>>s;

		if(F.find(s)) 
			rightF++;
		else wrongF++;

		if(T.find(s)) 
			rightT++;
		else wrongT++;

		BloomLies=rightF-rightT;
	}

	cout<<rightF<<' '<<wrongF<<' '<<BloomLies;

	return 0;
}
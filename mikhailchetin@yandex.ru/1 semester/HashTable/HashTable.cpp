#include<iostream>
#include<list>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;
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
	int maxCollision();
};
HashTable::HashTable()
{
	size=initialSize;
	allsize=0;
	table.resize(size);
}

int HashTable::maxCollision()
{
	int maxcoll=0;
	for(int i=0;i<size;i++)
		maxcoll=max((int)table[i].size(),maxcoll);
	return maxcoll;
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
			cout<<"такой элемент уже есть";
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
	int n;
	int operation;//0-добавление
				  //1-удаление
				  //2-поиск
	string s;

	cin>>n;
	HashTable T;
	for(int i=1;i<=n;i++)
	{
		cin>>s>>operation;
		if(operation==0)
		T.add(s);
		else
			if(operation==1)
				T.remove(s);
			else
				if(T.find(s)) cout<<"Yes";
				else cout<<"No";
	}

	list<string>::iterator j;

	for(int i=0;i<T.size;i++)
		for(j=T.table[i].begin();j!=T.table[i].end();j++)
			cout<<i<<' '<<*j<<' ';

	cout<<T.maxCollision();

	return 0;
}
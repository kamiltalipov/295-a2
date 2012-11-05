#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <stdio.h>

using namespace std;

class Hash_Table
{
public:
	void Add (string &Str);
	void Delete(string &Str);
	bool Str_Exists(string &Str);
	int Count_Collisions();
	Hash_Table();
	vector <list <string> > myarray;

	class iterator
	{
	public:
		int index;
		list< string >::iterator it;
		vector <list < string > > &myarray;

		string operator *()
		{
			return *it;
		}
	
		bool operator ==(iterator tocomp)
		{
			return (&it == &tocomp.it);
		}
	
		bool operator !=(iterator tocomp)
		{
			return (&it != &tocomp.it);
		}

		iterator operator ++()
		{
			it++;
			if (it == (myarray[index].end()))
			{
				index++;
				while (myarray[index].size() == 0)
					(index++) % myarray.size();
				it = myarray[index].begin();
			}
			return *this;
		}
		
		iterator end()
		{
			int tmp = myarray.size() - 1;
			while (myarray[tmp].empty())
				(tmp--);
			it = myarray[tmp].end();
			return *this;
		}

		iterator (vector <list < string > > &arr, int ind):
		myarray(arr), index(ind) 
		{
			while (myarray[index].empty())
				(index++ % myarray.size());
				it = myarray[index].begin();
		}
		private:
	};

private:
	int myarray_size;
	int size;
	int base;
	unsigned long long hash(string &Str);
	unsigned long long hs;
	void check();
	void realloc (int new_size);
};


int Hash_Table::Count_Collisions()
{
	int answer = 0;
	for (int i = 0; i < myarray_size; i++)
		if (myarray[i].size() != 1)
			answer += myarray[i].size();

	return answer;
}

void Hash_Table::realloc(int new_size)
{
	myarray_size = new_size;
	vector <list <string> > new_myarray(myarray_size);
	for(int i = 0; i < myarray_size / 2; i++)
	{
		for(list<string>::iterator j = myarray[i].begin(); j != myarray[i].end(); j++)
		{
			int hs = hash(*j);
			new_myarray[hs].push_back(*j);
		}
	}

	myarray.resize(new_size);
	swap(myarray, new_myarray);
}

void Hash_Table::check()
{
	if (size > (3 * myarray_size / 4))
		realloc(myarray_size * 2);
	else
		if ((size < myarray_size / 4) && (myarray_size != 1024))
		realloc(myarray_size / 4);
}

bool Hash_Table::Str_Exists(string &Str)
{
	hs = hash(Str);
	if (!myarray[hs].empty())
		for(list <string>::iterator i = myarray[hs].begin(); i != myarray[hs].end(); i++)
			if (Str == *i)
				return true;
	return false;
}

void Hash_Table::Add(string &Str)
{
	if (!Str_Exists(Str))
	{
		myarray[hs].push_back(Str);
		size++;
		check();
	}
}

void Hash_Table::Delete(string &Str)
{
	if (Str_Exists(Str))
	{
		for(list <string>::iterator i = myarray[hs].begin(); i != myarray[hs].end(); i++)
			if (*i == Str)
			{
				myarray[hs].erase(i);
				break;
			}
		size--;
		check();
	}
}

Hash_Table::Hash_Table():
myarray_size(1024), base(17), size(0), myarray(1024) {};

unsigned long long Hash_Table::hash(string &Str)
{
	unsigned long long answer = 1;
	for(int i = 0; i < Str.size(); i++)
		answer = answer * base + Str[i];
	return answer % myarray_size;
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	Hash_Table Table;
	char Operation;
	string Str;

	cout << "0 to add, 1 to find, 2 to delete, # to quit\n";
	cin >> Operation >> Str;
	while (Operation != '#')
	{
		switch (Operation)
		{
		case '+':
			Table.Add(Str); 
			break;
		
		case '?':
			if (Table.Str_Exists(Str))
				cout << "Yes\n";
			else
				cout << "No\n";
			break;

		case '-':
			Table.Delete(Str); 
			break;

		default:
			break;
		}
		cin >> Operation >> Str;
	}
	
	for(Hash_Table::iterator it (Table.myarray, 0); it != Hash_Table::iterator(Table.myarray, 0).end(); it++)
		cout << *it << endl;

	cout << "Number of collisions: " << Table.Count_Collisions() << endl;

	fclose(stdin);
	fclose(stdout);
	return 0;
}

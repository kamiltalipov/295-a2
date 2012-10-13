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

/*	class iterator
	{
	private:
		int index;
		//Hash_Table *array;
		list <string>::iterator it; 

	public:
		iterator operator ++()
		{
			if (it != )
		}


		string operator *()
		{
			return *it;
		}
	};
	
	I just can't understand, what does this iterator class has to do. :(
	*/

private:
	int array_size;
	int size;
	int base;
	unsigned long long hash(string &Str);
	unsigned long long hs;
	void check();
	void realloc (int new_size);
	list <string> *array;

};

int Hash_Table::Count_Collisions()
{
	int answer = 0;
	for (int i = 0; i < array_size; i++)
		if (array[i].size() != 1)
			answer += array[i].size();

	return answer;
}

void Hash_Table::realloc(int new_size)
{
	array_size = new_size;
	list<string> *new_array = new list <string>[array_size];
	for(int i = 0; i < array_size / 2; i++)
	{
		for(list<string>::iterator j = array[i].begin(); j != array[i].end(); j++)
		{
			int hs = hash(*j);
			new_array[hs].push_back(*j);
		}
	}

	delete [] array;
	array = new_array;
}

void Hash_Table::check()
{
	if (size > (3 * array_size / 4))
		realloc(array_size * 2);
	else
		if ((size < array_size / 4) && (array_size != 1024))
		realloc(array_size / 4);
}

bool Hash_Table::Str_Exists(string &Str)
{
	hs = hash(Str);
	if (!array[hs].empty())
		for(list <string>::iterator i = array[hs].begin(); i != array[hs].end(); i++)
			if (Str == *i)
				return true;
	return false;
}

void Hash_Table::Add(string &Str)
{
	if (!Str_Exists(Str))
	{
		array[hs].push_back(Str);
		size++;
		check();
	}
}

void Hash_Table::Delete(string &Str)
{
	if (Str_Exists(Str))
	{
		for(list <string>::iterator i = array[hs].begin(); i != array[hs].end(); i++)
			if (*i == Str)
			{
				array[hs].erase(i);
				break;
			}
		size--;
		check();
	}
}

Hash_Table::Hash_Table()
{
	array_size = 1024;
	base = 17;
	size = 0;
	array = new list <string>[array_size];
}

unsigned long long Hash_Table::hash(string &Str)
{
	unsigned long long answer = 1;
	for(int i = 0; i < Str.size(); i++)
		answer = answer * base + Str[i];
	return answer % array_size;
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
			cout << "Goodbye.";
			break;
		}
		cin >> Operation >> Str;
	}

	cout << "Number of collisions: " << Table.Count_Collisions() << endl;

	fclose(stdin);
	fclose(stdout);
	return 0;
}
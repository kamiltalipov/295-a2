#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <stdio.h>
#include <fstream>

using namespace std;

class Hash_Table
{
public:
	void Add (string &Str);
	bool Str_Exists(string &Str);
	int Count_Collisions();
	Hash_Table();

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

Hash_Table::Hash_Table()
{
	array_size = 1024;
	base = 23;
	size = 0;
	array = new list <string>[array_size];

}

unsigned long long Hash_Table::hash(string &Str)
{
	unsigned long long result = 1;
	for(int i = 0; i < Str.size(); i++)
	{
		result = result * base + Str[i];
	}
	return result % array_size;
}

class Bloom_Filter
{
private:
	vector <bool> array;
	int base1, base2;
	int array_size;
	int hashcount;
	unsigned long long hash(string &Str, unsigned long long *result);

public:
	void Add(string &Str);
	Bloom_Filter(int m, int k);
	bool Str_Exists(string &Str);
};

unsigned long long Bloom_Filter::hash(string &Str, unsigned long long *result2)
{
	unsigned long long result1 = 1;
	for(int i = 0; i < Str.size(); i++)
	{
		result1 = result1 * base1 + Str[i];
		*result2 = *result2 * base2 + Str[i];
	}
	*result2 %= array_size;
	return result1 % array_size;
}

Bloom_Filter::Bloom_Filter(int size, int count)
{
	array_size = size;
	hashcount = count;
	base1 = 17;
	base2 = 71;
	array.resize(size);
}

void Bloom_Filter::Add(string &Str)
{
	unsigned long long hash1 = 0;
	unsigned long long hash2 = hash(Str, &hash1);
	for(int i = 0; i < hashcount; i++)
	{
		array[(hash1 + i * hash2) % array_size] = true;
	}
}

bool Bloom_Filter::Str_Exists(string &Str)
{
	unsigned long long hash1 = 0;
	unsigned long long hash2 = hash(Str, &hash1);
	for(int i = 0; i < hashcount; i++)
	{
		if (!array[(hash1 + i * hash2) % array_size])
			return false;
	}
	return true;
}

int main()
{
	ifstream input;
	input.open("vocab.txt");
	freopen("output.txt", "w", stdout);

	Hash_Table Table;
	Bloom_Filter Filter(1000000, 5);
	string Str;
	while (input >> Str)
	{
		while ((Str != "") && (((Str[0] < 'a') || (Str[0] > 'z')) && ((Str[0] < 'A') || (Str[0] > 'Z'))))
			Str.erase(0, 1);

		while ((Str != "") && (((Str[Str.size() - 1] < 'a') || (Str[Str.size() - 1] > 'z')) && ((Str[Str.size() - 1] < 'A') || (Str[Str.size() - 1] > 'Z'))))
			Str.erase(Str.size() - 1, 1);

		for(int i = 0; i < Str.size(); i++)
			Str[i] = tolower(Str[i]);

		if (Str != "")
		{
			Table.Add(Str);
			Filter.Add(Str);
		}
	}
	input.close();
	input.open("text.txt");

	int falsepos = 0;
	int in_vocab = 0;
	int not_in_vocab = 0;

	while (input >> Str)
	{
		while ((Str != "") && (((Str[0] < 'a') || (Str[0] > 'z')) && ((Str[0] < 'A') || (Str[0] > 'Z'))))
			Str.erase(0, 1);

		while ((Str != "") && (((Str[Str.size() - 1] < 'a') || (Str[Str.size() - 1] > 'z')) && ((Str[Str.size() - 1] < 'A') || (Str[Str.size() - 1] > 'Z'))))
			Str.erase(Str.size() - 1, 1);

		for(int i = 0; i < Str.size(); i++)
			Str[i] = tolower(Str[i]);

		bool infilter = Filter.Str_Exists(Str);
		bool inhash = Table.Str_Exists(Str);

		if (infilter && inhash)
			in_vocab++;
		else
			if (infilter && !inhash)
				falsepos++;
			else
				if (!infilter && !inhash)
					not_in_vocab++;
	}
	
	cout << "Vocabular words: " << in_vocab << endl;
	cout << "Non-vocabular words: " << not_in_vocab << endl;
	cout << "False positives: " << falsepos << endl;

	input.close();
	fclose(stdout);
	return 0;
}
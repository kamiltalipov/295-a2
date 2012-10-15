#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;
typedef unsigned long long hash_value_type;

class Hasher
{
public:
	hash_value_type operator()(const string& s, hash_value_type mod);
	Hasher() { P = rand() % (primes_count); }
	void next_hash() { do P = (rand() % primes_count); while (gcd(P, primes_count) != 1); }
private:
	static const int prime[], primes_count;
	unsigned int P;
	int gcd(int a, int b)
	{
		while ( b )
			a %= b, swap(a, b);
		return a;
	}
};

const int Hasher::prime[] = {101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997, 1009, 1013, 1019, 1021, 1031, 1033, 1039, 1049, 1051, 1061, 1063, 1069, 1087, 1091, 1093, 1097, 1103, 1109, 1117, 1123, 1129, 1151, 1153, 1163, 1171, 1181, 1187, 1193, 1201, 1213, 1217, 1223, 1229, 1231, 1237, 1249, 1259, 1277, 1279, 1283, 1289, 1291, 1297, 1301, 1303, 1307, 1319, 1321, 1327, 1361, 1367, 1373, 1381, 1399, 1409, 1423, 1427, 1429, 1433, 1439, 1447, 1451, 1453, 1459, 1471, 1481, 1483, 1487, 1489, 1493, 1499, 1511, 1523, 1531, 1543, 1549, 1553, 1559, 1567, 1571, 1579, 1583, 1597, 1601, 1607, 1609, 1613, 1619, 1621, 1627, 1637, 1657, 1663, 1667, 1669, 1693, 1697, 1699, 1709, 1721, 1723, 1733, 1741, 1747, 1753, 1759, 1777, 1783, 1787, 1789, 1801, 1811, 1823, 1831, 1847, 1861, 1867, 1871, 1873, 1877, 1879, 1889, 1901, 1907, 1913, 1931, 1933, 1949, 1951, 1973, 1979, 1987, 1993, 1997, 1999};
const int Hasher::primes_count = 278;

hash_value_type Hasher::operator()(const string& s, hash_value_type mod)
{
	hash_value_type hash = 0;
	for (int i = 0; i < s.length(); ++i)
		hash = (hash * P + s[i]) % mod;
	return hash;
}

class HashTable {
public:
	class iterator;
private:
	typedef vector < list < string > > table_type;
	typedef HashTable::iterator hash_iterator_type;
public:
	int Size() const { return n; }
	void Add(const string& s);
	bool Contain(const string& s);
	void Delete(const string& s);
	HashTable(int base_size = 2) : table(*(new table_type(base_size))), n(0), hasher() {}
	HashTable(const HashTable& hash_table) : hasher(), n(0), table(*(new table_type(hash_table.Size())))
	{
		for (hash_iterator_type it = hash_table.begin(); it != hash_table.end(); ++it)
			Add(*it);
	}
	virtual ~HashTable() { delete &table; }
	class iterator
	{
	private:
		friend class HashTable;
		const table_type::iterator const table_begin, table_end;
		table_type::iterator table_it;
		list < string >::iterator list_it;
		iterator(const HashTable& ht) : table_begin(ht.table.begin()), table_end(ht.table.end()), table_it(ht.table.begin())
		{
			while (table_it != table_end && !table_it->size()) ++table_it;
			list_it = table_it != table_end ? table_it->begin() : list < string >::iterator();
		}
		iterator(const HashTable& ht, const table_type::iterator& table_it, const list < string >::iterator& list_it) :
			table_begin(ht.table.begin()), table_end(ht.table.end()), list_it(list_it), table_it(table_it) {}
	public:
		hash_iterator_type& operator++();
		hash_iterator_type operator++(int);
		hash_iterator_type& operator--();
		hash_iterator_type operator--(int);
		const string& operator*() { return *list_it; }
		const string& operator->() { return *list_it; }
		bool operator==(const hash_iterator_type &it) { return table_it == it.table_it && it.list_it == list_it; }
		bool operator!=(const hash_iterator_type &it) { return !(table_it == table_end && it.table_it == table_end) && (table_it != it.table_it || it.list_it != list_it); }
	};
	hash_iterator_type begin() const { return iterator(*this); }
	hash_iterator_type end() const { return iterator(*this, this->table.end(), list < string >::iterator()); }
private:
	Hasher hasher;
	table_type& table;
	int n;
	void rebuild();
};

HashTable::iterator HashTable::iterator::operator++(int)
{
	iterator it = iterator(*this);
	++(*this);
	return it;
}

HashTable::iterator HashTable::iterator::operator--(int)
{
	iterator it = iterator(*this);
	--(*this);
	return it;
}

HashTable::iterator& HashTable::iterator::operator++()
{
	if (table_it == table_end) return *this;
	if (++list_it == table_it->end())
	{
		do ++table_it; while (table_it != table_end && !table_it->size());
		if (table_it != table_end)
			list_it = table_it->begin();
	}
	return *this;
}

HashTable::iterator& HashTable::iterator::operator--()
{
	if (table_it == table_begin && list_it == table_begin->begin()) return *this;
	if (list_it != table_it->begin())
		--list_it;
	else
	{
		do --table_it; while (table_it != table_begin && !table_it->size());
		list_it = table_it->size() ? --table_it->end() : table_it->begin();
	}
	return *this;
}

void HashTable::Add(const string& s)
{
	hash_value_type hash = hasher(s, table.size());
	for (list < string >::iterator it = table[hash].begin(); it != table[hash].end(); ++it)
		if (*it == s)
			return;
	table[hash].push_back(s);
	++n;
	rebuild();
}

bool HashTable::Contain(const string& s)
{
	hash_value_type hash = hasher(s, table.size());
	for (list < string >::iterator it = table[hash].begin(); it != table[hash].end(); ++it)
		if (*it == s)
			return true;
	return false;
}

void HashTable::Delete(const string& s)
{
	hash_value_type hash = hasher(s, table.size());
	for (list < string >::iterator it = table[hash].begin(); it != table[hash].end(); ++it)
		if (*it == s)
		{
			table[hash].erase(it);
			--n;
			break;
		}
	rebuild();
}

void HashTable::rebuild()
{
	if (table.size() <= n * 4 && n * 2 <= table.size())
		return;
	vector < string > data;
	for (hash_iterator_type it = begin(); it != end(); ++it)
		data.push_back(*it);
	int nn = table.size() > n * 4 ? n / 2 : n * 2;
	hasher.next_hash();
	table.assign(nn, list < string > ());
	int cur_hash;
	for (vector < string >::iterator it = data.begin(); it != data.end(); ++it)
	{
		cur_hash = hasher(*it, nn);
		table[cur_hash].push_back(*it);
	}
}

int main()
{
	string s;
	HashTable ht;
	HashTable::iterator it = ht.begin();
	ht.Add("pumpururum");
	ht.Add("12345");
	ht.Add("80931283");
	ht.Add("uieiuf");
	cout << ht.Size() << endl;
	system("pause");
	return 0;
}

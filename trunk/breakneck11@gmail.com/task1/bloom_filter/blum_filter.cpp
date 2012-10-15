#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class BitSet
{
	static const int fsize = sizeof(int) * 8;
	vector < unsigned int > data;
	int size;
	static int divide2up(int a, int b) { return a % b ? (a / b) + 1 : a / b; }
public:
	BitSet(int size = 128) : size(size), data(divide2up(size, fsize)) {}
	static BitSet* FromInt(int a);
	void SetBit(int bit, bool val);
	bool GetBit(int bit);
};

void BitSet::SetBit(int bit, bool val)
{
	if (bit > size)
	{
		data.resize(size = divide2up(bit, fsize));
	}
	int n = bit / fsize, pos = bit % fsize;
	if (val)
		data[n] |= 1 << pos;
	else
		data[n] &= ~(1 << pos);
}

bool BitSet::GetBit(int bit)
{
	if (bit > size) throw new string("Wrong Index");
	int n = bit / fsize, pos = bit % fsize;
	return data[n] & (1 << pos);
}

static BitSet* FromInt(int a)
{
	BitSet* bs = new BitSet(1);
	for (int i = 0; a; ++i, a >>= 1)
		bs->SetBit(i, a & 1);
	return bs;
}

struct Hasher
{
	int P, mod;
	Hasher(int P, int mod) : P(P), mod(mod) {}
	Hasher() : P(0), mod(1) {}
	unsigned long long operator()(const string& s)
	{
		unsigned long long hash = 0;
		for (int i = 0; i < s.length(); ++i)
			hash = (hash * P + s[i]) % mod;
		return hash;
	}
};

class BloomFilter
{
	static const int primes[], primes_size;
	int  size;
	vector < Hasher > hash_funcs;
	BitSet &filter;
public:
	BloomFilter(int _hash_funcs_size, int size) : filter(* new BitSet(size)), size(size)
	{
	const int hash_funcs_size = min(primes_size, _hash_funcs_size);
	hash_funcs = vector < Hasher > (hash_funcs_size);
	for (int i = 0; i < hash_funcs_size; ++i)
		hash_funcs[i] = Hasher(primes[primes_size - i - 1], size);
	}
	~BloomFilter() { delete &filter; }
	void Add(const string& s);
	bool Contain(const string& s);
};

void BloomFilter::Add(const string& s)
{
	for (int i = 0; i < hash_funcs.size(); ++i)
		filter.SetBit(hash_funcs[i](s), true);
}

bool BloomFilter::Contain(const string& s)
{
	for (int i = 0; i < hash_funcs.size(); ++i)
		if (!filter.GetBit(hash_funcs[i](s)))
			return false;
	return true;
}

const int BloomFilter::primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997, 1009, 1013, 1019, 1021, 1031, 1033, 1039, 1049, 1051, 1061, 1063, 1069, 1087, 1091, 1093, 1097, 1103, 1109, 1117, 1123, 1129, 1151, 1153, 1163, 1171, 1181, 1187, 1193, 1201, 1213, 1217, 1223, 1229, 1231, 1237, 1249, 1259, 1277, 1279, 1283, 1289, 1291, 1297, 1301, 1303, 1307, 1319, 1321, 1327, 1361, 1367, 1373, 1381, 1399, 1409, 1423, 1427, 1429, 1433, 1439, 1447, 1451, 1453, 1459, 1471, 1481, 1483, 1487, 1489, 1493, 1499, 1511, 1523, 1531, 1543, 1549, 1553, 1559, 1567, 1571, 1579, 1583, 1597, 1601, 1607, 1609, 1613, 1619, 1621, 1627, 1637, 1657, 1663, 1667, 1669, 1693, 1697, 1699, 1709, 1721, 1723, 1733, 1741, 1747, 1753, 1759, 1777, 1783, 1787, 1789, 1801, 1811, 1823, 1831, 1847, 1861, 1867, 1871, 1873, 1877, 1879, 1889, 1901, 1907, 1913, 1931, 1933, 1949, 1951, 1973, 1979, 1987, 1993, 1997, 1999};
const int BloomFilter::primes_size = 303;
int main()
{
	BloomFilter bl(2, 1000);
	bl.Add("ololo");
	cout << bl.Contain("ololo") << endl;
	cout << bl.Contain("lolol") << endl;
	system("pause");
	return 0;
}

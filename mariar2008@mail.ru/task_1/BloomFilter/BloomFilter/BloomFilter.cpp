#include<vector>
#include<cstdio>
#include<iostream>
#include<fstream>
#include<cctype>
#include<string>
#include<list>
#include<iterator>
#include<crtdbg.h>
#include<ctime>

using namespace std;

class HashTable{
public:
	HashTable();
	void Add(string& s);
	void Delete(string& s);
	bool Find(string& s, list<string>::iterator& it);
	bool Find(string& s);

	class iterator{
	public:
		HashTable* Table;
		list<string>::iterator ListIt;
		vector<list<string>>::iterator VectorIt;
		
		iterator(HashTable* Table_, vector<list<string>>::iterator VectorIt_, list<string>::iterator ListIt_){
			Table = Table_;
			VectorIt = VectorIt_;
			ListIt = ListIt_;
		}
		iterator& operator ++(){
			ListIt++;
			if (ListIt != (*VectorIt).end())
				return *this;
			VectorIt++;
			while (VectorIt != (Table->table).end()){
				ListIt = (*VectorIt).begin();
				if (ListIt != (*VectorIt).end())
					return *this;
				VectorIt++;
			}
			ListIt = (*(VectorIt - 1)).end();
			return *this;
		}
		iterator& operator --(){
			if (VectorIt == (Table->table).end()){
				VectorIt--;
				while ((*VectorIt).size() == 0)
					VectorIt--;
				ListIt = (*VectorIt).end();
			}
			else{
				if ((*VectorIt).size() == 0){
					while ((*VectorIt).size() == 0)
						VectorIt--;
					ListIt = (*VectorIt).end();
				}
			}
			if (ListIt != (*VectorIt).begin()){
					ListIt--;
					return *this;
			}
			else{
				VectorIt--;
				while ((*VectorIt).size() == 0)
				    VectorIt--;
				ListIt = --((*VectorIt).end());
				return *this;
			}
		}
		string& operator *(){
			return *ListIt;
		}
		string* operator ->(){
			return &*ListIt;
		}
		bool operator !=(iterator It){
			if (It.VectorIt == VectorIt && It.ListIt == ListIt)
				return false;
			else
				return true;
		}
		bool operator ==(iterator It){
			if(It.VectorIt == VectorIt && It.ListIt == ListIt)
				return true;
			else
				return false;
		}
	};
	iterator begin(){
		vector<list<string>>::iterator It = table.begin();
		while ((*It).size() == 0 && It != table.end()){
			It++;
		}
		if (It != table.end())
			return iterator(this, It, (*It).begin());
		else
			return iterator(this, It, (*--It).end());
	}
	iterator end(){
		return iterator(this, table.end(), (*--table.end()).end()); 
	};
	int MaxNumCollisions(){
		unsigned int result = 0;
		for (int i = 0; i < size; i++){
			result = max(result, table[i].size());
		}
		return result;
	};
private:
	vector<list<string>> table;
	const static int Simple = 1000007;
	int number, size;
	int DoHash(string& s);
	void Resize();
	bool not_simple(int x);
};

HashTable::HashTable(){
	table.resize(2);
	size = 2;
	number = 0;
}
int HashTable::DoHash(string& s){
	unsigned long long CurHash = 0, Deg = 1;
	for (int i = 0; i < s.size(); i++){
		CurHash = CurHash*Deg + s[i];
		Deg *= Simple;
	}
	return CurHash%size;
}

bool HashTable::not_simple(int x){
	for (int i = 2; i*i <= x; i++)
		if (x % i == 0)
			return true;
	return false;
}

void HashTable::Resize(){
	size = 8*size;
	while (not_simple(size)){
		size++;
	}
	iterator it = begin();
	vector<string> element;
	while (it != end()){
		element.push_back(*it);
		++it;
	}
	table.clear();
	table.resize(size);
	number = 0;

	for(int i = 0; i < element.size(); i++)
		Add(element[i]);
}

void HashTable::Add(string& s){
	unsigned long long h = DoHash(s);
	list<string>::iterator It = table[h].begin();
	while (It != table[h].end()){
		if (*It == s)
			return;
		It++;
	}
	table[h].push_back(s);
	number++;
	if (number > size*4)
		Resize();
}
bool HashTable::Find(string& s){
	unsigned long long h = DoHash(s);
	list<string>::iterator It = table[h].begin();
	while (It != table[h].end()){
		if (*It == s) return true;
		It++;
	}
	return false;
}

bool HashTable::Find(string& s, list<string>::iterator& it){
	unsigned long long h = DoHash(s);
	list<string>::iterator It = table[h].begin();
	while (It != table[h].end()){
		if (*It == s){
			it = It;
			return true;
		}
		It++;
	}
	it = It;
	return false;
}

void HashTable::Delete(string& s){
	unsigned long long h = DoHash(s);
	list<string>::iterator it;
	if (!Find(s, it))
		return;
	table[h].erase(it);
	number--;
}


class BloomFilter{
public:
	BloomFilter();
	void add(string& s);
	bool find(string& s);
private:
	static const int size = 4804692; //4804692; //size = -(501269*ln(0.01))/(ln2)^2
	static const int NumHash = 7;//NumHash = (size*ln2)/501269;
	unsigned int DoHash(int p, string& s);
	void DoModule();
	int NextPrime(int x);
	bool isPrime(int x);
	vector<bool> ourArr;
	vector<int> module;
};

BloomFilter::BloomFilter(){
	ourArr.resize(size);
	module.resize(NumHash);
	DoModule();
}

bool BloomFilter::isPrime(int x){
	for (int i = 2; i*i <= x; i++)
		if (x % i == 0) return false;
	return true;
}

int BloomFilter::NextPrime(int x){
	while (!isPrime(x))
		x++;
	return x;
}

void BloomFilter::DoModule(){
	srand(time(NULL));
	module[0] = NextPrime(rand());
	for (int i = 1; i < NumHash; i++)
		module[i] = NextPrime(module[i - 1] + 1);
}

unsigned int BloomFilter::DoHash(int p, string& s){
	unsigned int h = 0;
	for (int i = 0; i < s.size(); i++)
		h = h*p + s[i];
	return h%size;
}

void BloomFilter::add(string& s){
	for (int i = 0; i < NumHash; i++){
		unsigned int h = DoHash(module[i], s);
		ourArr[h] = 1;
	}
}
bool BloomFilter::find(string& s){
	for (int i = 0; i < NumHash; i++){
		unsigned int h = DoHash(module[i], s);
		if (!ourArr[h])
			return false;
	}
	return true;
}

bool sign(char a){
	if (('a' <= a && a <= 'z')||('A' <= a && a <= 'Z'))
		return false;
	else
		return true;
}

int main(void){
	freopen("output.txt","w",stdout);
	ifstream inOne ("LordOfTheRings.txt");
	HashTable DictionaryHT;
	BloomFilter DictionaryBF;
	string s;
	int cur = 0;
	while (!inOne.eof()){
		inOne >> s;
		if (s != ""){	
			int i = 0;
			int j = s.size() - 1;
			while (i < j && sign(s[i])) i++;
			while (j >= 0 && sign(s[j])) j--;
			if (i <= j){
				for (int k = i; k <= j; k++)
					s[k] = tolower(s[k]);
				DictionaryHT.Add(s.substr(i, j - i + 1));
			    DictionaryBF.add(s.substr(i, j - i + 1));
				cur++;
			}
		}
	}
	cout << "Количество слов в словаре " << cur << endl;  
	inOne.close();
	ifstream inTwo ("ThreeMenInABoat.txt");
	int BFfalse = 0, find = 0, unic = 0;;
	double MediumTimeHT = 0, MediumTimeBF = 0;
	while (!inTwo.eof()){
		inTwo >> s;
		if (s != ""){
			int i = 0;
			int j = s.size() - 1;
			while (i < j && sign(s[i])) i++;
			while (j >= 0 && sign(s[j])) j--;
			if (i <= j){
				for (int k = i; k <= j; k++)
					s[k] = tolower(s[k]);
				double timeHT = clock();
				bool HTfind = DictionaryHT.Find(s.substr(i, j - i + 1));
				timeHT = clock() - timeHT;
				MediumTimeHT += timeHT;
				double timeBF = clock();
				bool BFfind = DictionaryBF.find(s.substr(i, j - i + 1));
				timeBF = clock() - timeBF;
				MediumTimeBF += timeBF;
				if (HTfind) find++;
				else unic++;
				
				//if (!HTfind && BFfind)	BFfalse++;
				if (HTfind != BFfind) BFfalse++;
			}
		}
	}
	cout << "Количество ложных срабатываний " << BFfalse << endl << "Количество словарных слов " << find << endl << "Количество уникальных слов " << unic << endl;
	cout << "Среднее время проверки в HT " << MediumTimeHT/(find + unic) << endl << "Среднее время проверки в BF "<< MediumTimeBF/(find + unic);
	inTwo.close();
	return 0;
}
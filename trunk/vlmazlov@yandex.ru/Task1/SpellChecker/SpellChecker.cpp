#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cassert>
#include <cmath>
#include <cctype>
#include <Windows.h>
using namespace std;

const int HashBase = 37, Prime = 1000000007; // Вряд ли в масииве будет больше 10:9 + 7 элементов; по-хорошему, конечно, нужен генератор простых чисел
int MAXLEN = 50;// максимальная длина слова явно не больше 50

class HashTable;

class iteratorr {
private:
	HashTable* Table;
	vector <list <string> >::iterator listNum;
	list <string>::iterator elementIt;
public:
	friend class HashTable;
	iteratorr(HashTable* Table);
	void operator++();
	void operator--();
	string operator*();
	string* iteratorr::operator ->();
	bool operator !=(iteratorr that);
};

class HashTable {
public:
	friend class iteratorr;
	bool find(string& s);
	void add(string& s);
	void erase(string& s);
	void iterate();
	iteratorr begin();
	iteratorr end();
	HashTable();
	int countWords() { return wordsQuantity; };
private:
	int wordsQuantity;
	void reallocate();
	vector <list <string> > buffer;
	int hash(string& s);
	vector <int> hashDegrees;
};	

void HashTable::reallocate() {
	HashTable* NewTable = new HashTable;
	NewTable->buffer.resize(this->buffer.size() * 4);
	iteratorr it(this);
	for (it = this->begin();it != this->end();++it) {
		NewTable->add(*it);
	}
	*this = *NewTable;
	delete NewTable;
}

iteratorr::iteratorr(HashTable* Table) {
	this->Table = Table;
	this->listNum = Table->buffer.begin();
	this->elementIt = Table->buffer[0].begin();
}

HashTable::HashTable() {
	buffer.resize(1000);
	hashDegrees.resize(MAXLEN);
	wordsQuantity = 0;
	hashDegrees[0] = 1;
	for (int i = 1;i < MAXLEN;i++) {
		hashDegrees[i] = ((unsigned)hashDegrees[i - 1] * HashBase) % Prime;
	}
}

int HashTable::hash(string& s) {
	int res = 0;
	for (int i = 0;i < s.length();i++) {
		res = ((res * hashDegrees[i]) % Prime + s[i]) % Prime;
	}
	return (unsigned)res % buffer.size();
}

void iteratorr::operator++() {
	if (elementIt != listNum->end()) {
		elementIt++;
	} 
	if (elementIt == listNum->end()) {
		if (listNum == Table->buffer.end()) {
			elementIt = Table->buffer[Table->buffer.size() - 1].end(); 	
			return;
		}
		listNum++;
		for (;(listNum < Table->buffer.end()) && (listNum->empty());listNum++);
		if (listNum < Table->buffer.end()) elementIt = listNum->begin();
	} 
}

void iteratorr::operator--() {
	if ((listNum != Table->buffer.end()) && (elementIt != listNum->begin())) {
		elementIt--;
	} else {
		assert(listNum != Table->buffer.begin());
		listNum--;
		for (;(listNum > Table->buffer.begin()) && ((*listNum).empty());listNum--);
		elementIt = --listNum->end();
	}
}

string iteratorr::operator*() {
	return *elementIt;
}

string* iteratorr::operator ->() {
	return &(*elementIt);
}

bool iteratorr::operator !=(iteratorr that) {
	if ((this->Table == that.Table) && (this->listNum == that.listNum) && (this->elementIt == that.elementIt)) return false;
	return true;
}

iteratorr HashTable::begin() {
	iteratorr it(this);
	return it;
}

iteratorr HashTable::end() {
	iteratorr it(this);
	it.listNum = buffer.end();
	it.elementIt = buffer[buffer.size() - 1].end();
	return it;
}

bool HashTable::find(string& s) {
	int hashS = hash(s);
	for (list <string>::iterator it = buffer[hashS].begin();it != buffer[hashS].end();it++) {
		if (!it->compare(s)) return true; 
	}
	return false;
}

void HashTable::add(string& s) {
	int hashS = hash(s);
	for (list <string>::iterator it = buffer[hashS].begin();it != buffer[hashS].end();it++) {
		if (!it->compare(s)) return; 
	}
	wordsQuantity++;
	buffer[hashS].push_back(s);
	if (wordsQuantity > 4 * buffer.size()) reallocate();
}

void HashTable::erase(string& s) {
	int hashS = hash(s);
	for (list <string>::iterator it = buffer[hashS].begin();it != buffer[hashS].end();it++) {
		if (it->compare(s)) {
			buffer[hashS].erase(it);
			return;
		}
	}
}

void HashTable::iterate() {
	iteratorr it(this);
	/*it = begin(); - C начала
	cout << (*it) << endl;
	while (it != end()) {
		cout << *it << " " << it->size() endl;
		++it;
	}*/
	it = end();  // С конца
	while(it != begin()) {
		--it;
		cout << *it << " " << it->size() << endl; // it->size выводится для демонстарции работы оператора ->, все остальные используются в программе
	}
}

class BloomFilter {
private:
	int size;
	int hashQuantity;
	vector <int> basePowers[2];
	static const int hashBase1 = 31, hashBase2 = 33;
    vector <bool> buffer;
	int preHash(string& s, int hashID);
    int* hash(string& s);
public:
	BloomFilter(double probability, int worsdQuantity);
	bool check(string& s);
	void add(string& s);
};

BloomFilter::BloomFilter(double probability, int wordsQuantity) {
	basePowers[0].push_back(1);
	basePowers[1].push_back(1);
	for (int i = 1;i < MAXLEN;i++) {
		basePowers[0].push_back(basePowers[0][i - 1] * hashBase1);
		basePowers[1].push_back(basePowers[1][i - 1] * hashBase2);
	}
	hashQuantity = (-1) * log(probability) / log((double)2);
	size = hashQuantity * wordsQuantity / log((double)2);
	buffer.resize(size);
}

int BloomFilter::preHash(string& s, int hashID) {
   int res = 0;
   for (int i = 0;i < s.length();i++) {
      res += s[i] * basePowers[hashID][i];
   }
   return res;
}

int* BloomFilter::hash(string& s) {
   int* res = new int[hashQuantity];
   for (int j=0;j<hashQuantity;j++) {
      *(res + j) = ((unsigned)(preHash(s, 0) + j * preHash(s, 1))) % size;
   }
   return res;
}

void BloomFilter::add(string& s) {
   int* sHash = hash(s);
   for (int j = 0;j < hashQuantity;j++) {
	   //cout << *(sHash + j) << " ";
	   buffer[*(sHash + j)] = 1;
   }
  // cout << endl;
}

bool BloomFilter::check(string& s) {
    int* sHash = hash(s);
    for (int j = 0;j < hashQuantity;j++) {
        if (!buffer[*(sHash + j)]) return false;
    }
    return true; 
}

bool checkFilter(string& s, HashTable* Table) {	
	if (Table->find(s)) {
		cout << "and it is." << endl;
		return 0;
	}
	cout << "but actually isn't." << endl;
	return 1;
}


int main() {
	double probability;
	cin >> probability;
	freopen("WordBase.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	HashTable* Table = new HashTable;
	char c;
	string s;
	
	while (scanf("%c", &c) == 1) {// Чтение и запоминание в хэш-таблице
		if (isalnum(c)) s.push_back(c);
		else if (!s.empty()) {
			Table->add(s);
			s.clear();
		}
	}
	
	BloomFilter* dict = new BloomFilter(probability, Table->countWords()); //Инициализация фильтра Блюма
	iteratorr it(Table);
	it = Table->end();
	--it;
	while (it != Table->begin()) {
		--it;
		dict->add(*it);
	}
	
	fclose(stdin);
	freopen("input.txt", "r", stdin);
	
	int previousTime = GetTickCount(), timeHashTable, timeBloomFilter = 0;
 	while (scanf("%c", &c) == 1) { // Проверка хэш-таблицей
		if (isalnum(c)) s.push_back(c);
		else if (!s.empty()) {
			if (Table->find(s)) cout << s << " is correct" << endl;
			else cout << s << " is incorrect" << endl;
			s.clear();
		}
	}
	timeHashTable = GetTickCount() - previousTime;
	cout << "HashTable: " << timeHashTable << "ms" << endl;
						
	fclose(stdin);
	freopen("input.txt", "r", stdin);
	
	previousTime = GetTickCount();
	int FilterFail = 0;

	while (scanf("%c", &c) == 1) { // Проверка фильтром Блюма
		if (isalnum(c)) s.push_back(c);
		else if (!s.empty()) {
			if (dict->check(s)) {
				timeBloomFilter += GetTickCount() - previousTime;
				cout << s << " is probably correct " << endl;
				FilterFail += checkFilter(s, Table); 
				previousTime = GetTickCount();
			} else cout << s << " is incorrect" << endl;
			s.clear();
		}
	}
	timeBloomFilter += GetTickCount() - previousTime;
	cout << "BoomFilter: " << timeBloomFilter << "ms" << endl;
	cout << "BloomFilter Failed " << FilterFail << " times, which is " << (double)FilterFail / (double)Table->countWords() 
		<< " percent; probability of fail was " << probability << endl; 
	if (timeBloomFilter < timeHashTable) {
		cout << "BloomFilter works faster by " <<  timeHashTable - timeBloomFilter << "ms" << endl;
	} else {
		cout << "HashTable works faster by " << timeBloomFilter -  timeHashTable << "ms" << endl;
	}
	delete dict;
	delete Table;
	return 0;
}
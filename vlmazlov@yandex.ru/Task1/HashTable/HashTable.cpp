#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cassert>
using namespace std;

const int HashBase = 37, Prime = 1000000007; // ¬р€д ли в масииве будет больше 10:9 + 7 элементов; по-хорошему, конечно, нужен генератор простых чисел
int MAXLEN = 50;// максимальна€ длина слова €вно не больше 50

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
	it = end();  // — конца
	while(it != begin()) {
		--it;
		cout << *it << " " << it->size() << endl; // it->size выводитс€ дл€ демонстарции работы оператора ->, все остальные используютс€ в программе
	}
}

int main() {
	freopen("WordBase.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	HashTable* Table = new HashTable;
	char c;
	string s;
	while (scanf("%c", &c) == 1) {
		if (isalnum(c)) s.push_back(c);
		else if (!s.empty()) {
			Table->add(s);
			s.clear();
		}
	}
	fclose(stdin);
	freopen("input.txt", "r", stdin);
	while (scanf("%c", &c) == 1) {
		if (isalnum(c)) s.push_back(c);
		else if (!s.empty()) {
			if (Table->find(s)) cout << s << " is correct" << endl;
			else cout << s << " is incorrect" << endl;
			s.clear();
		}
	}
	cout << "Table:" << endl;
	Table->iterate();
	//delete Table;
	return 0;
}
#include<vector>
#include<cstdio>
#include<iostream>
#include<string>
#include<list>
#include<iterator>
#include<crtdbg.h>

using namespace std;

class HashTable{
public:
	HashTable();
	void Add(string& s);
	void Delete(string& s);
	bool Find(string& s, list<string>::iterator& it);

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
				while (ListIt != (*VectorIt).end()){
					return *this;
					ListIt++;
				}
				return *this;
				VectorIt++;
			}
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
		it++;
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

int main(void){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);

	int Num;
	HashTable ourHashTable;
	string s;
	cin >> Num;
	for (int i = 0; i < Num; i++){
		cin >> s;
		if (s == "Add"){
			cin >> s;
			ourHashTable.Add(s);
		}
		if (s == "Delete"){
			cin >> s;
			ourHashTable.Delete(s);
		}
		if (s == "Find"){
			cin >> s;
			list<string>::iterator cur;
			cout << s << " " << ourHashTable.Find(s, cur) << endl;
		}
	}
	cout << ourHashTable.MaxNumCollisions();

	return 0;
}
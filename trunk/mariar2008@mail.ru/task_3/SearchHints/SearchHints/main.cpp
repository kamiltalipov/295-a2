#include<cstdio>
#include<iostream>
#include<fstream>
#include<cctype>
#include<string>
#include<list>
#include<iterator>
#include<crtdbg.h>
#include<ctime>
#include<queue>
#include<algorithm>
#include<vector>

using namespace std;
struct my{
	int rate;
	string s;
};

class HashTable{
public:
	HashTable();
	void Add(string& s);
	void Delete(string& s);
	bool Find(string& s, list<my>::iterator& it);
	bool Find(string& s);

	class iterator{
	public:
		HashTable* Table;
		list<my>::iterator ListIt;
		vector<list<my>>::iterator VectorIt;
		
		iterator(HashTable* Table_, vector<list<my>>::iterator VectorIt_, list<my>::iterator ListIt_){
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
		my& operator *(){
			return *ListIt;
		}
		my* operator ->(){
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
		vector<list<my>>::iterator It = table.begin();
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
	vector<list<my>> table;
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
		element.push_back((*it).s);
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
	list<my>::iterator It = table[h].begin();
	while (It != table[h].end()){
		if ((*It).s == s){
			(*It).rate++;
			return;
		}
		It++;
	}
	my x;
	x.s = s; x.rate = 1;
	table[h].push_back(x);
	number++;
	if (number > size*4)
		Resize();
}
bool HashTable::Find(string& s){
	unsigned long long h = DoHash(s);
	list<my>::iterator It = table[h].begin();
	while (It != table[h].end()){
		if ((*It).s == s) return true;
		It++;
	}
	return false;
}

bool HashTable::Find(string& s, list<my>::iterator& it){
	unsigned long long h = DoHash(s);
	list<my>::iterator It = table[h].begin();
	while (It != table[h].end()){
		if ((*It).s == s){
			it = It;
			return true;
		}
		It++;
	}
	it = It;
	return false;
}
bool sign(char a){
	if (('a' <= a && a <= 'z')||('A' <= a && a <= 'Z'))
		return false;
	else
		return true;
}

struct TreeNode{
	int valMax, ind, l, r;
};

class IntervalTree{
public:
	IntervalTree(vector<my>& arr);
	int GetMax(int l, int r, int ind, int& IndMaxElem);
	void Replace(int IndOfElem, int value);
private:
	vector<TreeNode> ourTree;
	int size, shift;
};
IntervalTree::IntervalTree(vector<my>& arr){
	shift = arr.size() - 1;
	int deg = 0;
	while (shift != 0){
		shift = shift >> 1;
		deg++;
	}
	shift = (1 << deg);
	size = shift*2;
	shift--;
	ourTree.resize(size);
	int j = 0;
	for (int i = shift + 1; i < shift + arr.size() + 1; i++){
		ourTree[i].valMax = arr[j].rate;
		ourTree[i].ind = j;
		j++;
		ourTree[i].l = i;
		ourTree[i].r = i;
	}
	for (int i = shift + arr.size() + 1; i < size; i++){
		ourTree[i].valMax = numeric_limits<int>::min();
		ourTree[i].ind = i - shift - 1;
		ourTree[i].l = i;
		ourTree[i].r = i;
	}

	for (int i = shift; i > 0; i--){
		if (ourTree[i*2].valMax > ourTree[i*2 + 1].valMax){
			ourTree[i].valMax = ourTree[i*2].valMax;
			ourTree[i].ind = ourTree[i*2].ind;
		}
		else{
			ourTree[i].valMax = ourTree[i*2 + 1].valMax;
			ourTree[i].ind = ourTree[i*2 + 1].ind;
		}
		ourTree[i].l = ourTree[i*2].l;
		ourTree[i].r = ourTree[i*2 + 1].r;
	}
}
int IntervalTree::GetMax(int l, int r, int ind, int& IndMaxElem){
	int left = l + shift;
	int right = r + shift;
	IndMaxElem = size;
	if (ourTree[ind].l > right || ourTree[ind].r < left)
		return numeric_limits<int>::min();
	if (left <= ourTree[ind].l && ourTree[ind].r <= right){
		IndMaxElem = ourTree[ind].ind;
		return ourTree[ind].valMax;
	}
	int IndMaxElemOne = 0, IndMaxElemTwo = 0;
	int MaxOne = GetMax(l, r, ind*2, IndMaxElemOne), MaxTwo = GetMax(l, r, ind*2 + 1, IndMaxElemTwo);
	if (MaxOne > MaxTwo){
		IndMaxElem = IndMaxElemOne;
		return MaxOne;
	}
	else{
		IndMaxElem = IndMaxElemTwo;
		return MaxTwo;
	}
}

void IntervalTree::Replace(int IndOfElem, int value){
	int IndNew = IndOfElem + shift;
	ourTree[IndNew].valMax = value;
	IndNew /= 2;
	while (IndNew > 0){
		if (ourTree[IndNew*2].valMax > ourTree[IndNew*2 + 1].valMax){
			ourTree[IndNew].valMax = ourTree[IndNew*2].valMax;
			ourTree[IndNew].ind = ourTree[IndNew*2].ind;
		}
		else{
			ourTree[IndNew].valMax = ourTree[IndNew*2 + 1].valMax;
			ourTree[IndNew].ind = ourTree[IndNew*2 + 1].ind;
		}
		IndNew /= 2;
	}

}
int lower_bound(vector<my>& arr, string& s){
	int l = 0, r = arr.size() - 1;
	while (l + 1 < r){
		int middle = (l + r)/2;
		if (arr[middle].s <= s)
			l = middle;
		else
			r = middle;
	}
	if (arr[l].s == s) return l;
	if (arr[r].s == s) return r;
	return l;
}
int upper_bound(vector<my>& arr, string& s){
	int l = 0, r = arr.size();
	while (l + 1 < r){
		int middle = (l + r)/2;
		if (arr[middle].s < s)
			l = middle;
		else
			r = middle;
	}
	if (arr[r].s == s) return r + 1;
	if (arr[l].s == s || arr[r].s > s) return r;
	return l;
}
void Back(vector<pair<int, int>>& values, IntervalTree& RMQ){
	for (int i = 0; i < values.size(); i++)
		RMQ.Replace(values[i].first, values[i].second);
}
void processing(string& s, vector<my>& arr, IntervalTree& RMQ, int k){
	int low = lower_bound(arr, s);
	s.push_back('z' + 1);
	int up = upper_bound(arr, s);
	int middle;
	if (low >= up)
		return;
	vector<pair<int, int>> values;
	for (int i = 0; i < k; i++){
		int middle = 0;
		int res = RMQ.GetMax(low + 1, up, 1, middle);
		if (res == numeric_limits<int>::min()){
			Back(values, RMQ);
			return;
		}
		cout << arr[middle].s << " " << arr[middle].rate << endl;
		pair<int, int> x; x.first = middle; x.second = arr[middle].rate;
		values.push_back(x);
		RMQ.Replace(middle + 1, numeric_limits<int>::min());
	}
	Back(values, RMQ);

}
int compare(my x, my y){
	return(x.s < y.s);
}
int main( void ){
	freopen("output.txt","w",stdout);
	ifstream inOne("Dickens.txt");
	HashTable DictionaryHT;
	string s;
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
			}
		}
	}
	vector<my> dictionary;
	HashTable::iterator It = DictionaryHT.begin();
	while (It != DictionaryHT.end()){
		dictionary.push_back(*It);
		++It;
	}
	inOne.close();
	sort(dictionary.begin(), dictionary.end(), compare);
	IntervalTree RMQ(dictionary);
	ifstream inTwo("input.txt");
	int k;

	while (!inTwo.eof()){
		inTwo >> s >> k;
		processing(s, dictionary, RMQ, k);
	}
	return 0;
}
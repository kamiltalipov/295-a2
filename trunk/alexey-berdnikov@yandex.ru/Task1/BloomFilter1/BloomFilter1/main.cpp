// Я хочу спать, поэтому тексты не прикрутил.
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cassert>

using namespace std;

class hash_function {
	class random_function {
		int val[224];
	public:
		random_function() { for (int i = 0; i < 224; ++i) val[i] = (rand()<<15)+rand(); }
		int operator()(char c) const { return val[c-32]; }
	};

	vector<random_function> h;
public:
	int operator()(const string& s)
	{
		if (s.length() > h.size()) h.resize(s.length());

		int result = 0;
		for (unsigned i = 0; i < s.length(); ++i) {
			int a = h[i](s[i]);
			result ^= a;
		}
		return result;
	}
};

class bloom_filter {
	vector<bool> filter;
	vector<hash_function> hash;
public:
	bloom_filter(unsigned, unsigned);
	void add(const string&);
	bool search(const string&);
};

bloom_filter::bloom_filter(unsigned size, unsigned k)
{
	unsigned d = 0;
	unsigned m = 1;
	while (m < size) {
		++d;
		m <<= 1;
	}

	srand(unsigned(time(NULL)));
	filter.resize(m);
	hash.resize(k);
}

void bloom_filter::add(const string& s)
{
	for (unsigned i = 0; i < hash.size(); ++i)
		filter[hash[i](s)%filter.size()] = true;
}

bool bloom_filter::search(const string& s)
{
	for (unsigned i = 0; i < hash.size(); ++i)
		if (!filter[hash[i](s)%filter.size()]) return false;
	return true;
}

class hash_table {
public:
	class iterator;
private:
	class element {
	public:
		vector<list<element*>>* table;
		int index;
		list<element*>::iterator list_it;
		int key;
		string value;

		element(int k, const string& s) : key(k), value(s) { }
	};

	vector<list<element*>> table;
	int number_of_elements;
	int min_index;

	iterator make_iterator(element*) const;
	hash_function hash;
	iterator find(int, const string&);
	iterator insert(vector<list<element*>>&, element*, int&);
	void reallocate();

public:
	class iterator {
		element* element_ptr;
		
		friend class hash_table;

	public:
		iterator& operator++();
		iterator& operator--();
		string operator*() const;
		const string* operator->() const;
		bool operator== (const iterator& other) const { return element_ptr == other.element_ptr; }
		bool operator!= (const iterator& other) const { return !(*this==other); }
	};

	hash_table();
	~hash_table();
	iterator find(const string&);
	iterator insert(const string&);
	void erase(iterator);
	void erase(const string&);
	iterator begin() const;
	iterator end() const;
	int size() const { return number_of_elements; }
	int max_number_of_collisions() const;
};

hash_table::iterator& hash_table::iterator::operator++()
{
	const vector<list<element*>>& table = *(element_ptr->table);
	int index = element_ptr->index;
	list<element*>::const_iterator list_it = element_ptr->list_it;

	++list_it;
	while (list_it==table[index].end()) {
		++index;
		list_it = table[index].begin();
	}
	element_ptr = *list_it;
	return *this;
}

hash_table::iterator& hash_table::iterator::operator--()
{
	const vector<list<element*>>& table = *(element_ptr->table);
	int index = element_ptr->index;
	list<element*>::const_iterator list_it = element_ptr->list_it;

	while (list_it==table[index].begin()) {
		--index;
		list_it = table[index].end();
	}
	--list_it;
	element_ptr = *list_it;
	return *this;
}

string hash_table::iterator::operator*() const
{
	element e = *element_ptr;

	assert(e.key!=-1);
	return e.value;
}

const string* hash_table::iterator::operator->() const
{
	element e = *element_ptr;

	assert(e.key!=-1);
	return &e.value;
}

hash_table::iterator hash_table::make_iterator(element* ptr) const
{
	iterator it;
	it.element_ptr = ptr;
	return it;
}

hash_table::iterator hash_table::find(int hash_value, const string& s)
{
	int index = hash_value%table.size();
	list<element*>::const_iterator list_it = table[index].begin();
	while (list_it!=table[index].end() && ((*list_it)->key!=hash_value||(*list_it)->value!=s)) ++list_it;
	return list_it!=table[index].end() ? make_iterator(*list_it) : end();
}

hash_table::iterator hash_table::insert(vector<list<element*>>& table, element* element_ptr, int& min_index)
{
	int index = (element_ptr->key)%table.size();
	if (index == -1) index += table.size();

	element_ptr->table = &(this->table);
	element_ptr->index = index;
	table[index].push_front(element_ptr);
	element_ptr->list_it = table[index].begin();
	++number_of_elements;
	min_index = min(index,min_index);
	return make_iterator(element_ptr);
}

void hash_table::reallocate()
{
	vector<list<element*>> new_table(2*table.size());
	int new_min_index = new_table.size();

	number_of_elements = -1;
	iterator it = end();
	while (it != begin()) {
		element* element_ptr = it.element_ptr;
		--it;
		insert(new_table,element_ptr,new_min_index);
	}
	insert(new_table,it.element_ptr,new_min_index);
	swap(table,new_table);
	min_index = new_min_index;
}

hash_table::hash_table() : table(1), number_of_elements(-1), min_index(0)
{
	element* end = new element(-1,"");
	insert(table,end,min_index);
}

hash_table::~hash_table()
{
	iterator it = begin();
	while (it != end()) {
		element* ptr = it.element_ptr;
		++it;
		delete ptr;
	}
	delete end().element_ptr;
}

hash_table::iterator hash_table::find(const string& s)
{
	return find(hash(s),s);
}

hash_table::iterator hash_table::insert(const string& s)
{
	int hash_value = hash(s);
	iterator it = find(hash_value,s);

	if (it == end()) {
		if (size() == 4*table.size()) reallocate();
		element* new_element = new element(hash_value,s);
		it = insert(table,new_element,min_index);
	}
	return it;
}

void hash_table::erase(iterator it)
{
	element* element_ptr = it.element_ptr;

	assert(it!=end());
	if (it == begin()) min_index = (++it).element_ptr->index;
	table[element_ptr->index].erase(element_ptr->list_it);
	delete element_ptr;
	--number_of_elements;
}

void hash_table::erase(const string& s)
{
	int hash_value = hash(s);
	iterator it = find(hash_value,s);

	if (it != end()) erase(it);
}

hash_table::iterator hash_table::begin() const
{
	return make_iterator(table[min_index].front());
}

hash_table::iterator hash_table::end() const
{
	return make_iterator(table.back().back());
}

int hash_table::max_number_of_collisions() const
{
	unsigned result = table.back().size()-1;
	for (int i = table.size()-2; i >= 0; --i) result = max(result,table[i].size());
	return result;
}

void check()
{
	bloom_filter filter(1000000,20);
	filter.add("ololo");
	filter.add("sdfgdsfhgf");
	filter.search("ololo");
}

int main()
{
	check();
	return 0;
}
#include < iostream >
#include < vector >
#include < list >
#include < string >
#include < cassert >

using namespace std;

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
	const int mod;
	int number_of_elements;
	int min_index;

	iterator make_iterator(element*) const;
	int hash(const string&) const;
	iterator find(int, const string&) const;
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
	iterator find(const string&) const;
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

int hash_table::hash(const string& s) const
{
	int hash = 0;
	for (unsigned i = 0; i < s.length(); ++i) hash = (hash*256+128+s[i])%mod;
	return hash;
}

hash_table::iterator hash_table::find(int hash_value, const string& s) const
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

hash_table::hash_table() : table(1), mod(8388593), number_of_elements(-1), min_index(0)
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

hash_table::iterator hash_table::find(const string& s) const
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
	for (int i = table.size()-1; i >= 0; --i) result = max(result,table[i].size());
	return result;
}

void check()
{
	hash_table a;
	a.insert("ololo");
	a.insert("dfsf");
	a.insert("ololo");
	hash_table::iterator end = a.end();
	a.insert("edg");
	a.insert("ollo");
	a.insert("dfggf");
	cout << a.max_number_of_collisions() << endl;
	a.erase("dfggf");
	a.erase("ertdfgdgrdg");
	a.erase("ollo");
	a.erase("edg");
	assert(end==a.end());
	for (hash_table::iterator it = a.begin(); it != a.end(); ++it) cout << *it << endl;

/*	hash_table table;
	string request, s;
	for (;;) {
		cin >> request;
		if (request == "#") exit(0);
		cin >> s;
		if (request == "+") table.insert(s);
		if (request == "-") table.erase(s);
		if (request == "?") cout << (table.find(s)==table.end()?"NO\n":"YES\n");
	} */
}

int main()
{
	check();
	_CrtDumpMemoryLeaks();
	return 0;
}
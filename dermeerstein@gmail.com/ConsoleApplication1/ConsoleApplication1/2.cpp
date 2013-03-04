#include <iostream>
#include <map>
#include <string>

using namespace std;


int main()
{
	pair <map<string, int>::iterator, bool> p;
	map <string, int> m;
	p = m.insert(make_pair("a", 5));
	cout << (p.second ? "new" : "already exists") << endl; 
	p = m.insert(make_pair("a", 4));
	cout << (p.second ? "new" : "already exists") << endl; 
	return 0;
}
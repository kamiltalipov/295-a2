#include <iostream>
#include <list>

using namespace std;

int main()
{
	list <int> lst1;
	list <int> lst2;
	for (int i = 0; i < 5; i++)
	{
		lst1.insert(lst1.begin(), i);
		lst2.insert(lst2.begin(), i);
	}
	lst1.splice(lst1.end(), lst2); //O(1)
	return 0;
}
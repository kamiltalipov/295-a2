#include <iostream>
#include <list>
#include <queue>

using namespace std;


int main()
{
	list<int> lst;
	for (int i = 0; i < 5; i++)
	{
		lst.insert(lst.begin(), i);
	}
	queue<int, list<int> > q(lst);
	return 0;
}
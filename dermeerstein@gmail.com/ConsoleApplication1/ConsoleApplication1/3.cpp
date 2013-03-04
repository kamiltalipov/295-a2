#include <iostream>
#include <set>

using namespace std;

struct Le 
{
	bool operator() (int a, int b)
	{
		return (a > b);
	}
};

int main()
{
	set<int, Le> st;
	st.insert(4);
	st.insert(3);
	cout << *st.begin();
	return 0;
}
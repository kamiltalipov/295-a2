#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <map>
#include <utility>
#include <algorithm>
#include <cassert>
#include <cmath>

using namespace std;

typedef pair<int, int> point;
typedef pair<int, point> element;

inline int h(const point& p)
{
	return min(p.first,p.second);
}

void relax(map<point, int>& distance, const point& p, int d, priority_queue<element>& q)
{
	map<point, int>::iterator it = distance.find(p);

	if (it == distance.end())
		it = distance.insert(make_pair(p,0)).first;
	else if (d <= it->second)
		return;
	it->second = d;
	q.push(element(d+h(p),p));
}

int LCS(string& s1, string& s2)
{
	map<point, int> distance;
	priority_queue<element> q;

	point s(s1.length(),s2.length());
	distance[s] = 0;
	q.push(element(h(s),s));
	for(;;)
	{
		element u = q.top();
		q.pop();
		
		int d = u.first-h(u.second);
		int i = u.second.first;
		int j = u.second.second;

		if (i==0 && j==0) return d;
		if (d < distance[u.second]) continue;
		if (i) {
			point p(i-1,j);
			relax(distance,p,d,q);
		}
		if (i && j) {
			point p(i-1,j-1);
			relax(distance,p,d+(s1[p.first]==s2[p.second]),q);
		}
		if (j) {
			point p(i,j-1);
			relax(distance,p,d,q);
		}
	}
}

int main()
{
	ifstream text1("text1.txt");
	ifstream text2("text2.txt");
	string s1, s2;

	getline(text1,s1,'\0');
	getline(text2,s2,'\0');
	cout << LCS(s1,s2);
	return 0;
}
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <set>
using namespace std;
struct vertex
{
	int x, y, dist, estimate;
	vertex(int X, int Y, int Dist, int Estimate)
	{
		x=X, y=Y, dist=Dist, estimate=Estimate;
	}
	bool operator<(const vertex &b) const
	{
		return dist+estimate>b.dist+b.estimate;
	}
};
int estimate(int x, int y, int len1, int len2)
{
	return abs(x-len1+len2-y);
}
int main()
{
	ifstream text1("text1.txt");
	ifstream text2("text2.txt");
	string s1, s2;
	getline(text1, s1, '\0');
	getline(text2, s2, '\0');
	text1.close();
	text2.close();
	int len1=s1.length(), len2=s2.length();
	priority_queue <vertex> q;
	q.push(vertex(0, 0, 0, 0));
	set < pair <int, int> > used;
	int x, y, dist;
	while(!q.empty())
	{
		x=q.top().x;
		y=q.top().y;
		dist=q.top().dist;
		q.pop();
		if(x==len1&&y==len2)
		{
			cout<<dist;
			break;
		}
		if(used.find(make_pair(x, y))!=used.end())
			continue;
		used.insert(make_pair(x, y));
		if(x!=len1&&y!=len2&&s1[x]==s2[y])
			q.push(vertex(x+1, y+1, dist, estimate(x+1, y+1, len1, len2)));
		if(x!=len1&&y!=len2&&s1[x]!=s2[y])
			q.push(vertex(x+1, y+1, dist+1, estimate(x+1, y+1, len1, len2)));
		if(x!=len1)
			q.push(vertex(x+1, y, dist+1, estimate(x+1, y, len1, len2)));
		if(y!=len2)
			q.push(vertex(x, y+1, dist+1, estimate(x, y+1, len1, len2)));
	}
	return 0;
}
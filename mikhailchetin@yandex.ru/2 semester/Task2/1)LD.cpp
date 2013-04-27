#include<iostream>
#include<string>
#include<algorithm>
#include<fstream>
#include<queue>
#include<set>
using namespace std;

struct vertex
{
	int x;
	int y;
	int distance;
	int potential;
	vertex(int _x, int _y, int _distance, int _potential)
	{
		x=_x;
		y=_y;
		distance=_distance;
		potential=_potential;
	}
	bool operator <(const vertex &other) const
	{
		return (distance+potential)>(other.distance+other.potential);
	}
};

int potential(int x,int y,int l1,int l2)
{
	//return max(x,y)-min(x,y);   //для случая, когда l1==l2
	return max(y*l1/l2-x,x*l2/l1-y);
}

int main()
{
	ifstream inp1("input1.txt");
    ifstream inp2("input2.txt");
    string s1;
    string s2;
    getline(inp1, s1, '\0');
    getline(inp2, s2, '\0');
    inp1.close();
    inp2.close();
    int l1 = s1.length();
    int l2 = s2.length();
    priority_queue <vertex> q;
	int x,y,distance;
	set<pair<int,int>> used;
	q.push(vertex(0,0,0,0));
	while(!q.empty())
	{
		x=q.top().x;
		y=q.top().y;
		distance=q.top().distance;
		if(x==l1 && y==l2)
		{
			cout<<distance;
			return 0;
		}
		q.pop();
		if(used.find(make_pair(x,y))!=used.end())
            continue;
        used.insert(make_pair(x,y));
		
		if(x!=l1 && y!=l2 && s1[x]==s2[y])
			q.push(vertex(x+1,y+1,distance,potential(x+1,y+1,l1,l2)));
		if(x!=l1 && y!=l2 && s1[x]!=s2[y])
			q.push(vertex(x+1,y+1,distance+1,potential(x+1,y+1,l1,l2)));
		if(x!=l1)
			q.push(vertex(x+1,y,distance+1,potential(x+1,y,l1,l2)));
		if(y!=l2)
			q.push(vertex(x,y+1,distance+1,potential(x,y+1,l1,l2)));
	}
	return 0;
}
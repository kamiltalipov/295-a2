#include<iostream>
#include<string.h>
#include<string>
#include<vector>
#include<set>
#include<queue>
#include<algorithm>
#include<fstream>
using namespace std;

struct a_star{
	int x;
	int y;
	int dist;
	double poten;
	a_star (int x1, int y1, int dist1, double poten1){
		x = x1;
		y = y1;
		dist = dist1;
		poten = poten1;
	}
	bool operator <(const a_star &other) const{
		return ((double)dist+poten)>((double)other.dist+other.poten);
	}
};

double potential (int x, int y, int len_1, int len_2){
	if(len_1==len_2)
		return abs(x-y);
	else{
		double dist_1 = (double)x * (double)len_2/(double)len_1 - (double)y;
		double dist_2 = (double)y * (double)len_1/(double)len_2 - (double)x;
		return max(abs(dist_1),abs(dist_2));
	}
}
int main(){
	ifstream input_1("input1.txt");
    ifstream input_2("input2.txt");
    string s1,s2;
    getline(input_1, s1, '\0');
    getline(input_2, s2, '\0');
    input_1.close();
    input_2.close();
    int len_1 = s1.length();
    int len_2 = s2.length();
	int x,y,dist;
    priority_queue <a_star> q;
	set< pair<int,int> > used;
	q.push(a_star(0,0,0,0));
	while(!q.empty()){
		x=q.top().x;
		y=q.top().y;
		if(used.find(make_pair(x,y))!=used.end())
            continue;
        used.insert(make_pair(x,y));
		dist=q.top().dist;
		if(x==len_1 && y==len_2){
			cout<<dist;
			return 0;
		}
		q.pop();
		if(x!=len_1 && y!=len_2 && s1[x]==s2[y])
			q.push(a_star(x+1,y+1,dist,potential(x+1,y+1,len_1,len_2)));
		if(x!=len_1 && y!=len_2 && s1[x]!=s2[y])
			q.push(a_star(x+1,y+1,dist+1,potential(x+1,y+1,len_1,len_2)));
		if(x!=len_1)
			q.push(a_star(x+1,y,dist+1,potential(x+1,y,len_1,len_2)));
		if(y!=len_2)
			q.push(a_star(x,y+1,dist+1,potential(x,y+1,len_1,len_2)));
	}
}
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cmath>
#include <string>
#include <vector>
#include <map>
#include <deque>
#include <cassert>


#define DEBUG 1

using namespace std;

class myclass{
public:
	void Read(){
		first = "";
		second = "";
		fstream FirstIn;
		FirstIn.open("input1.txt");
		string cur = "";
		while (FirstIn >> cur){
			first += " " + cur;
			cur = "";
		}
		FirstIn.close();
		
		fstream SecondIn;
	
		SecondIn.open("input2.txt");
		cur = "";
		while (SecondIn >> cur){
			second += " " + cur;
			cur = "";
		}
		SecondIn.close();
		
		n = first.length() - 1;
		m = second.length() - 1;
	}

	long long num(int x, int y){
		return ((long long)x*(m + 1) + (long long)y);
	}
	
	void get_by_num(long long num, int &x, int &y){
		//assert(x != 0);
		//x =  num/x;// Здесь были инопланетяне и написали другой код.
		
		
		
		long long nx = num/(m + (long long) 1); 
		x = num/(m + 1);  // new
		x = nx;
		
		y = num - (nx*(m + (long long) 1));
	}

	int Solve(){
		int result = max(n, m) + 1;
		map<long long, pair<int, bool> > used;
		deque<long long> vert;
		long long s = 0;
		/* Уважаемая Мария,
		 * 		прошу вас прочитать мой скромный комментарий.
		 * 		А еще прошу не делить в get_by_num на ноль,
		 * 		или неинициализированное число. Далее анонимусу стало 
		 * 		влом.
		 * 
		 *		 
		 * 		Извините за вторжение в вашу интеллектуальную собственность.		 
		 */
		vert.push_front(s);
		pair<int, bool> coast(0, 0);
		used.insert(pair<long long, pair<int, bool> >(s, coast));
		long long f = num(n, m);
		
		while (!vert.empty()){
			long long current = vert.front();
			map<long long, pair<int, bool> >::iterator it = used.find(current);
			int x, y, dist = (it->second).first;
			bool arc = (it->second).second;
			if (arc){
				current = vert.back();
				it = used.find(current);
				dist = (it->second).first;
				vert.pop_back();
			}
			else
				vert.pop_front();
			
			get_by_num(it->first, x, y);
			
			if (it->first == f){
				return dist;	
			}
			if (x + 1 <= n){
				long long new_num = num(x + 1, y);
				int new_dist = dist + 1;
				map<long long, pair<int, bool> >::iterator current_it = used.find(new_num);
				if (current_it == used.end()){
					pair<int, bool> coast(new_dist, 1);
					used.insert(pair<long long, pair<int, bool> >(new_num, coast));
					vert.push_back(new_num);
				}
				else
					if ((current_it->second).first > new_dist){
						(current_it->second).first = new_dist;
						(current_it->second).second = 1;
					}
			}
			
			if (y + 1 <= n){
				long long new_num = num(x, y + 1);
				int new_dist = dist + 1;
				map<long long, pair<int, bool> >::iterator current_it = used.find(new_num);
				if (current_it == used.end()){
					pair<int, bool> coast(new_dist, 1);
					used.insert(pair<long long, pair<int, bool> >(new_num, coast));
					vert.push_back(new_num);
				}
				else
					if ((current_it->second).first > new_dist){
						(current_it->second).first = new_dist;
						(current_it->second).second = 1;
					}
			}
			if (x + 1 <= n && y + 1 <= m){
				 long long new_num = num(x + 1, y + 1);
				 int new_dist = dist + 1;
				 int arc = 1;
				 if (first[x + 1] == second[y + 1]){
					new_dist = new_dist - 1;
					--arc;
				 }
				 map<long long, pair<int, bool> >::iterator current_it = used.find(new_num);
				 
				 if (current_it == used.end()){
					 pair<int, bool> coast(new_dist, arc);
					used.insert(pair<long long, pair<int, bool> >(new_num, coast));
					if (dist == new_dist)
						vert.push_front(new_num);
					else
						vert.push_back(new_num);
				 }
				 else
					if ((current_it->second).first > new_dist){
						(current_it->second).first = new_dist;
						(current_it->second).second = arc;
					}
			}
		}
		return -1;
	}
	
	string first, second;
	long long n, m;
};

int main(){
	
	myclass Dist;
	Dist.Read();
	cout << Dist.Solve();
	return 0;
}

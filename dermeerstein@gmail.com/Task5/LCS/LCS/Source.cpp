#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <deque>
#include <map>

using namespace std;

int LCS(string &s1, string &s2)
{
	map<pair<int, int>, int> dist;
	dist[make_pair(0, 0)] = 0;
	pair<int, int> finish = make_pair(s1.size(), s2.size());
	deque<pair<int, int>> deq;
	deq.push_back(make_pair(0, 0));
	pair<int, int> cur_v, next_v;
	int dx[] = {0, 1, 1};
	int dy[] = {1, 0, 1};
	while(!deq.empty())
	{
		cur_v = deq.front();
		deq.pop_front();
		for (int i = 0; i < 3; ++i)
		{
			next_v = make_pair(cur_v.first + dx[i], cur_v.second + dy[i]);
			if (next_v.first > finish.first || next_v.second > finish.second)
				continue;
			if (next_v.first == 0 || next_v.second == 0)
			{
				if (dist.find(next_v) == dist.end() || dist[next_v] > dist[cur_v] + 1)
				{
					dist[next_v] = dist[cur_v] + 1;
					deq.push_back(next_v);
				}
			}
			else if (s1[next_v.first - 1] == s2[next_v.second - 1])
			{
				if (dist.find(next_v) == dist.end() || dist[next_v] > dist[cur_v])
				{
					dist[next_v] = dist[cur_v];
					deq.push_front(next_v);
				}
			}
			else
			{
				if (dist.find(next_v) == dist.end() || dist[next_v] > dist[cur_v] + 1)
				{
					dist[next_v] = dist[cur_v] + 1;
					deq.push_back(next_v);
				}
			}
			if (dist.find(finish) != dist.end())
			{
				int a;
				a = dist[finish];
				cout << a;
				cout.flush();
				return a;
			}
		}
	}
}

int main()
{
	string s1, s2;
	ifstream fin1("file1.txt");
	ifstream fin2("file2.txt");
	getline(fin1, s1, '\0');
	getline(fin2, s2, '\0');
	int ans;
	ans = LCS(s1, s2);
	cout << ans;
	return 0;
}
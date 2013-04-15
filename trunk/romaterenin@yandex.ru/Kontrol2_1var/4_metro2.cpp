#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;
int main(){
	int n;
	cin>>n;
	vector < pair < int, pair<int,int> > > g; // ��� + �������_1 + �������_2
	int k;
	cin>>k;
	for(int i=0;i<k;i++){
		int a,b,time;
		cin>>a>>b>>time;
		g.push_back(make_pair(time,make_pair(a,b)));
	} // ��� ��� ����� ������� ����� ��������� �� ����� �� �����, �� ����� �������, ��� ��������� ����� �����, � �� �������
	int cost = 0;
	vector < pair<int,int> > res;
	sort (g.begin(), g.end());
	vector<int> tree_id (n);
	for (int i=0; i<n; i++)
		tree_id[i] = i;
	for (int i=0; i<k; i++){
		int a = g[i].second.first,  b = g[i].second.second,  len = g[i].first;
		if (tree_id[a] != tree_id[b]){
			cost += len;
			res.push_back (make_pair (a, b));
			int old_id = tree_id[b],  new_id = tree_id[a];
			for (int j=0; j<n; j++)
				if (tree_id[j] == old_id)
					tree_id[j] = new_id;
		}
	}
	// ������� ������ ������ ����� �� res
	return 0;
}
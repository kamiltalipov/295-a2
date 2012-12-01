#include<iostream>
#include<stdio.h>
#include<vector>
#include<string>

const static int MAXINT = 2147483647;

struct Tree{
	long long valMin, l, r, sum;
};

using namespace std;
class IntervalTree{
public:
	IntervalTree(int n);
	void Add(int l, int r, int val, int ind);
	int GetMin(int l, int r, int ind);
	void read(int n);
private:
	void push(int ind);
	vector<Tree> ourTree;
	int size, shift;
};

IntervalTree::IntervalTree(int n){
	shift = n - 1;
	int deg = 0;
	while (shift != 0){
		shift = shift >> 1;
		deg++;
	}
	shift = (1 << deg);
	size = shift*2;
	shift--;
	ourTree.resize(size);
}

void IntervalTree::read(int n){
	for (int i = shift + 1; i < shift + n + 1; i++){
		cin >> ourTree[i].valMin;
		ourTree[i].l = i;
		ourTree[i].r = i;
	}
	for (int i = shift + n + 1; i < size; i++){
		ourTree[i].valMin = MAXINT;
		ourTree[i].l = i;
		ourTree[i].r = i;
	}

	for (int i = shift; i > 0; i--){
		ourTree[i].valMin = min(ourTree[i*2].valMin, ourTree[i*2 + 1].valMin);
		ourTree[i].l = ourTree[i*2].l;
		ourTree[i].r = ourTree[i*2 + 1].r;
	}
}

void IntervalTree::push(int ind){
	ourTree[ind].valMin += ourTree[ind].sum;
	if (ind*2 < size){
		ourTree[ind*2].sum += ourTree[ind].sum;
		ourTree[ind*2 + 1].sum += ourTree[ind].sum;
	}
	ourTree[ind].sum = 0;
}

void IntervalTree::Add(int l, int r, int val, int ind){
	int left = l + shift;
	int right = r + shift;
	push(ind);
	if (ourTree[ind].l > right || ourTree[ind].r < left)
		return;
	if (left <= ourTree[ind].l && ourTree[ind].r <= right){
		ourTree[ind].sum += val;
		push(ind);
		return;
	}
	Add(l, r, val, ind*2);
	Add(l, r, val, ind*2 + 1);
	ourTree[ind].valMin = min(ourTree[ind*2].valMin, ourTree[ind*2 + 1].valMin);
}
int IntervalTree::GetMin(int l, int r, int ind){
	int left = l + shift;
	int right = r + shift;
	push(ind);
	if (ourTree[ind].l > right || ourTree[ind].r < left)
		return MAXINT;
	if (left <= ourTree[ind].l && ourTree[ind].r <= right)
		return ourTree[ind].valMin;
	return min(GetMin(l, r, ind*2), GetMin(l, r, ind*2 + 1));
}
int main( void ){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int n, m, l, r, val;
	cin >> n;
	IntervalTree arr(n);
	arr.read(n);
	cin >> m;
	for (int i = 0; i < m; i++){
		string c;
		cin >> c;
		if (c == "m"){
			cin >> l >> r;
			cout << arr.GetMin(l, r, 1) << " ";
		}
		else{
			cin >> l >> r >> val;
			arr.Add(l, r, val, 1);
		}
	}
	return 0;
}
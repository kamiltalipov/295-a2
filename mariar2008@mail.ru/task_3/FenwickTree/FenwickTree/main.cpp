#include<stdio.h>
#include<iostream>
#include<vector>
#include<string>

using namespace std;

class FenwickTree{
public:
	FenwickTree(int n);
	int GetSum(int l, int r);
	void Update(int ind, int val);
private:
	int size;
	vector<int>ourArr;
	vector<int>Tree;
	void MakeTree();
	int GetSum(int ind);
	int Func(int ind);
};

int FenwickTree::Func(int ind){
	return ind & (ind + 1);
}
void FenwickTree::MakeTree(){
	Tree[0] = ourArr[0];
	for (int i = 1; i < size; i++)
		Tree[i] = Tree[i - 1] + ourArr[i];
	for (int i = size - 1; i >= 0; i--)
		if (Func(i) > 0)
			Tree[i] -= Tree[Func(i) - 1];
}
FenwickTree::FenwickTree(int n){
	ourArr.resize(n + 1);
	Tree.resize(n + 1);
	size = n + 1;
	MakeTree();
}

int FenwickTree::GetSum(int ind){
	int cur = ind, result = 0;
	while (cur >= 0){
		result += Tree[cur];
		cur = Func(cur) - 1;
	}
	return result;
}
int FenwickTree::GetSum(int l, int r){
	return(GetSum(r) - GetSum(l - 1));
}
void FenwickTree::Update(int ind, int val){
	int cur = ind;
	while (cur < size){
		Tree[cur] += val;
		cur = cur | (cur + 1);
	}
	ourArr[ind] += val;
}

int main( void ){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	
	int n, result = 0;
	cin >> n;
	FenwickTree ourArr(n);
	vector<int> perm(n);
	for (int i = 0; i < n; i++){
		cin >> perm[i];
		result += ourArr.GetSum(perm[i] + 1, n);
		ourArr.Update(perm[i], 1);
	}
	cout << result;
}
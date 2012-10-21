#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct student{
	int mark;
	string name, number;
};

void countingSort(vector <student>& arr) {
	vector <int> prefixSum(6, 0);
	for (int i = 0;i < arr.size();++i)	{
		prefixSum[arr[i].mark]++;
	}
	for (int i = 3;i < prefixSum.size();++i) {
		prefixSum[i] = prefixSum[i - 1] + prefixSum[i]; 
	} // ќтныне prefixSum[i] - место, куда надо добавить следующего ученика с оценкой i; блоки заполн€ютс€ с конца
	vector <student> res(arr.size());
	for (int i = 0;i < arr.size();i++) {
		res[(prefixSum[arr[i].mark] - 1)] = arr[i];	
		prefixSum[arr[i].mark]--;
	}	
	for (int i = 0;i < arr.size();i++) {
		arr[i] = res[i];
	}
} 

int main() {
	freopen("input.txt", "r", stdin);
	//freopen("arr.txt", "w", stdout);
	student tmp;
	int n;
	vector <student> arr;
	cin >> n;
	for (int i = 0;i < n;i++) {
		cin >> tmp.number >> tmp.name >> tmp.mark;
		arr.push_back(tmp);
	}
	countingSort(arr);
	for (int i = 0;i < arr.size();++i) {
		cout << arr[i].number << " " << arr[i].name << " " << arr[i].mark << endl;
	}
	return 0;
}
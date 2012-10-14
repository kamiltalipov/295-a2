#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct student{
	int mark;
	string name, number;
};

student* countingSort(vector <student>& arr) {
	vector <int> prefixSum(6);
	memset(&prefixSum[0], 0, sizeof(prefixSum));
	for (int i = 0;i < arr.size();++i)	{
		prefixSum[arr[i].mark]++;
	}
	for (int i = 3;i < prefixSum.size();++i) {
		prefixSum[i] = prefixSum[i - 1] + prefixSum[i]; 
	} // ќтныне prefixSum[i] - место, куда надо добавить следующего ученика с оценкой i; блоки заполн€ютс€ с конца
	student* res = new student[arr.size()];
	for (int i = 0;i < arr.size();i++) {
		res[(prefixSum[arr[i].mark] - 1)] = arr[i];	
		prefixSum[arr[i].mark]--;
	}	
	return res;
} 

int main() {
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	student tmp;
	int n;
	vector <student> input;
	cin >> n;
	for (int i = 0;i < n;i++) {
		cin >> tmp.number >> tmp.name >> tmp.mark;
		input.push_back(tmp);
	}
	student* output = countingSort(input);
	for (int i = 0;i < input.size();++i) {
		cout << (output + i)->number << " " << (output + i)->name << " " << (output + i)->mark << endl;
	}
	return 0;
}
#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct student{
	int mark;
	string name, number;
};

vector <student>* countingSort(vector <student>* arr) {
	vector <int> prefixSum(6);
	for (int i = 0;i < arr->size();++i)	{
		prefixSum[(arr->begin() + i)->mark]++;
	}
	for (int i = 3;i < prefixSum.size();++i) {
		prefixSum[i] = prefixSum[i - 1] + prefixSum[i]; 
	} // ќтныне prefixSum[i] - место, куда надо добавить следующего ученика с оценкой i; блоки заполн€ютс€ с конца
	vector <student>* res = new vector <student> (arr->size());
	for (int i = 0;i < arr->size();i++) {
		*(res->begin() + (prefixSum[(arr->begin() + i)->mark] - 1)) = *(arr->begin() + i);	
		prefixSum[(arr->begin() + i)->mark]--;
	}	
	return res;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	student tmp;
	int n;
	vector <student> input;
	cin >> n;
	for (int i = 0;i < n;i++) {
		cin >> tmp.number >> tmp.name >> tmp.mark;
		input.push_back(tmp);
	}
	vector <student>* output = countingSort(&input);
	for (int i = 0;i < output->size();++i) {
		cout << (output->begin() + i)->number << " " <<(output->begin() + i)->name << " " << (output->begin() + i)->mark << endl;
	}
	return 0;
}
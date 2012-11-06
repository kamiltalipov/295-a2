#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class operation {
public:	
	int index, type;
	char element;
	operation* eval(int ind, int typ, char elem) {
		index = ind;
		type = typ;
		element = elem;
		return this;
	}
};

int Hirschberg(string& s1, string& s2, vector <operation>& ans, int l1, int r1, int l2, int r2) {
	operation done;
	if (l2 == r2) {
		for (int i = l1;i < r1;i++) {
			ans.push_back(*done.eval(i + 1, 0, s1[i]));//ans = ans + "Delete " + s1[i] + " from " + str(i + 1) + "\n"; 
		} 
		return r1 - l1;		
	} 
	if (l1 == r1) {
		for (int i = l2;i < r2;i++) ans.push_back(*done.eval(l1, 1, s2[i]));//ans = ans + "Add " + s2[i] + " after " + str(l1) + "\n";
		return r2 - l2;
	}
	if (r2 == l2 + 1) {
		int find, k;
		for (k = l1;k < r1;k++) {
			if (s1[k] == s2[l2]) break;	
		}
		if (k == r1) {
			ans.push_back(*done.eval(l1 + 1, 2, s2[l2]));//ans = ans + "Substitute " + s1[l1] + " in " + str(l1 + 1) + " with " + s2[l2] + "\n";	
			for (int i = l1 + 1;i < r1;i++) {
			ans.push_back(*done.eval(i + 1, 0, s1[i]));//ans = ans + "Delete " + s1[i] + " from " + str(i + 1) + "\n"; 
			}
			return r1 - l1;
		}
		find = k;
		for (int i = l1;i < r1;i++) {
			if (i != find) {
				ans.push_back(*done.eval(i + 1, 0, s1[i]));//ans = ans + "Delete " + s1[i] + " from " + str(i + 1) + "\n"; 
			} 
		}
		return r1 - l1 - 1;
	}

	vector <int> col[2];
	col[1].resize(r1 - l1 + 1);
	for (int i = 0;i < r1 - l1 + 1;i++) col[0].push_back(i);
	int mid = (r2 + l2) / 2;
	for (int i = 0;i < mid;i++) { //Calculating forward
		col[(i + 1) % 2][0] = i + 1;
		for (int j = 1;j < col[i % 2].size();j++) {
			col[(i + 1) % 2][j] = min(min(col[i % 2][j] + 1, col[(i + 1) % 2][j - 1] + 1), col[i % 2][j - 1] + (s1[l1 + j - 1] != s2[i]));
		}
	}
	vector <int> left(col[mid % 2].begin(), col[mid % 2].end()); // result for the left half

	for (int i = r1 - l1;i >= 0;i--) col[0][i] = r1 - l1 - i;
	for (int i = 0;i <=  (r2 - l2 - 1) / 2;i++) { //Calculating backwards 
		col[(i + 1) % 2][col[(i + 1) % 2].size() - 1] = i + 1;
		for (int j = col[(i + 1) % 2].size() - 2;j >= 0;j--) {
			col[(i + 1) % 2][j] = min(min(col[i % 2][j] + 1, col[(i + 1) % 2][j + 1] + 1), col[i % 2][j + 1] + (s1[l1 + j] != s2[r2 - 1 - i]));
		}
	}
	vector <int> right(col[(((r2 - l2 - 1) / 2) + 1) % 2].begin(), col[(((r2 - l2 - 1) / 2) + 1) % 2].end()); // result for the right half
	
	int bound = 0; //Dividing
	for (int i = 0;i < left.size();i++) {
		if (left[bound] + right[bound] > right[i] + left[i]) {
			bound = i;
		}
	}
	return Hirschberg(s1, s2, ans, l1, l1 + bound, l2, mid) + Hirschberg(s1, s2, ans, l1 + bound, r1, mid, r2);  
}

int main() {
	ifstream input("input1.txt", ifstream::in);
	freopen("output.txt", "w", stdout);
	string s1, s2;
	vector <operation> ans;
	getline(input, s1, '\0');
	input.close();
	input.open("input2.txt", ifstream::in);
	getline(input, s2, '\0');
	cout << Hirschberg(s1, s2, ans, 0, s1.length(), 0, s2.length()) << endl;
	int inc = 0;
	for (int i = 0;i < ans.size();i++) {
		if (ans[i].type == 0) {
			cout << "Delete " << ans[i].element << " from " << (ans[i].index + inc) << endl;
			inc--;
		}
		if (ans[i].type == 1) {
			cout << "Add " << ans[i].element << " after " << (ans[i].index + inc) << endl;
			inc++;
		}
		if (ans[i].type == 2) {
			cout << "Substitute " << s1[ans[i].index + inc] << " in " << (ans[i].index + inc) << " with " << ans[i].element << endl;
		}
	}
	return 0;
}
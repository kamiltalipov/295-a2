#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

vector <string> input; 

class BloomFilter {
private:
	int size;
	int hashQuantity;
	int hashBase[2];
    vector <bool> buffer;
	int preHash(string& s, int hashID);
    int* hash(string& s);
public:
	BloomFilter(double probability);
	bool check(string& s);
	void add(string& s);
};

int countWords() {
	return input.size();
}

BloomFilter::BloomFilter(double probability) {
	hashBase[0] = 31;
	hashBase[1] = 33;
	hashQuantity = (-1) * log(probability) / log((double)2);
	size = hashQuantity * countWords() / log((double)2);
	buffer.resize(size);
}

int BloomFilter::preHash(string& s, int hashID) {
   int res = s[0];
   for (int i = 1;i < s.length();i++) {
      res += s[i] * hashBase[hashID];
   }
   return res;
}

int* BloomFilter::hash(string& s) {
   int* res = new int[hashQuantity];
   for (int j=0;j<hashQuantity;j++) {
      *(res + j) = ((unsigned)(preHash(s, 0) + j * preHash(s, 1))) % size;
   }
   return res;
}

void BloomFilter::add(string& s) {
   int* sHash = hash(s);
   for (int j = 0;j < hashQuantity;j++) {
	   //cout << *(sHash + j) << " ";
	   buffer[*(sHash + j)] = 1;
   }
   delete sHash;
  // cout << endl;
}
bool BloomFilter::check(string& s) {
	int* sHash = hash(s);
    for (int j = 0;j < hashQuantity;j++) {
        if (!buffer[*(sHash + j)]) return false;
    }
	delete sHash;
    return true; 
}

bool checkFilter(string& s) {
	for (int i = 0;i < input.size();i++) {
		if (s == input[i]) {
			cout << "and it is." << endl;
			return 0;
		}
	}
	cout << "but actually isn't." << endl;
	return 1;
}


int main() {
	string s;
	char c;
	int FilterFail = 0;
	double probability;
	cin >> probability;
	freopen("WordBase.txt", "r", stdin);
	while (scanf("%c", &c) == 1) {
		if (isalnum(c)) s.push_back(c);
		else if (!s.empty()) {
			input.push_back(s);
			//cout << s << endl;
			s.clear();
		}
	}
	BloomFilter dict(probability);
	fclose(stdin);
	cin >> probability;
	freopen("WordBase.txt", "r", stdin);
	while (scanf("%c", &c) == 1) {
		if (isalnum(c)) s.push_back(c);
		else if (!s.empty()) {
			dict.add(s);
			//cout << s << endl;
			s.clear();
		}
	}
	fclose(stdin);
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	while (scanf("%c", &c) == 1) {
		if (isalnum(c)) s.push_back(c);
		else if (!s.empty()) {
			if (dict.check(s)) {
				cout << s << " is probably correct " << endl;
				FilterFail += checkFilter(s); 
			} else cout << s << " is incorrect" << endl;
			s.clear();
		}
	}
	cout << FilterFail << endl;
	return 0;
}
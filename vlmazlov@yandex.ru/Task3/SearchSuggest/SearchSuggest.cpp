#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <crtdbg.h>
#include <algorithm>
using namespace std;

template <class T>
class RMQ {
private:
	T maxx(T& val1, T& val2) {
		if (val1 > val2) return val1;
		else return val2;
	}
	pair<T, int> maxx(pair<T, int>& val1, pair<T, int>& val2) {
		if (val1.first > val2.first) return val1;
		else return val2;
	}
	vector <pair<T, int> > maxim;
	pair<T, int> getMax(int v, int left, int right, int coverLeft, int coverRight);
	void init(int v, int coverLeft, int coverRight, vector <T>& arr);
public:
	RMQ(vector <T>& arr);
	pair<T, int> getMax(int left, int right);
};

template <class T> RMQ<T>::RMQ(vector <T>& arr) {
	maxim.resize(4 * arr.size());
	init(0, 0, arr.size() - 1, arr);
}

template <class T> void RMQ<T>::init(int v, int coverLeft, int coverRight, vector <T>& arr) {
	if (coverLeft == coverRight) maxim[v] = make_pair(arr[coverLeft], coverLeft);
	else {
		int mid = (coverLeft + coverRight) / 2;
		init(2 * v + 1, coverLeft, mid, arr);
		init(2 * v + 2, mid  + 1, coverRight, arr);
		maxim[v] = maxx(maxim[2 * v + 1], maxim[2 * v + 2]);
	}
}


template <class T> pair<T, int> RMQ<T>::getMax(int v, int left, int right, int coverLeft, int coverRight) {
	if ((left == coverLeft) && (right == coverRight)) {
		return maxim[v];
	}
	int mid = (coverLeft + coverRight) / 2;
	if (mid >= right) {
		return getMax(2 * v + 1, left, right, coverLeft, mid);
	} else if (mid  < left) {
		return getMax(2 * v + 2, left, right, mid + 1, coverRight);
	} else {
		return maxx(getMax(2 * v + 1, left, mid, coverLeft, mid), getMax(2 * v + 2, mid + 1, right, mid + 1, coverRight));
	}
}

template <class T> pair<T, int> RMQ<T>::getMax(int left, int right) {
	return getMax(0, left, right, 0, maxim.size() / 4 - 1);
}

struct stringFreq {
	string str;
	int freq;
	stringFreq()
	{}
	stringFreq(string& s, int f) {
		str = s;
		freq = f;
	}
	bool operator < (const stringFreq& s) const  {
		return str < s.str; //Why this dosn't work? 
	}
	bool operator > (const stringFreq& s) const {
		return freq > s.freq;
	}
	bool pref(string& s) {
		if (s.length() > str.length()) return  0;
		return (str.substr(0, s.length()) == s);
	}
};
 
struct maxOnSeg {
	int val, left, right, pos;
	maxOnSeg(int v, int l, int r, int p) {
		val = v;
		left = l;
		right = r;
		pos = p;
	}
	bool operator < (const maxOnSeg& m) const  {
		return val < m.val;
	}
};

class Suggestor {
private:
	vector <stringFreq> base;
	RMQ <stringFreq>* rmq;
	int findUpperBound(string& prefix, int lowerBound);
public:
	Suggestor(vector <stringFreq>& input) {
		for (int i = 0;i < input.size();i++) {
			base.push_back(input[i]);
		}
		sort(base.begin(), base.end());
		rmq = new RMQ <stringFreq>(base);
	}
	~Suggestor() {
		delete rmq;
	}
	void Query(string& prefix, int quantity, vector <string>& res);
};
int Suggestor::findUpperBound(string &prefix, int lowerBound) {
	int left = lowerBound, right = base.size() - 1, mid;
	while (left < right) {
		mid = right - (right - left) / 2;
		if ((base[mid].str < prefix) || (base[mid].pref(prefix))) {
			left = mid;
		} else right = mid - 1;
	}
	if (!(base[right].pref(prefix))) return -1; // If right < left, it is also < base.size(), as it only decreases
	return left;//debug
}

void Suggestor::Query(string &prefix, int quantity, vector<string> &res) {
	priority_queue <maxOnSeg>* heap = new priority_queue <maxOnSeg>;
	int left = lower_bound(base.begin(), base.end(), stringFreq(prefix, 0)) - base.begin(), right = findUpperBound(prefix, left);
	if (right == -1) return;
	heap->push(maxOnSeg(rmq->getMax(left, right).first.freq, left, right, rmq->getMax(left, right).second));
	for (int i = 0;i < min(right - left + 1, quantity);i++) {
		maxOnSeg currMax = heap->top();
		heap->pop();
		pair <stringFreq, int> nextMax;
		if (currMax.left < currMax.pos) {
			nextMax = rmq->getMax(currMax.left, currMax.pos - 1);
			heap->push(maxOnSeg(nextMax.first.freq, currMax.left,
				currMax.pos - 1, nextMax.second));
		}
		if (currMax.right > currMax.pos) {
			nextMax = rmq->getMax(currMax.pos + 1, currMax.right);
			heap->push(maxOnSeg(nextMax.first.freq, currMax.pos + 1, currMax.right,
				nextMax.second));
		}
		res.push_back(base[currMax.pos].str);
	}
	delete heap;
}

int main() {
	freopen("input.txt", "r", stdin);
	vector <stringFreq> input;
	vector <string> res;
	string prefix;
	int n, quantity, f;
	cin >> n;
	for (int i = 0; i< n;i++) {
		cin >> prefix >> f;
		input.push_back(stringFreq(prefix, f));
	}
	cin >> prefix >> quantity;
	Suggestor suggestor(input);
	suggestor.Query(prefix, quantity, res);
	for (int i = 0;i < res.size();i++) {
		cout << res[i] << endl;
	}
	return 0;
}
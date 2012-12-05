#include <iostream>
#include <vector>
#include <string>
using namespace std;

class RMQ {
private:
	vector <int> minim;
	vector <int> toAdd;
	int getMin(int v, int left, int right, int coverLeft, int coverRight);
	void init(int v, int coverLeft, int coverRight, vector <int>& arr);
	void push(int v);
	void update(int v, int left, int right, int coverLeft, int coverRight, int x);
public:
	RMQ(vector <int>& arr);
	int getMin(int left, int right);
	void add(int Add, int left, int right);
};

RMQ::RMQ(vector <int>& arr) {
	minim.resize(4 * arr.size());
	toAdd.assign(4 * arr.size(), 0);
	init(0, 0, arr.size() - 1, arr);
}

void RMQ::init(int v, int coverLeft, int coverRight, vector <int>& arr) {
	if (coverLeft == coverRight) minim[v] = arr[coverLeft];
	else {
		int mid = (coverLeft + coverRight) / 2;
		init(2 * v + 1, coverLeft, mid, arr);
		init(2 * v + 2, mid  + 1, coverRight, arr);
		minim[v] = min(minim[2 * v + 1], minim[2 * v + 2]);
	}
}

void RMQ::push(int v) {
	toAdd[2 * v + 1] += toAdd[v];
	toAdd[2 * v + 2] += toAdd[v];
	minim[v] += toAdd[v];
	toAdd[v] = 0;
}

void RMQ::update(int v, int left, int right, int coverLeft, int coverRight, int Add) {
	push(v);
	if ((left == coverLeft) && (right == coverRight)) {
		toAdd[v] += Add;
		return;
	}
	int mid = (coverLeft + coverRight) / 2;
	if (mid >= right) {
		update(2 * v + 1, left, right, coverLeft, mid, Add);
	} else if (mid  < left) {
		update(2 * v + 2, left, right, mid + 1, coverRight, Add);
	} else {
		update(2 * v + 1, left, mid, coverLeft, mid, Add);
		update(2 * v + 2, mid, right, mid, coverRight, Add);
	}
	minim[v] = min(minim[2 * v + 1] + toAdd[2 * v + 1], minim[2 * v + 2] + toAdd[2 * v + 2]);
}

int RMQ::getMin(int v, int left, int right, int coverLeft, int coverRight) {
	push(v);
	if ((left == coverLeft) && (right == coverRight)) {
		return minim[v];
	}
	int mid = (coverLeft + coverRight) / 2;
	if (mid >= right) {
		return getMin(2 * v + 1, left, right, coverLeft, mid);
	} else if (mid  < left) {
		return getMin(2 * v + 2, left, right, mid + 1, coverRight);
	} else {
		return min(getMin(2 * v + 1, left, mid, coverLeft, mid), getMin(2 * v + 2, mid, right, mid, coverRight));
	}
}

int RMQ::getMin(int left, int right) {
	return getMin(0, left - 1, right - 1, 0, minim.size() / 4 - 1);
}

void RMQ::add(int Add, int left, int right) {
	update(0, left - 1, right - 1, 0, toAdd.size() / 4 - 1, Add); 
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n;
	cin >> n;
	vector <int> arr(n);
	for (int i = 0;i < n;i++) {
		cin >> arr[i];
	}
	RMQ* rmq = new RMQ(arr);
	string s;
	int l, r, x;
	while (cin >> s) {
		if (s == "add") {
			cin >> l >> r >> x;
			rmq->add(x, l, r);
		} else {
			cin >> l >> r;
			cout << "Minimum on [" << l << "; " << r << "] is " << rmq->getMin(l, r) << endl;
		}
	}                                                                                              
	return 0;
}

	
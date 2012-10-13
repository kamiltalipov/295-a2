#include < iostream >
#include < vector >
#include < cassert >

using namespace std;

class heap {
	vector<int> a;
	int parent(int i) const { return i>>1; }
	int left(int i) const { return i<<1; }
	int right(int i) const { return i<<1 | 1; }
	void heapify(int);
	void build();

public:
	heap();
	heap(const vector<int>&);
	~heap();
	int size() const { return a.size()-1; }
	int maximum() const;
	int extract_max();
	void insert(int);
	static void heapsort(vector<int>&);
};

heap::heap()
{
	a.resize(1);
}

heap::heap(const vector<int>& arr)
{
	a.resize(1);
	a.insert(a.end(),arr.begin(),arr.end());
	build();
}

heap::~heap()
{
	a.clear();
}

int heap::maximum() const
{
	assert(size()>0);
	return a[1];
}

int heap::extract_max()
{
	assert(size()>0);
	int max = a[1];

	a[1] = a[size()];
	a.pop_back();
	heapify(1);
	return max;
}

void heap::insert(int key)
{
	a.push_back(key);
	for (int i = size(); i>1 && a[parent(i)]<a[i]; i = parent(i)) swap(a[i],a[parent(i)]);
}

void heap::heapify(int i)
{
	int l = left(i);
	int r = right(i);

	int largest = i;
	if (l<=size() && a[l]>a[i]) largest = l;
	if (r<=size() && a[r]>a[largest]) largest = r;

	if (largest != i) {
		swap(a[i],a[largest]);
		heapify(largest);
	}
}

void heap::build()
{
	for (int i = size()>>1; i > 0; --i) heapify(i);
}

void heap::heapsort(vector<int>& v)
{
	heap h(v);

	for (int i = v.size()-1; i >= 0; --i) v[i] = h.extract_max();
}

void check_heapsort()
{
	int n;
	vector<int> v;

	cin >> n;
	v.resize(n);
	for (int i = 0; i < n; ++i) cin >> v[i];

	heap::heapsort(v);
	for (int i = 0; i < n; ++i) cout << v[i] << ' ';
}

int main()
{
	check_heapsort();

	_CrtDumpMemoryLeaks();
	return 0;
}
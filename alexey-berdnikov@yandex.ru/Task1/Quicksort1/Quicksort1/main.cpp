#include < iostream >
#include < vector >

#include < cassert >

using namespace std;

typedef pair<int*, int*> ptr_pair;

int* partition(int* left, int* right)
{
	assert(left<right);
	--right;
	int x = *right;
	int* i = left;
	for (int* j = left; j != right; ++j)
		if (*j <= x) {
			swap(*i,*j);
			++i;
		}
	swap(*i,*right);
	return i;
}

void quicksort(int* left, int* right)
{
	assert(left<=right);
	if (right-left < 2) return;

	int* q = partition(left,right);
	quicksort(left,q);
	quicksort(q+1,right);
}

void quicksort_nonrecursive(int* left, int* right)
{
	assert(left<=right);
	vector<ptr_pair> stack(1,(make_pair(left,right)));
	while (!stack.empty()) {
		ptr_pair p = stack.back();
		stack.pop_back();
		int* left = p.first;
		int* right = p.second;
		assert(left<=right);
		if (right-left < 2) continue;

		int* q = partition(left,right);
		stack.push_back(make_pair(left,q));
		stack.push_back(make_pair(q+1,right));
	}
}

void check_sort(int* arr, int size)
{
	assert(size>=0);

	for (int i = 1; i < size; ++i) assert(arr[i-1]<=arr[i]);
}

void nth_element(int* left, int* nth, int* right)
{
	assert(left<=nth&&nth<right);
	int* q = partition(left,right);

	if (q == nth) return;
	if (q < nth)
		nth_element(q+1,nth,right);
	else
		nth_element(left,nth,q);
}

void check_quicksort()
{
	int n, *a;

	cin >> n;
	assert(n>=0);
	a = new int [n];
	for (int i = 0; i < n; ++i) cin >> a[i];

	quicksort(a,a+n);
	check_sort(a,n);
	for (int i = 0; i < n; ++i) cout << a[i] << ' ';

	delete[] a;
}

void check_quicksort_nonrecursive()
{
	int n, *a;

	cin >> n;
	assert(n>=0);
	a = new int [n];
	for (int i = 0; i < n; ++i) cin >> a[i];

	quicksort_nonrecursive(a,a+n);
	check_sort(a,n);
	for (int i = 0; i < n; ++i) cout << a[i] << ' ';

	delete[] a;
}

void check_nth_element()
{
	int n, k, *a;

	cin >> n >> k;
	--k;
	assert(0<=k&&k<n);
	a = new int [n];
	for (int i = 0; i < n; ++i) cin >> a[i];

	nth_element(a,a+k,a+n);
	for (int i = 0; i < n; ++i) cout << a[i] << ' ';

	delete[] a;
}

int main()
{
	check_quicksort();
//	check_quicksort_nonrecursive();
//	check_nth_element();

	_CrtDumpMemoryLeaks();
	return 0;
}
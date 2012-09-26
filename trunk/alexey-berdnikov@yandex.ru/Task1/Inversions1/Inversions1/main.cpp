#include < cassert >
#include < iostream >

using namespace std;

int merge(int* l, int* m, int* r, int* buf)
{
	int inversions = 0;
	int* i = l;
	int* j = m;

	for (int* k = buf; i<m || j<r; ++k)
		if (j<r && (i==m||*j<*i)) {
			*k = *j;
			++j;
			inversions += m-i;
		}
		else {
			*k = *i;
			++i;
		}
	for (int*  i = l, *k = buf; i < r; ++i, ++k) *i = *k;

	return inversions;
}

int merge_sort(int* l, int* r, int* buf)
{
	if (r-l < 2) return 0;

	int a = r-l;
	int* m = l+(r-l)/2;

	int inversions = merge_sort(l,m,buf)+merge_sort(m,r,buf);
	inversions += merge(l,m,r,buf);

	return inversions;
}

int bubble_sort(int* a, int size)
{
	int inversions = 0;
	for (int i = 0; i < size; ++i)
		for (int j = size-1; j > i; --j)
			if (a[j-1] > a[j]) {
				swap(a[j-1],a[j]);
				++inversions;
			}
	return inversions;
}

int inversions(int* a, int size)
{
	int* buf = new int[size];
	int* b = new int[size];

	for (int i = 0; i < size; ++i)
		b[i] = a[i];
	int result1 = merge_sort(a,a+size,buf);
	int result2 = bubble_sort(b,size);
	assert(result1==result2);

	delete[] buf;
	delete[] b;

	return result1;
}

int main()
{
	int n, *a;

	cin >> n;
	a = new int [n];
	for (int i = 0; i < n; ++i) cin >> a[i];
	cout << inversions(a,n);

	delete[] a;

	_CrtDumpMemoryLeaks();

	return 0;
}
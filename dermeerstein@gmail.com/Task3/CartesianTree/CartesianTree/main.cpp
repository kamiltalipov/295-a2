#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

template <class T>
class CartesianTree
{
private:
	class CTNode
	{
	public:
		CTNode* left;
		CTNode* right;
		T x;
		int y;
		int size;
		
		CTNode() {}
		CTNode(T& value, CTNode* L, CTNode* R);
	};
	CTNode* root;

	void split(CTNode* root, T& k, CTNode* &L, CTNode* &R);
	CTNode* merge(CTNode* L, CTNode* R);
	int sizeOf(CTNode* root);
public:
	CartesianTree()
	{
		root = NULL;
	}
	CTNode* Find(T& value);
	void Insert(T value);
	void Erase(T& value);
	T Nth_element(int n);
};

template <class T>
CartesianTree<T>::CTNode::CTNode(T& value, CTNode* L, CTNode* R)
{
	this->left = L;
	this->right = R;
	this->x = value;
	this->y = rand();
	this->size = 1;
}

template <class T>
void CartesianTree<T>::split(CTNode* root, T& key, CTNode* &L, CTNode* &R)
{
	if (root == NULL)
		L = R = NULL;
	else if (key < root->x)
	{
		R = root;
		split(root->left, key, L, R->left);
		R->size = sizeOf(R->left) + sizeOf(R->right) + 1;
	}
	else
	{
		L = root;
		split(root->right, key, L->right, R);
		L->size = sizeOf(L->left) + sizeOf(L->right) + 1;
	}
}

template <class T>
typename CartesianTree<T>::CTNode* CartesianTree<T>::merge(CTNode* L, CTNode* R)
{
	if (L == NULL)
		return R;
	else if (R == NULL)
		return L;
	else
	{
		CTNode* result;
		if (L->y >= R->y)
		{
			result = L;
			result->right = merge(L->right, R);
		}
		else
		{
			result = R;
			result->left = merge(L, R->left);
		}
		
		result->size = sizeOf(result->left) + sizeOf(result->right) + 1;
		return result;
	}
}

template <class T>
int CartesianTree<T>::sizeOf(CTNode* root)
{
	return (root == NULL ? 0 : root->size);
}

template <class T>
typename CartesianTree<T>::CTNode* CartesianTree<T>::Find(T& value)
{
	CTNode* current = root;
	while (current != NULL)
	{
		if (current->x < value)
			current = current->right;
		else if (value < current->x)
			current = current->left;
		else
			return current;
	}
	return NULL;
}

template <class T>
void CartesianTree<T>::Insert(T value)
{
	CTNode* new_node = Find(value);
	if (new_node == NULL)
	{
		CTNode* L;
		CTNode* R;
		new_node = new CTNode(value, NULL, NULL);
		split(root, value, L, R);
		root = merge(merge(L, new_node), R);
	}
}

template <class T>
void CartesianTree<T>::Erase(T& value)
{
	if (Find(value))
	{
		CTNode* current = root;
		while (current != NULL && !(current->x == value))
		{
			current->size -= 1;
			if (current->x < value)
				current = current->right;
			else
				current = current->left;
		}
		*current = *merge(current->left, current->right);
	}
}

template <class T>
T CartesianTree<T>::Nth_element(int n)
{
	CTNode* current = root;
	while (current != NULL)
	{
		if (sizeOf(current->left) == n)
			return current->x;
		else if (sizeOf(current->left) < n)
		{
			current = current->right;
			n -= sizeOf(current->left);
		}
		else
			current = current->left;
	}
}

int main()
{
	srand(time(NULL));
	CartesianTree<int> CT;
	int n, t;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> t;
		CT.Insert(t);
	}
	cout << CT.Nth_element(3);
	int a = 2;
	CT.Erase(a);
	CT.Erase(a);
	cout << CT.Nth_element(3);
	CT.Insert(a);
	cout << CT.Nth_element(3);
	return 0;
}
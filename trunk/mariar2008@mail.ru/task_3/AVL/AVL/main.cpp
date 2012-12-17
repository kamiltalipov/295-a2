#include<cstdio>
#include<iostream>
#include<string>

using namespace std;
template<class T>
class AVL{
private:
	struct Node{
		T Key;
		int h;
		Node* left;
		Node* right;
		Node* parent;
	};
	Node* root;
	void update(Node* cur){
		if (cur == NULL)
			return;
		int max = 0;
		if (cur->left != NULL){
			(cur->left)->parent = cur;
			max = (cur->left)->h;
		}
		if (cur->right != NULL){
			(cur->right)->parent = cur;
			if (max < (cur->right)->h)
				max = (cur->right)->h;
		}
		cur->h = max + 1;
	}
	int bal(Node* cur){
		int hL = 0;
		if (cur->left != NULL)
			hL = (cur->left)->h;
		int hR = 0;
		if (cur->right != NULL)
			hR = (cur->right)->h;
		return hR - hL;
	}
	Node* TurnRight(Node* cur){
		Node* node = cur->left;
		cur->left = node->right;
		node->right = cur;
		update(cur);
		update(node);
		return node;
	}
	Node* TurnLeft(Node* cur){
		Node* node = cur->right;
		cur->right = node->left;
		node->left = cur;
		update(cur);
		update(node);
		return node;
	}
	Node* balance(Node* cur){
		update(cur);
		if (bal(cur) == 2){
			if (bal(cur->right) == -1)
				cur->right = TurnRight(cur->right);
			return TurnLeft(cur);
		}
		else
			if (bal(cur) == -2){
				if (bal(cur->left) == 1)
					cur->left = TurnLeft(cur->left);
				return TurnRight(cur);
			}
		return cur;
	}

public:
	AVL(){root = NULL;}
	~AVL(){erase(root);}
	void erase(Node* root){
		if (root == NULL)
			return;
		erase(root->left);
		erase(root->right);
		delete root;
	}
	Node* Find(T value, Node* cur){
		if (cur == NULL)
			return NULL;
		if (value == cur->Key)
			return cur;
		if (value < cur->Key)
			Find(value, cur->left);
		else
			Find(value, cur->right);
	}
	Node* Find(T value){
		return Find(value, root);
	}
	Node* Add(Node* cur, Node*& root){
		if (root == NULL)
			return cur;
		if (cur->Key < root->Key)
			root->left = Add(cur, root->left);
		else
			root->right = Add(cur, root->right);
		return balance(root);
	}
	void Add(T value){
		if (Find(value) != NULL)
			return;
		Node* cur = new Node;
		cur->Key = value;
		cur->h = 1;
		cur->left = cur->right = cur->parent = 0;
		root = Add(cur, root);
	}
	Node* Deletemin(Node* root){
		if (root->left == NULL)
			return root->right;
		root->left = Deletemin(root->left);
		return balance(root);
	}
	Node* Delete(T value, Node* root){
		if (root == NULL)
			return NULL;
		if (value < root->Key)
			root->left = Delete(value, root->left);
		else
			if (value > root->Key)
				root->right = Delete(value, root->right);
			else{
				Node* l = root->left;
				Node* r = root->right;
				Node* p = root->parent;
				delete root;
				if (r == NULL)
					return l;
				Node* min = r;
				while (r->left != NULL)
					min = r->left;
				min->right = Deletemin(r);
				min->left = l;
				min->parent = p;
				return balance(min);
			}
		return balance(root);
	}
	void Delete(T value){
		Node* cur = Find(value);
		if (cur != NULL)
			root = Delete(value, root);
	}
	Node* Next(Node* cur){
		if (cur->right != NULL){
			Node* node = cur->right;
			while (node->left != NULL)
				node = node->left;
			return node;
		}
		else{
			Node* node = cur;
			while (node->parent != NULL && node == (node->parent)->right)
				node = node->parent;
			if (node->parent == NULL)
				return NULL;
			else
				return node->parent;
		}
	}
	T Next(T value){
		Node* cur = Find(value);
		Node* ans;
		if (cur != NULL)
			ans = Next(cur);
		else
			ans = NULL;
		if (ans == NULL)
			return 0;
		else
			return ans->Key;
	}
	Node* Prev(Node* cur){
		if (cur->left != NULL){
			Node* node = cur->left;
			while (node->right != NULL)
				node = node->right;
			return node;
		}
		else{
			Node* node = cur;
			while (node->parent != NULL && node == (node->parent)->left)
				node = node->parent;
			if (node->parent == NULL)
				return NULL;
			else
				return node->parent;
		}
	}
	T Prev(T value){
		Node* cur = Find(value);
		Node* ans;
		if (cur != NULL)
			ans = Prev(cur);
		else
			ans = NULL;
		if (ans == NULL)
			return 0;
		else
			return ans->Key;
	}
};

int main( void ){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	AVL<int> Tree;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++){
		int x;
		string s;
		cin >> s >> x;
		if (s == "Add")
			Tree.Add(x);
		if (s == "Delete")
			Tree.Delete(x);
		if (s == "Next")
			cout << Tree.Next(x) << endl;
		if (s == "Prev")
			cout << Tree.Prev(x) << endl;
	}
	return 0;
}
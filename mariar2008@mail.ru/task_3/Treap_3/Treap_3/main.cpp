#include<cstdio>
#include<iostream>
#include<vector>
#include<algorithm>
#include<ctime>
#include<string>

using namespace std;
struct my{
	int num, num_p, num_l, num_r;
};
template<class T>
class Treap{
	private:
	struct Node{
		T KeyOne;
		int KeyTwo;
		Node* parent;
		Node* left;
		Node* right;
		int num;
	};
	Node* root;
	void split(T key, Node* root, Node*& L, Node*& R){
		if (root == NULL){
			L = NULL; R = NULL;
			return;
		}
		if (root->KeyOne >= key){
			split(key, root->left, L, root->left);
			if (L != NULL) L->parent = NULL;
			R = root;
		}
		else{ 
			split(key, root->right, root->right, R);
			if (R != NULL) R->parent = NULL;
			L = root;
		}
		root->num = 1;
		if (root->left != NULL){
			(root->left)->parent = root;
			root->num += (root->left)->num; 
		}
		if (root->right != NULL){
			(root->right)->parent = root;
			root->num += (root->right)->num;
		}

	}
	Node* merge(Node* L, Node* R){
		if (L == NULL)
			return R;
		if (R == NULL)
			return L;
		if (L->KeyTwo > R->KeyTwo){
			L->right = merge(L->right, R);
			L->num = 1;
			if (L->right != NULL){
				(L->right)->parent = L;
				L->num += (L->right)->num;
			}
			if (L->left != NULL)
				L->num += (L->left)->num;
			return L;
		}
		else{
			R->left = merge(L, R->left);
			R->num = 1;
			if (R->left != NULL){
				(R->left)->parent = R;
				R->num += (R->left)->num;
			}
			if (R->right != NULL)
				R->num += (R->right)->num;
			return R;
		}
	}
public:
	Treap(){root = NULL;}
	Treap(Node* node){root = node;}
	~Treap(){erase(root);}
	void erase(Node* root){
		if (root == NULL)
			return;
		erase(root->left);
		erase(root->right);
		delete root;
	}
	void Add(T valueOne, int valueTwo, Node*& node){
		if (Find(valueOne, node) != NULL)
			return;
		Node* curNode = new Node;
		curNode->parent = curNode->left = curNode->right = NULL;
		curNode->KeyOne = valueOne;
		curNode->KeyTwo = valueTwo;
		curNode->num = 1;
		Node* L; 
		split(valueOne, node, L, node);
		L = merge(L, curNode);
		node = merge(L, node);
	}
	void Add(T value){
		srand(time(NULL));
		Add(value, rand(), root);
	}
	void Delete(T value){
		if (Find(value, root) == NULL)
			return;
		Node* L;
		Node* R;
		Node* cur;
		split(value, root, L, R);
		split(value + 1, R, cur, R);
		root = merge(L, R);
	}

	Node* Find(T value, Node* root){
		if (root == NULL)
			return NULL;
		if (value == root->KeyOne)
			return root;
		if (value < root->KeyOne)
			Find(value, root->left);
		else
			Find(value, root->right);
	}
	Node* Find(T value){
		return Find(value, root);
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
		if (cur != NULL){
			Node* curTwo = Next(cur);
			if (curTwo != NULL)
				return curTwo->KeyOne;
		}
		return 0;
	}
	Node* Prev(Node* cur){
		if (left != NULL){
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
		if (cur != NULL){
			Node* curTwo = Prev(cur);
			if (curTwo != NULL)
				return curTwo->KeyOne;
		}
		return 0;
	}
	T Kth(int val, Node* node){
		if (node == NULL || val > node->num)
			return 0;
		int l, r;
		if (node->left == NULL) l = 0;
		else l = (node->left)->num;
		if (node->right == NULL) r = 0;
		else r = (node->right)->num;
		if (val == l + 1)
			return node->KeyOne;
		if (val <= l)
			return Kth(val, node->left);
		if (val > l)
			return Kth(val - l - 1, node->right);
	}
	T Kth(int val){
		return Kth(val, root);
	}

	/*void WalkTree(vector<my>& ans, Node* node){
		if (node == NULL)
			return; 
		int l, r, p;
		if (node->left == NULL) l = 0;
		else l = (node->left)->num;
		if (node->right == NULL) r = 0;
		else r = (node->right)->num;
		if (node->parent == NULL) p = 0;
		else p = (node->parent)->num;
		my w;
		w.num = node->num; w.num_p = p; w.num_l = l; w.num_r = r;
		
		ans.push_back(w);
		WalkTree(ans, node->left);
		WalkTree(ans, node->right);
	}
	void WalkTree(vector<my>& ans){
		WalkTree(ans, root);
	}*/
};
bool compare(my x, my y){
	if (x.num < y.num) return true;
	else return false;
}
int main(void){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w", stdout);
	Treap<int> tree;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++){
		int x;
		string s;
		cin >> s >> x;
		if (s == "Add")
			tree.Add(x);
		if (s == "Delete")
			tree.Delete(x);
		if (s == "Next")
			cout << tree.Next(x) << endl;
		if (s == "Prev")
			cout << tree.Prev(x) << endl;
		if (s == "K-th")
			cout << tree.Kth(x) << endl;
	}
	/*vector<my> ans;
	tree.WalkTree(ans);
	sort(ans.begin(), ans.end(), compare);
	cout << "YES" << endl;
	for (int i = 0; i < ans.size(); i++)
		cout << ans[i].num_p << " " << ans[i].num_l << " " << ans[i].num_r << endl; */
	return 0;
}
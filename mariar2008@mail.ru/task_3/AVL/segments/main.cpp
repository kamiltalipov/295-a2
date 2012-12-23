#include<cstdio>
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<limits>

using namespace std;
const static double eps = 0.00001;
struct point{
	double x, y;
	point(){}
	point(double x, double y):x(x), y(y){}
	bool operator==(const point cur){
		if (x == cur.x && y == cur.y)
			return true;
		else
			return false;
	}
};
struct segment{
	point pointOne, pointTwo;
	segment(){};
	segment(point pointOne, point pointTwo): pointOne(pointOne), pointTwo(pointTwo){}
	double gety(double x)const{
		if ((pointOne.x - pointTwo.x) <= eps)
			return pointOne.x;
		else
			return pointOne.y + (pointTwo.y - pointOne.y)*(x - pointOne.x)/(pointTwo.x - pointOne.x); 
	}
	bool operator==(const segment cur){
		if (pointOne == cur.pointOne && pointTwo == cur.pointTwo)
			return true;
		else
			return false;
	}
	bool operator<(const segment& cur){
		double x = max(min(pointOne.x, pointTwo.x), min(cur.pointOne.x, cur.pointTwo.x));
		return gety(x) < (cur.gety(x) - eps);
	}
	bool operator>(const segment& cur){
		double x = max(min(pointOne.x, pointTwo.x), min(cur.pointOne.x, cur.pointTwo.x));
		return (gety(x) - eps) > cur.gety(x);
	}
};
struct point_event{
	double x;
	int type, ind;
	point_event(double x, int type, int ind):x(x), type(type), ind(ind){
	}
	bool operator< (const point_event & cur){
		if (abs(x - cur.x) > eps)
			return x < cur.x;
		else
			return cur.type < type;
	}
};

template<class T>
class AVL{
private:
	struct Node{
		T Key;
		int h;
		Node* left;
		Node* right;
		Node* parent;
		Node(){};
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
			if (node == cur)
				return NULL;
			else
				return node;
		}
	}
	T Next(T value){
		double val = numeric_limits<double>::max();
		Node* cur = Find(value);
		Node* ans;
		bool add = false;
		if (cur != NULL)
			ans = Next(cur);
		else{
			Add(value);
			cur = Find(value);
			ans = Next(cur);
			add = true;
		}
		segment result;
		if (ans == NULL)
			result = segment(point(val, val), point(val, val));
		else
			result = ans->Key;
		if (add) Delete(value);
		return result;
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
			if (node == cur)
				return NULL;
			else
				return node;
		}
	}
	T Prev(T value){
		double val = numeric_limits<double>::max();
		Node* cur = Find(value);
		Node* ans;
		bool add = false;
		if (cur != NULL)
			ans = Prev(cur);
		else{
			Add(value);
			cur = Find(value);
			ans = Prev(cur);
			add = true;
		}
		segment result;
		if (ans == NULL)
			result = segment(point(val, val), point(val, val));
		else
			result = ans->Key;
		if (add) Delete(value);
		return result;
	}
};


bool in(segment& cur, double x, double y){
	double len1 = sqrt((cur.pointOne.x - x)*(cur.pointOne.x - x) + (cur.pointOne.y - y)*(cur.pointOne.y - y));
	double len2 = sqrt((cur.pointTwo.x - x)*(cur.pointTwo.x - x) + (cur.pointTwo.y - y)*(cur.pointTwo.y - y));
	double len = sqrt((cur.pointTwo.x - cur.pointOne.x)*(cur.pointTwo.x - cur.pointOne.x) + (cur.pointTwo.y - cur.pointOne.y)*(cur.pointTwo.y - cur.pointOne.y));
	return abs(len - len1 - len2) < eps;

}

bool crossing(segment& one, segment& two){
	double a1, b1, c1, a2, b2, c2, d;
	a1 = one.pointOne.y - one.pointTwo.y;
	b1 = one.pointTwo.x - one.pointOne.x;
	c1 = -a1*one.pointOne.x - b1*one.pointOne.y;
	d = sqrt(a1*a1 + b1*b1);
	a1 = a1/d;
	b1 = b1/d;
	c1 = c1/d;

	a2 = two.pointOne.y - two.pointTwo.y;
	b2 = two.pointTwo.x - two.pointOne.x;
	c2 = -a2*two.pointOne.x - b2*two.pointOne.y;
	d = sqrt(a2*a2 + b2*b2);
	a2 = a2/d;
	b2 = b2/d;
	c2 = c2/d;
	double x, y;
	if (abs(a1*b2 - a2*b1) < eps) 
		return false;
	else{
		x = -(c1*b2 - c2*b1)/(a1*b2 - a2*b1);
		y = -(a1*c2 - a2*c1)/(a1*b2 - a2*b1);
		if (in(one, x, y) && in(two, x, y))
			return true;
		else
			return false;
	}
}

int main( void ){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	AVL<segment> Tree;
	int n;
	cin >> n;
	vector<segment> seg;
	for (int i = 0; i < n; i++){
		point pointOne, pointTwo;
		cin >> pointOne.x >> pointOne.y >> pointTwo.x >> pointTwo.y;
		seg.push_back(segment(pointOne, pointTwo));
	}

	vector<point_event> e;
	for (int i = 0; i < n; i++){
		e.push_back(point_event(min(seg[i].pointOne.x, seg[i].pointTwo.x), 1, i));
		e.push_back(point_event(max(seg[i].pointOne.x, seg[i].pointTwo.x), -1, i));
	}
	sort(e.begin(), e.end());
	double val = numeric_limits<double>::max();
	segment zero(point(val, val), point(val, val));
	for (int i = 0; i < e.size(); i++){
		int ind = e[i].ind;
		if (e[i].type == 1){
			Tree.Add(seg[ind]);
			segment cur = Tree.Next(seg[ind]);
			if (!(cur == zero) && crossing(cur, seg[ind])){
				cout << "Еть пересечение";
				return 0;
			}
			cur = Tree.Prev(seg[ind]);
			if (!(cur == zero) && crossing(cur, seg[ind])){
				cout << "Есть пересечиние";
				return 0;
			}
			
		}
		else{
			segment cur = Tree.Next(seg[ind]);
			if (!(cur == zero) && crossing(cur, seg[ind])){
				cout << "Еть пересечение";
				return 0;
			}
			cur = Tree.Prev(seg[ind]);
			if (!(cur == zero) && crossing(cur, seg[ind])){
				cout << "Есть пересечиние";
				return 0;
			}
			Tree.Delete(seg[ind]);
		}
	}
	cout << "Нет пересечений";
	return 0;
}
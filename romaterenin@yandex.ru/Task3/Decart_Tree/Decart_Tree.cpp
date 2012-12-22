#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;
class Treap{
public:
    int key;
    int priority;
    Treap* left;
    Treap* right;
	Treap () {
	}
	~Treap () {
		delete left;
		delete right;
	}
	Treap (int _key, int _priority, Treap* _left, Treap* _right) {
		key=_key;
		priority=rand();
		right=_right;
		left=_left;
	}
	Treap (int _key){
		key=_key;
		priority=rand();
		left=NULL;
		right=NULL;
	}
	int size (Treap* tree){
		if(tree == NULL)
			return 0;
		else
			return 1 + size(tree->right) + size(tree->left);
	}
	bool Find(int x, const Treap* This) const {
		if(This==NULL)
			return false;
		if(This->key == x)
			return true;
		if(This->key < x) 
			return Find(x, This->right);
		else 
			return Find(x, This->left);
	}
	Treap* Merge(Treap* Left_treap, Treap* Right_treap){
		if (Left_treap == NULL) 
			return Right_treap;
		if (Right_treap == NULL) 
			return Left_treap;
		if (Left_treap->priority > Right_treap->priority){
			Treap* newRight = Merge(Left_treap->right, Right_treap);
			return new Treap(Left_treap->key, Left_treap->priority, Left_treap->left, newRight);
		}
		else{
			Treap* newLeft = Merge(Left_treap, Right_treap->left);
			return new Treap (Right_treap->key, Right_treap->priority, newLeft, Right_treap->right);
		}
	}
	void Split(int x, Treap* This, Treap* &Left, Treap* &Right){
		Treap* newTree = NULL;
		if (This == NULL) {
			Left = Right = NULL;
			return;
		}
		if (This->key <= x){
			if (This->right == NULL)
				Right = NULL;
			else
				Split(x, This->right, newTree, Right);
			Left = new Treap (This->key, This->priority, This->left, newTree);
		}
		else{
			if (This->left == NULL)
				Left = NULL;
			else
				Split(x,This->left, Left, newTree);
			Right = new Treap (This->key, This->priority, newTree, This->right);
		}
	}
	Treap* Add(int add, Treap* This){
		if(This==0)
			return new Treap(add);
		Treap* Left;
		Treap* Right;
		Split(add, This, Left, Right);
		Treap* middle;
		middle= new Treap(add);
		Treap* x=Merge (Left, middle);
		Treap* y=Merge (x, Right);
		return y;
	} 
	Treap* Remove(int x, Treap* This){
		Treap *Left,*middle, *Right, *Right2;
		Split(x-1, This, Left, Right);
		Split(x, Right, middle, Right2);
		delete middle;
		return Merge(Left, Right2);
	}

	int next(int x,Treap *This){
        int answer=0;
		Treap *Left, *Right;
        Split(x, This, Left, Right);
        if (Right != NULL){
                Treap *middle = Right;
				while ( middle->left != NULL)
                        middle = middle->left;
                answer = middle->key;
        }
        else
                answer = -1;
 
        This = Merge(Left, Right);
        return answer;
	}
};
int main(){
	freopen("in.txt", "r", stdin);
	int zapros,element;
	string s;
	cin>>zapros;
	Treap* root=NULL;
	for(int i=0;i<zapros;i++){
		cin>>s;
		cin>>element;
		if(s=="insert")
			root=root->Add(element,root);
		if(s=="find"){
			if(root->Find(element, root))
				cout<<"Yes";
			else
				cout<<"No";
			cout<<endl;
		}
		if(s=="remove")
			root=root->Remove(element,root);
	}
	return 0;
}
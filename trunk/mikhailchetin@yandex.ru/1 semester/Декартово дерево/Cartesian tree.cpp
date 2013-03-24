#include <cstdlib>
#include <iostream>
 
using namespace std;
 
struct treap
{
        int key;
		int priority;
		int size;
        treap *left;
		treap *right;
        treap (int _key)
		{
			size=1;
			key=_key;
            priority=rand();
            left=NULL;
            right=NULL;
        };
		treap(int _key,int _priority, treap* _left, treap* _right)
		{
			key=_key;
			left=_left;
			right=_right;
			priority=_priority;
			size=1;
		};
		~treap()
		{
			delete left;
			delete right;
		}
};
typedef treap* ptreap;

int size(ptreap p)
{
	return p==NULL ? 0 : p->size;
}

void recalc(ptreap &p)
{
    if(p!=NULL) p->size=size(p->left)+size(p->right)+1;
	else
		return;
}

void split(int key, ptreap current, ptreap& left, ptreap& right)
{
        if (current == NULL)
        {
                left = right = NULL;
                return void();
        }
        if (key < current->key)
		{
			split(key, current->left, left, current->left);
			recalc(current);
			right = current;
		}
        else
		{
			split(key, current->right, current->right, right);
			recalc(current);
			left = current;
		}
}

ptreap merge(ptreap left, ptreap right)
{
        if (left == NULL)
                return right;
        if (right == NULL)
                return left;
        if (left->priority < right->priority)
        {
                left->right = merge(left->right, right);
				recalc(left);
                return left;
        }
        else
        {
                right->left = merge(left, right->left);
				recalc(right);
                return right;
        }
}


void insert(ptreap neo,ptreap &root)
{
        ptreap left=NULL, right=NULL, place=NULL;
        split(neo->key-1, root, left, right);
        split(neo->key, right, place, right);
        if (place == NULL)
                place = neo;
        place = merge(left, place);
        root = merge(place, right);
}
 
 
int next(int i,ptreap &root)
{
        ptreap left=NULL, right=NULL;
        int result = 0;
       
        split(i, root, left, right);
 
        if (right != NULL)
        {
                ptreap temp = right;
                while (temp->left != NULL)
                        temp = temp->left;
                result = temp->key;
        }
        else
                result = -1;
 
        root = merge(left, right);
        return result;
}
int KthElement(ptreap p, int K)
{
    ptreap cur = p;
    while (cur != NULL)
    {
        int sizeLeft = size(cur->left);

        if (sizeLeft == K-1)
            return cur->key;

        if(sizeLeft>=K) 
			cur=cur->left;
		else cur=cur->right;

        if (sizeLeft < K)
            K-=sizeLeft + 1;
    }
}

int main()
{
	int m,a,k;
	int q;
	cin>>m;
	ptreap root=NULL;
	ptreap neo;
	srand(1000);
	for(int i=1;i<=m;i++)
	{
		cin>>q;    //q==1 - добавить элемент в дерево
				   //q==2 - вывести К-й элемент(К-ю порядковую статистику)
				   //q==3 - вывести все дерево в отсортированном порядке
				   //q==0 - вывести элемент, следующий за данным

		if(q==1)
		{
			cin>>a;
			neo=new treap(a);
			insert(neo,root);
		}
		else if(q==2)
		{
			cin>>k;
			cout<<KthElement(root,k)<<endl;
		}
		else if(q==3)
			for(int i=1;i<=root->size;i++) cout<<KthElement(root,i)<<' ';
		else
		{
			cin>>a;
			cout<<next(a,root);
		}
		
	}
	//cin>>m;
	return 0;
}
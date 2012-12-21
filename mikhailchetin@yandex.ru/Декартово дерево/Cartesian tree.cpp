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
void split(int x,ptreap current, ptreap &L, ptreap &R)
{
	if (current == NULL)
    {
                L = R = NULL;
                return void();
    }
    ptreap newTree = NULL;
    if (current->key <= x)
    {
        if (current->right == NULL)
            R = NULL;
        else
            split(x,current->right, newTree, R);
        L = new treap(current->key, current->priority, current->left, newTree);
        recalc(L);
    }
    else
    {
        if (current->left == NULL)
            L = NULL;
        else
            split(x,current->left,  L, newTree);
        R = new treap(current->key, current->priority, newTree, current->right);
        recalc(R);
    }
}

ptreap merge(ptreap L, ptreap R)
{
    if (L == NULL) return R;
    if (R == NULL) return L;

    ptreap answer;
    if (L->priority > R->priority)
    {
        ptreap newR = merge(L->right, R);
        answer = new treap(L->key, L->priority, L->left, newR);
    }
    else
    {
        ptreap newL = merge(L, R->left);
        answer = new treap(R->key, R->priority, newL, R->right);
    }

    recalc(answer); // пересчёт!
    return answer;
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
        ptreap left, right;
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
				   //q==0 - вывести все дерево в отсортированном порядке

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
		else
			for(int i=1;i<=root->size;i++) cout<<KthElement(root,i)<<' ';
	}
	//cin>>m;
	return 0;
}
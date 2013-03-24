#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

struct node
{
    int key;
    int height;
    node* left;
    node* right;
    node(int k) { key = k; left = right = 0; height = 1;}
	~node()
	{
		delete left;
		delete right;
	}
};

int height(node* p)
{
    return p?p->height:0;
}

int bfactor(node* p)
{
    return height(p->right)-height(p->left);
}

void fixheight(node* p)
{
    int hl = height(p->left);
    int hr = height(p->right);
    p->height = (hl>hr?hl:hr)+1;
}

node* rotateright(node* p)
{
    node* q = p->left;
    p->left = q->right;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q;
}

node* rotateleft(node* q)
{
    node* p = q->right;
    q->right = p->left;
    p->left = q;
    fixheight(q);
    fixheight(p);
    return p;
}

node* balance(node* p)
{
    fixheight(p);
    if( bfactor(p)==2 )
    {
        if( bfactor(p->right) < 0 )
            p->right = rotateright(p->right);
        return rotateleft(p);
    }
    if( bfactor(p)==-2 )
    {
        if( bfactor(p->left) > 0  )
            p->left = rotateleft(p->left);
        return rotateright(p);
    }
    return p;
}

node* insert(node* p, int k)
{
    if( !p ) return new node(k);
    if( k<p->key )
        p->left = insert(p->left,k);
    else
        p->right = insert(p->right,k);
    return balance(p);
}

node* findmin(node* p)
{
    return p->left?findmin(p->left):p;
}

node* removemin(node* p)
{
    if( p->left==0 )
        return p->right;
    p->left = removemin(p->left);
    return balance(p);
}

node* remove(node* p, int k)
{
    if( !p ) return 0;
    if( k < p->key )
        p->left = remove(p->left,k);
    else if( k > p->key )
        p->right = remove(p->right,k);	
    else //  k == p->key 
    {
        node* q = p->left;
        node* r = p->right;
        delete p;
        if( !r ) return q;
        node* min = findmin(r);
        min->right = removemin(r);
        min->left = q;
        return balance(min);
    }
    return balance(p);
}
 node* find(node *p, int a)
{
	node *result=p;
	while(result->key!=a && result!=NULL)
	{
		if(result->key<a)
			result=result->right;
		else
			result=result->left;
	}
	if(result==NULL)
		cout<<"Такого элемента не существует";
	return result;
}

/*node* next(node *p)
{
	node* result=NULL;
	if(p->right!=NULL)
	{
		result=p->right;
		while(result->left!=NULL)
			result=result->left;
	}
	else
		if(p->parent!=NULL)
		{
			result=p->parent;
			int value=p->key;

			while(result->key<value)
				result=result->parent;
		}
		else
			cout<<"Такого элемента не существует";

	return result;
}

node* prev(node *p)
{
	node* result=NULL;
	if(p->left!=NULL)
	{
		result=p->left;
		while(result->right!=NULL)
			result=result->right;
	}
	else
		if(p->parent!=NULL)
		{
			result=p->parent;
			int value=p->key;

			while(result->key>value)
				result=result->parent;
		}
		else
			cout<<"Такого элемента не существует";

	return result;
}*/

void print(node* p) //выводит дерево в порядке возрастания элементов
{
	if(p->left)
		print(p->left);
	cout<<p->key<<' ';
	if(p->right)
		print(p->right);
}

int main()
{
	int n,a;
	node *p=NULL;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a;
		p=insert(p,a);
	}


	print(p);
	return 0;
}
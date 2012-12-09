#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

struct node // ��������� ��� ������������� ����� ������
{
    int key;
    int high;
    node* left;
    node* right;

    node(int k) { key = k; left = right = 0; high = 1; }
	node* findmin();
	node* removemin();
	node* remove(int k);
	int height();
	node* insert(int k);
	int diff();
	void fixheight();
	node* rotateright();
	node* rotateleft();
	node* balance();
};

int node::height()
{
    return this?high:0;
}

int node::diff()
{
    return right->height()-left->height();
}

void node::fixheight()
{
    int hl = left->height();
    int hr = right->height();
    high = (hl>hr?hl:hr)+1;
}

node* node::rotateright() // ������ ������� ������ p
{
    node* q = left;
    left = q->right;
    q->right = this;
    this->fixheight();
    q->fixheight();
    return q;
}

node* node::rotateleft() // ����� ������� ������ q
{
    node* p = right;
    right = p->left;
    p->left = this;
    fixheight();
    p->fixheight();
    return p;
}

node* node::balance() // ������������ ���� p
{
    fixheight();
    if( diff()==2 )
    {
        if( right->diff() < 0 )
            right = right->rotateright();
        return rotateleft();
    }
    if( diff()==-2 )
    {
        if( left->diff() > 0  )
            left = left->rotateleft();
        return rotateright();
    }
    return this; // ������������ �� �����
}

node* node::insert(int k) // ������� ����� k � ������ � ������ p
{
    if( !this ) return new node(k);
    if( k<key )
        left = left->insert(k);
    else
        right = right->insert(k);
    return balance();
}

node* node::findmin() // ����� ���� � ����������� ������ � ������ p 
{
    return left?left->findmin():this;
}

node* node::removemin() // �������� ���� � ����������� ������ �� ������ p
{
    if( left==0 )
        return right;
    left = left->removemin();
    return balance();
}

node* node::remove(int k) // �������� ����� k �� ������ p
{
    if( !this ) return 0;
    if( k < key )
        left = left->remove(k);
    else if( k > key )
        right = right->remove(k);	
    else //  k == p->key 
    {
        node* q = left;
        node* r = right;
        
        if( !r ) return q;
        node* min = r->findmin();
        min->right = r->removemin();
        min->left = q;
		delete this;
        return min->balance();
    }
    return balance();
}
/*treeElement* treeElement::find(treeElement *p, int a)
{
	treeElement *result=p;
	while(result->key!=a && result!=NULL)
	{
		if(result->key<a)
			result=result->right;
		else
			result=result->left;
	}
	if(result==NULL)
		cout<<"������ �������� �� ����������";
	return result;
}*/

/*treeElement* treeElement::next(treeElement *p)
{
	treeElement* result=NULL;
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
			cout<<"������ �������� �� ����������";

	return result;
}

treeElement* treeElement::prev(treeElement *p)
{
	treeElement* result=NULL;
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
			cout<<"������ �������� �� ����������";

	return result;
}*/

/*void node::print(node* p)
{
	
	if(p->left);
	cout<<p->left->key;
	if(p->right)
	cout<<' '<<p->right->key;
	cout<<endl;
	if(p->left)
		print(p->left);
	cout<<' ';
	if(p->right)
		print(p->right);
}*/

int main()
{
	int n,a;
	node T(0);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a;
		if(i==1)
			T.key=a;
		else
			T.insert(a);
	}
	//print(p);
	return 0;
}
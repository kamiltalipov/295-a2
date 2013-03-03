class BSTNode
{
public:
	BSTNode();
	const BSTNode* Find ( int val ) const;
	const BSTNode* Left () const { return left; }
	virtual BSTNode* Add ( int val );

private:
	int value;
	BSTNode *left;
	BSTNode *right;
};

class AVLTreeNode : public BSTNode{
public:
	virtual BSTNode* Add ( int val ); //they're different
	void Change();


private:
	//BSTNode baseNode;
	int height;



void add( BSTNode* node, int val )
{
	node->Add( val );
}

int main()
{
	AVLTreeNode* node = new AVLTreeNode;
	//заполняем
	add(node, 15);

	
	
	const AVLTreeNode* val = static_cast<const AVLTreeNode*>(node->Find( 15 ));
	BSTNode* node = new BSTNode;
	add (node, 14 );


	return 0;
}

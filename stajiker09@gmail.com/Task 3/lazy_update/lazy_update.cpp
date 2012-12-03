#include <iostream>
#include <vector>
#include <limits>
using namespace std;
struct Vertex
{
	int min, to_add;
};
class segment_tree
{
public:
	segment_tree(vector <int> &array)
	{
		tree=new Vertex[4*array.size()];
		size=array.size();
		build(1, 0, size-1, array);
	}
	~segment_tree()
	{
		delete[] tree;
	}
	int RMQ(int l, int r)
	{
		return RMQ(1, 0, size-1, l, r);
	}
	void update(int l, int r, int add)
	{
		update(1, 0, size-1, l, r, add);
	}
private:
	Vertex *tree;
	int size;
	void build(int vertex, int vertex_left, int vertex_right, vector <int> &array)
	{
		if(vertex_left==vertex_right)
		{
			tree[vertex].min=array[vertex_left];
			tree[vertex].to_add=0;
		}
		else
		{
			int vertex_middle=(vertex_left+vertex_right)/2;
			build(2*vertex, vertex_left, vertex_middle, array);
			build(2*vertex+1, vertex_middle+1, vertex_right, array);
			tree[vertex].min=min(tree[2*vertex].min, tree[2*vertex+1].min);
			tree[vertex].to_add=0;
		}
	}
	void push(int vertex)
	{
		tree[2*vertex].to_add+=tree[vertex].to_add, tree[2*vertex+1].to_add+=tree[vertex].to_add;
		tree[2*vertex].min+=tree[vertex].to_add, tree[2*vertex+1].min+=tree[vertex].to_add;
		tree[vertex].to_add=0;
	}
	int RMQ(int vertex, int vertex_left, int vertex_right, int left, int right)
	{
		push(vertex);
		if(right<vertex_left||vertex_right<left)
			return numeric_limits<int>::max();
		if(left<=vertex_left&&vertex_right<=right)
			return tree[vertex].min;
		int vertex_middle=(vertex_left+vertex_right)/2;
		return min(RMQ(2*vertex, vertex_left, vertex_middle, left, right), RMQ(2*vertex+1, vertex_middle+1, vertex_right, left, right));
	}
	void update(int vertex, int vertex_left, int vertex_right, int left, int right, int add)
	{
		push(vertex);
		if(right<vertex_left||vertex_right<left)
			return ;
		if(left<=vertex_left&&vertex_right<=right)
		{
			tree[vertex].to_add=add;
			tree[vertex].min+=add;
		}
		else
		{
			int vertex_middle=(vertex_left+vertex_right)/2;
			update(2*vertex, vertex_left, vertex_middle, left, right, add);
			update(2*vertex+1, vertex_middle+1, vertex_right, left, right, add);
			tree[vertex].min=min(tree[2*vertex].min, tree[2*vertex+1].min);
		}
	}
};
int main()
{
	int n;
	cin>>n;
	vector <int> array(n);
	for(int i=0; i<n; ++i)
		cin>>array[i];
	segment_tree tree(array);
	int k;
	cin>>k;
	for(int i=0; i<k; ++i)
	{
		char c;
		cin>>c;
		if(c=='a')
		{
			int l, r;
			cin>>l>>r;
			cout<<tree.RMQ(l-1, r-1)<<endl;
		}
		if(c=='b')
		{
			int l, r, add;
			cin>>l>>r>>add;
			tree.update(l-1, r-1, add);
		}
	}
	return 0;
}
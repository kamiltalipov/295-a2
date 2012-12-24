#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
using namespace std;
struct node
{
	string str;
	int freq;
	node()
	{
	}
	node(string Str, int Freq)
	{
		str=Str;
		freq=Freq;
	}
	bool operator<(const node &b) const
	{
		if(str<b.str)
			return true;
		return false;
	}
};
struct node_segment_tree
{
	int max, pos;
	node_segment_tree()
	{
	}
	node_segment_tree(int Max, int Pos)
	{
		max=Max, pos=Pos;
	}
	bool operator <(const node_segment_tree &b) const
	{
		if(max<b.max)
			return true;
		return false;
	}
};
class segment_tree
{
public:
	segment_tree(const vector <node> &array)
	{
		tree=new node_segment_tree[4*array.size()];
		size=array.size();
		build(1, 0, size-1, array);
	}
	~segment_tree()
	{
		delete[] tree;
	}
	node_segment_tree RMQ(int l, int r)
	{
		return RMQ(1, 0, size-1, l, r);
	}
private:
	node_segment_tree *tree;
	int size;
	void build(int vertex, int vertex_left, int vertex_right, const vector <node> &array)
	{
		if(vertex_left==vertex_right)
			tree[vertex]=node_segment_tree(array[vertex_left].freq, vertex_left);
		else
		{
			int vertex_middle=(vertex_left+vertex_right)/2;
			build(2*vertex, vertex_left, vertex_middle, array);
			build(2*vertex+1, vertex_middle+1, vertex_right, array);
			tree[vertex]=max(tree[2*vertex], tree[2*vertex+1]);
		}
	}
	node_segment_tree RMQ(int vertex, int vertex_left, int vertex_right, int left, int right)
	{
		if(right<vertex_left||vertex_right<left)
			return node_segment_tree(-1, -1);
		if(left<=vertex_left&&vertex_right<=right)
			return tree[vertex];
		int vertex_middle=(vertex_left+vertex_right)/2;
		return max(RMQ(2*vertex, vertex_left, vertex_middle, left, right), RMQ(2*vertex+1, vertex_middle+1, vertex_right, left, right));
	}
};
struct node_heap
{
	int freq, pos, left, right;
	node_heap(int Freq, int Pos, int Left, int Right)
	{
		freq=Freq;
		pos=Pos;
		left=Left;
		right=Right;
	}
	bool operator<(const node_heap &b) const
	{
		if(freq<b.freq)
			return true;
		return false;
	}
};
class suggest
{
public:
	suggest(const vector <node> &array)
	{
		data=array;
		sort(data.begin(), data.end());
		tree=new segment_tree(array);;
	}
	~suggest()
	{
		delete tree;
	}
	void search_query(string &prefix, int k, vector <int> &result)
	{
		int left=lower_bound(data.begin(), data.end(), node(prefix, 0))-data.begin();
		int right=upper_bound(data.begin(), data.end(), node(prefix+(char)100, 0))-data.begin();
		if(left==data.size())
			return ;
		if(right-left+1<k)
			k=right-left+1;
		priority_queue <node_heap> heap;
		node_segment_tree q=tree->RMQ(left, right);
		heap.push(node_heap(q.max, q.pos, left, right));
		while(k>0)
		{
			result.push_back(heap.top().pos);
			node_heap x=heap.top();
			q=tree->RMQ(x.left, x.pos-1);
			heap.push(node_heap(q.max, q.pos, x.left, x.pos-1));
			q=tree->RMQ(x.pos+1, x.right);
			heap.push(node_heap(q.max, q.pos, x.pos+1, x.right));
			heap.pop();
			--k;
		}
	}
private:
	vector <node> data;
	segment_tree *tree;
};
int main()
{
	int n;
	cin>>n;
	vector <node> array(n);
	for(int i=0; i<n; ++i)
		cin>>array[i].str>>array[i].freq;
	suggest hints(array);
	string s;
	int k;
	vector <int> result;
	cin>>s>>k;
	hints.search_query(s, k, result);
	if(result.size()==0)
		cout<<"Not found\n";
	else
		for(int i=0; i<result.size(); ++i)
			cout<<array[result[i]].str<<endl;
	return 0;
}
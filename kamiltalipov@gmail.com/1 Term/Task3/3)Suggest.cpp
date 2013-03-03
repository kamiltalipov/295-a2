#include <iostream>
using std :: istream;
using std :: ostream;
#include <fstream>
using std :: ifstream;
using std :: ofstream;
#include <string>
using std :: string;
#include <vector>
using std :: vector;
#include <queue>
using std :: priority_queue;
#include <algorithm>
using std :: min;
using std :: max;
using std :: lower_bound;
using std :: upper_bound;
using std :: sort;

struct SuggestNode
{
    string str;
    size_t freq;

    SuggestNode (const string& _str = string ())
        :
        str (_str),
        freq ()
    {
    }

    SuggestNode (const string& _str, size_t _freq)
        :
        str (_str),
        freq (_freq)
    {
    }

    friend istream& operator >> (istream& input, SuggestNode& node);
    friend ostream& operator << (ostream& output, const SuggestNode& node);
    friend bool operator < (const SuggestNode& node1, const SuggestNode& node2);
};

istream& operator >> (istream& input, SuggestNode& node)
{
    input >> node.str >> node.freq;
    return input;
}

ostream& operator << (ostream& output, const SuggestNode& node)
{
    output << node.str << ' ' << node.freq;
    return output;
}

bool operator < (const SuggestNode& node1, const SuggestNode& node2)
{
    return node1.str < node2.str;
}

class SuggestCompare
{
public:
    SuggestCompare (const string& _prefix)
        :
        prefix (_prefix)
    {
    }

	//use that node1 contain prefix
    bool operator () (const SuggestNode& node1, const SuggestNode& node2)
    {
		return node2.str.find (prefix) != 0;
    }

private:
    string prefix;
};

struct PositionMax
{
	size_t pos;
	SuggestNode max;
	
	PositionMax ()
		:
		pos (-1),
		max ()
	{
	}

	PositionMax (size_t _pos, const SuggestNode& _max)
		:
		pos (_pos),
		max (_max)
	{
	}

	friend bool operator < (const PositionMax& a, const PositionMax& b);
};

bool operator < (const PositionMax& a, const PositionMax& b)
{
	return a.max < b.max;
}

class SegmentTree 
{
public:
	void init (int n) 
	{
		for (offset = 1; offset < n; offset <<= 1)
			;

		v.resize(2 * offset);
	}

	void update (int x, const PositionMax& q) 
	{
		v[x + offset] = q;
		for (int i = (x + offset) >> 1; i > 0; i >>= 1)
			v[i] = max (v[i * 2], v[i * 2 + 1]);
	}

	PositionMax getMax (int left, int right) 
	{
		return getMax (1, 0, offset, left, right + 1);
	}

private:
	int offset;
	vector<PositionMax> v;
	
	PositionMax getMax (int x, int lo, int hi, int left, int right) 
	{
		if (lo >= right || hi <= left)
			return PositionMax ();
		if (lo >= left && hi <= right)
			return v[x];

		return max (getMax (x * 2, lo, (lo + hi) / 2, left, right), 
					getMax (x * 2 + 1, (lo + hi) / 2, hi, left, right));
	}
};

class Suggestor
{
public:
    Suggestor (const vector<SuggestNode>& _node)
        :
        node (_node),
		rmq ()
    {
        sort (node.begin (), node.end ());
        rmq.init (node.size ());
		for (size_t i = 0; i < node.size (); ++i)
			rmq.update (i, PositionMax (i, node[i]));
    }

    void getSuggest (const string& prefix, size_t quantity, vector<SuggestNode>& res);

private:
    vector<SuggestNode> node;
	SegmentTree rmq;    
};

void Suggestor :: getSuggest (const string& prefix, size_t quantity, vector<SuggestNode>& res)
{
    vector<SuggestNode> :: iterator left = lower_bound (node.begin (), node.end (), SuggestNode (prefix));
    vector<SuggestNode> :: iterator right = upper_bound (left, node.end (), SuggestNode (prefix), SuggestCompare (prefix));
    if (left == node.end ())
        return;
    if (right - left + 1 < quantity)
        quantity = right - left + 1;
	
	vector<size_t> maxPos (quantity);
	res.resize (quantity);
	for (size_t i = 0; i < quantity; ++i)
	{
		PositionMax pos = rmq.getMax (left - node.begin (), right - node.begin ());
		res[i] = pos.max;
		maxPos[i] = pos.pos;
		rmq.update (pos.pos, PositionMax ());
	}

	for (size_t i = 0; i < quantity; ++i)
	{
		rmq.update (maxPos[i], PositionMax (maxPos[i], res[i]));
	}
}


int main ()
{
    ifstream input ("input.txt");
    ofstream output ("output.txt");

    size_t allNode = 0;
    input >> allNode;
    vector<SuggestNode> node (allNode);
    for (size_t i = 0; i < allNode; ++i)
        input >> node[i];
    string prefix;
    input >> prefix;
    size_t quantity;
    input >> quantity;

    Suggestor s (node);
    vector<SuggestNode> res;
    s.getSuggest (prefix, quantity, res);

    for (size_t i = 0; i < res.size (); ++i)
        output << res[i].str << '\n';

    return 0;
}

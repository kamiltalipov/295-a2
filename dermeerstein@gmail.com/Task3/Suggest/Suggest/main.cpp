#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <queue>
#include <set>
#include "hashtable.h"

using namespace std;

struct word_freq
{
	string word;
	int freq;
	word_freq(){}
	word_freq(string w, int f)
	{
		word = w;
		freq = f;
	}
	bool operator< (const word_freq& b) const
	{
		for (int i = 0; i < min(word.size(), b.word.size()); i++)
		{
			if (word[i] < b.word[i])
				return 1;
			else if (word[i] > b.word[i])
				return 0;
		}
		return 0;
	}
};

class SegmentTree
{
public:
	SegmentTree(const vector <word_freq>& outside_vector);
	const word_freq* GetMax(int left, int right);

private:
	int size;
	//static const word_freq* NEUTRAL = new word_freq("", -1e+9);
	const word_freq* NEUTRAL;
	struct Node
	{
		int left, right;
		const word_freq* max_val;
	};
	vector <Node> buffer;
	
	const word_freq* _getMax(int left, int right, int index);
};

class Suggest
{
public:
	Suggest(const vector <word_freq>& Table);
	void Query(string& prefix, int number, vector <const word_freq*>& result); 
private:
	const vector <word_freq>& FreqTable;
	int size;
	SegmentTree* tree;
	struct Comp
	{
		bool operator() (const word_freq*& a, const word_freq*& b) const
		{
			return (a->freq < b->freq);
		}
	};
	priority_queue <const word_freq*, vector<const word_freq*>, Comp> heap;
};

Suggest::Suggest(const vector <word_freq>& Table):FreqTable(Table)
{
	size = FreqTable.size();
	tree = new SegmentTree(FreqTable);
}

void Suggest::Query(string& prefix, int number, vector <const word_freq*>& result)
{
	pair <vector <word_freq>::const_iterator, vector <word_freq>::const_iterator> range;
	word_freq search_val;
	search_val.word = prefix;
	range = equal_range(FreqTable.begin(), FreqTable.end(), search_val);
	int left, right;
	left = range.first - FreqTable.begin();
	right = range.second - FreqTable.begin() - 1;
	if (left > right)
		return;
	set <int> indices;
	const word_freq* tmp;
	int index, ind;
	tmp = tree->GetMax(left, right);
	result.push_back(tmp);
	index = tmp - &*FreqTable.begin();
	indices.insert(left - 1);
	indices.insert(index);
	indices.insert(right + 1);
	
	for (int i = 0; i < number - 1; i++)
	{
		left = *(--indices.lower_bound(index));
		right = *indices.upper_bound(index);
		if (index - left - 1 > 0)
		{
			tmp = tree->GetMax(left + 1, index - 1);
			heap.push(tmp);
			ind = tmp - &*FreqTable.begin();
			indices.insert(ind);
		}
		if (right - index - 1 > 0)
		{
			tmp = tree->GetMax(index + 1, right - 1);
			heap.push(tmp);
			ind = tmp - &*FreqTable.begin();
			indices.insert(ind);
		}
		if(heap.empty())
			break;
		result.push_back(heap.top());
		heap.pop();
		index = result[result.size() - 1] -  &*FreqTable.begin();
	}
}

SegmentTree::SegmentTree(const vector <word_freq>& outside_vector)
{
	NEUTRAL = new word_freq("", -1e+9);
	int pw2 = pow((double) 2, ceil(log((double) outside_vector.size()) / log((double)2)));
	size = 2 * pw2 - 1;
	buffer.resize(size);
	for (int i = 0; i < outside_vector.size(); i++)
	{
		buffer[pw2 - 1 + i].max_val = &outside_vector[i];
		buffer[pw2 - 1 + i].left = i;
		buffer[pw2 - 1 + i].right = i;
	}
	for (int i = outside_vector.size(); i < pw2; i++)
	{
		buffer[pw2 - 1 + i].max_val = NEUTRAL;
		buffer[pw2 - 1 + i].left = i;
		buffer[pw2 - 1 + i].right = i;
	}

	for (int i = pw2 - 2; i >= 0; i--)
	{
		if ((*buffer[2 * i + 1].max_val).freq > (*buffer[2 * i + 2].max_val).freq)
			buffer[i].max_val = buffer[2 * i + 1].max_val;
		else
			buffer[i].max_val = buffer[2 * i + 2].max_val;
		buffer[i].left = buffer[2 * i + 1].left;
		buffer[i].right = buffer[2 * i + 2].right;
	}
}

const word_freq* SegmentTree::GetMax(int left, int right)
{
	return _getMax(left, right, 0);
}

const word_freq* SegmentTree::_getMax(int left, int right, int index)
{
	if (right < buffer[index].left || left > buffer[index].right)
		return NEUTRAL;
	else if (left <= buffer[index].left && right >= buffer[index].right)
		return buffer[index].max_val;
	else
	{
		const word_freq* first;
		const word_freq* second;
		first = _getMax(left, right, 2 * index + 1);
		second = _getMax(left, right, 2 * index + 2);
		if ((*first).freq > (*second).freq)
			return first;
		else
			return second;
	}
}

bool sort_cmp(const word_freq &a, const word_freq &b)
{
	return (a.word < b.word);
}

string lower(string &s)
{
	string result;
	for (int i = 0; i < s.size(); i++)
		result += (islower(s[i]) ? s[i] : tolower(s[i]));
	return result;
}

int main()
{
	ifstream fin("Tolstoy.txt");
	HashTable* HT = new HashTable;
	string s;
	while(getline(fin, s))
	{
		int i = 0, j;
		while (i < s.size())
		{
			while (i < s.size() && !isalpha(s[i]))
				i++;
			if (i < s.size() && isalpha(s[i]))
			{
				j = i;
				while (i < s.size() && isalpha(s[i]))
					i++;
				HT->Add(lower(s.substr(j, i - j)));
			}
		}
	}
	word_freq t;
	vector <word_freq> FreqTable;
	for (HashTable::iterator it = HT->begin(); it != HT->end(); it++)
	{
		t.word = (*it).first;
		t.freq = (*it).second;
		FreqTable.push_back(t);
	}
	delete HT;
	
	sort(FreqTable.begin(), FreqTable.end(), sort_cmp);
	
	
	Suggest* S = new Suggest(FreqTable);
	int num;
	cin >> s >> num;
	vector <const word_freq*> answer;
	S->Query(s, num, answer);
	for (int i = 0; i < answer.size(); i++)
		cout << (*answer[i]).word << " " << (*answer[i]).freq << endl;
	return 0;
}
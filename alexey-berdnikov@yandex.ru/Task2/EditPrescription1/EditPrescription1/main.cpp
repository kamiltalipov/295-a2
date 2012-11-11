#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> edit_distance_vector(const string& string1, const string& string2)
{
	vector<int> result, buffer(string2.length()+1);
	for (unsigned j = 0; j <= string2.length(); ++j)
		result.push_back(j);
	for (unsigned i = 0; i < string1.length(); ++i) {
		buffer[0] = i+1;
		for (unsigned j = 0; j < string2.length(); ++j)
			buffer[j+1] = min(min(buffer[j],result[j+1])+1,result[j]+(string1[i]!=string2[j]));
		swap(result,buffer);
	}
	return result;
}

string edit_prescription(const string& string1, const string& string2)
{
	if (string1.empty())
		return string(string2.length(),'I');
	if (string2.empty())
		return string(string1.length(),'D');
	if (string1.length() == 1) {
		string result(string2.length(),'I');

		unsigned pos = string2.find(string1[0]);
		if (pos == -1)
			result[0] = 'R';
		else
			result[pos] = 'M';
		return result;
	}
	int m = string1.length()/2;
	string left = string1.substr(0,m);
	string right = string1.substr(m);
	string string2_reverse(string2);
	reverse(string2_reverse.begin(),string2_reverse.end());
	string right_reverse(right);
	reverse(right_reverse.begin(),right_reverse.end());
	vector<int> dist_left = edit_distance_vector(left,string2);
	vector<int> dist_right = edit_distance_vector(right_reverse,string2_reverse);

	int i_min = 0;
	int min_distance = string1.length()+string2.length();
	for (int i = 0, j = string2.length(); j >= 0; ++i, --j) {
		int distance = dist_left[i]+dist_right[j];
		if (distance < min_distance) {
			min_distance = distance;
			i_min = i;
		}
	}
	return edit_prescription(left,string2.substr(0,i_min))+edit_prescription(right,string2.substr(i_min));
}

int edit_distance(const string& string1, const string& string2)
{
	return edit_distance_vector(string1,string2).back();
}

void check()
{
	string string1, string2;
	cin >> string1 >> string2;
	cout << edit_distance(string1,string2) << endl
		<< edit_prescription(string1,string2) << endl;
}

int main()
{
	check();
	_CrtDumpMemoryLeaks();
	return 0;
}
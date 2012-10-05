#include <iostream>
#include <string>
#include <string.h>
#include <vector>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<pair<string, int> > data;
    int marks[5];
    for (int i = 0; i < 5; i++)
        marks[i] = 0;
    for (int i = 0; i < n; i++)
    {
        int readable3;
        string readable1, readable2;
        cin >> readable1 >> readable2 >> readable3;
        data.push_back(make_pair(readable1 + " " + readable2, readable3));
        marks[readable3 - 1]++;
    }
    for (int i = 1; i < 5; i++)
        marks[i] = marks[i - 1] + marks[i];
    vector<pair<string, int> > answer(n);
    for (int i = 0; i < n; i++)
        answer[marks[data[i].second - 2]++] = data[i];
    for (int i = 0; i < n; i++)
        cout << answer[i].first << " " << answer[i].second << endl;
    return 0;
}

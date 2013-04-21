#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>
#include <queue>
#include <set>
#include <stdlib.h>

using namespace std;

struct QUnit
{
    int y, x;
    int distance;
    int estimation;

    QUnit(int y, int x, int distance, int estimation):
        y(y), x(x), distance(distance), estimation(estimation) {};

    bool operator <(const QUnit &other)const
    {
        return (distance + estimation) > (other.distance + other.estimation);
    }
};

int estimate(int y, int x, int l1, int l2)
{
    if (l1 - y > l2)
        return -l2;
    else
        return -l1 + y;
}

int main()
{
    ifstream file1("input1.txt");
    ifstream file2("input2.txt");
    string s1;
    string s2;
    getline(file1, s1, '\0');
    getline(file2, s2, '\0');
    file1.close();
    file2.close();
    int l1 = s1.length();
    int l2 = s2.length();
    priority_queue<QUnit> q;
    set< pair<int, int> > used;
    q.push(QUnit(0, 0, 0, 0));
    while (!q.empty())
    {
        int y = q.top().y;
        int x = q.top().x;
        int dist = q.top().distance;
        if (y == l1 && x == l2)
        {
            cout << -dist;
            break;
        }
        q.pop();
        if (used.find(make_pair(y, x)) != used.end())
            continue;
        used.insert(make_pair(y, x));
        if (y != l1 && x != l2 && s1[y] == s2[x])
            q.push(QUnit(y + 1, x + 1, dist - 1, estimate(y + 1, x + 1, l1, l2)));
        if (y != l1)
            q.push(QUnit(y + 1, x, dist, estimate(y + 1, x, l1, l2)));
        if (x != l2)
            q.push(QUnit(y, x + 1, dist, estimate(y, x + 1, l1, l2)));
    }
    return 0;
}

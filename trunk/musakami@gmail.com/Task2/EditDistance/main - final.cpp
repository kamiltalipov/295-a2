#include <iostream>
#include <string>
#include <string.h>
#include <vector>

using namespace std;

int solve(string &s1, string &s2, int left1, int right1, int left2, int right2, vector<pair<int, int> > &answer)
{
    if (left1 == right1)
    {
        if (right2 < left2)
        {
            answer.push_back(make_pair(left1, right2));
            return 1;
        }
        else
        {
            bool jump = false;
            for (int i = left2; i < right2; i++)
            {
                if (s1[i - 1] == s2[left1 - 1])
                    jump = true;
                if (jump)
                    answer.push_back(make_pair(left1, i));
                else
                    answer.push_back(make_pair(left1 - 1, i));
            }
            answer.push_back(make_pair(left1, right2));
            if (!jump && s1[right2 - 1] != s2[left1 - 1])
                return right2 - left2 + 1;
            return right2 - left2;
        }
    }
    int middle = (left1 + right1) / 2;
    int length = right2 - left2 + 1;
    vector<int> dleft[2];
    for (int i = 0; i < 2; i++)
        dleft[i].resize(length + 1, (1 << 31) - 1);
    for (int i = 0; i <= length; i++)
        dleft[0][i] = i;
    for (int i = left1; i <= middle; i++)
    {
        dleft[1][0] = i - left1 + 1;
        for (int j = 1; j <= length; j++)
        {
            dleft[1][j] = (1 << 31) - 1;
            if (s2[i - 1] == s1[left2 + j - 2])
            {
                dleft[1][j] = dleft[0][j - 1];
            }
            dleft[1][j] = min(dleft[1][j], dleft[1][j - 1] + 1);
            dleft[1][j] = min(dleft[1][j], dleft[0][j] + 1);
            dleft[1][j] = min(dleft[1][j], dleft[0][j - 1] + 1);
        }
        dleft[1].swap(dleft[0]);
    }
    vector<int> dright[2];
    for (int i = 0; i < 2; i++)
        dright[i].resize(length + 1, (1 << 31) - 1);
    for (int i = length; i >= 0; i--)
        dright[0][i] = length - i;
    for (int i = right1; i > middle; i--)
    {
        dright[1][length] = right1 - i + 1;
        for (int j = length - 1; j >= 0; j--)
        {
            dright[1][j] = (1 << 31) - 1;
            if (s2[i - 1] == s1[left2 + j - 1])
            {
                dright[1][j] = dright[0][j + 1];
            }
            dright[1][j] = min(dright[1][j], dright[1][j + 1] + 1);
            dright[1][j] = min(dright[1][j], dright[0][j] + 1);
            dright[1][j] = min(dright[1][j], dright[0][j + 1] + 1);
        }
        dright[1].swap(dright[0]);
    }
    int min = 0;
    int mincost = dleft[0][0] + dright[0][0];
    for (int i = 0; i <= length; i++)
    {
        if (dleft[0][i] + dright[0][i] < mincost)
        {
            min = i;
            mincost = dleft[0][i] + dright[0][i];
        }
    }
    solve(s1, s2, left1, middle, left2, left2 + min - 1, answer);
    solve(s1, s2, middle + 1, right1, left2 + min, right2, answer);
    return mincost;
}

int main()
{
    string a, b;
    cin >> a >> b;
    int lengtha = a.length();
    int lengthb = b.length();
    vector<pair<int, int> > answer;
    answer.push_back(make_pair(0, 0));
    cout << solve(a, b, 1, lengthb, 1, lengtha, answer)  << endl;
    for (int i = 1; i < answer.size(); i++)
    {
        if (answer[i].first == answer[i - 1].first)
            cout << "Delete from 1st string at " << answer[i].second << endl;
        else
            if (answer[i].second == answer[i - 1].second)
                cout << "Add " << b[answer[i].first - 1] << " to 1st string before " << answer[i].second + 1 << endl;
            else
                if (a[answer[i].second - 1] != b[answer[i].first - 1])
                    cout << "Change in the 1st string at " << answer[i].second << " to " << b[answer[i].first - 1] << endl;
    }
    return 0;
}

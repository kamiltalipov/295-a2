#include <iostream>
using std :: cin;
using std :: cout;
#include <string>
using std :: string;
#include <vector>
using std :: vector;
#include <algorithm>
using std :: min;

enum ActionType
{
    INSERT,
    DELETE,
    REPLACE
};

struct Action
{
    ActionType type;
    size_t pos;
    char c;

    Action (ActionType _type, size_t _pos, char _c = '\0')
        :
        type (_type),
        pos (_pos),
        c (_c)
    {
    }
};

void levenshteinDistance (const string& s1, const string& s2,
                          size_t l1, size_t r1, size_t l2, size_t r2,
                          vector<Action>& ans)
{
    if (l1 == r1)
    {
        for (int i = r2 - 1; i >= l2; --i)
        {
            Action curAction (INSERT, l1, s2[i]);
            ans.push_back (curAction);
        }

        return;
    }
    if (l2 == r2)
    {
        for (size_t i = l1; i < r1; ++i)
        {
            Action curAction (DELETE, i + 1, s1[i]);
            ans.push_back (curAction);
        }

        return;
    }
    if (l2 + 1 == r2)
    {
        size_t findPos = -1;
        for (findPos = l1; findPos < r1; ++findPos)
            if (s1[findPos] == s2[l2])
                break;

        if (findPos == r1)
        {
            Action curAction (REPLACE, l1 + 1, s2[l2]);
            ans.push_back (curAction);
            for (size_t i = l1 + 1; i < r1; ++i)
            {
                curAction.type = DELETE, curAction.pos = i + 1, curAction.c = s1[i];
                ans.push_back (curAction);
            }

            return;
        }

        for (size_t i = l1; i < r1; ++i)
            if (i != findPos)
            {
                Action curAction (DELETE, i + 1, s1[i]);
                ans.push_back (curAction);
            }

        return;
    }

    vector<size_t> dist[2];
    dist[0].resize (r1 - l1 + 1);
    dist[1].resize (r1 - l1 + 1);
    for (size_t i = 0; i < dist[0].size (); ++i)
        dist[0][i] = i;

    size_t mid = (l2 + r2) / 2;
    bool curDist = true;
    for (size_t i = 0; i < mid - l2; ++i)
    {
        dist[curDist][0] = i + 1;
        for (size_t j = 1; j < dist[!curDist].size (); ++j)
        {
            dist[curDist][j] = min (min (dist[!curDist][j], dist[curDist][j - 1]) + 1,
                                    dist[!curDist][j - 1] + (s1[l1 + j - 1] != s2[l2 + i]));
        }

        curDist = !curDist;
    }

    vector<size_t> leftDistance (dist[!curDist].begin (), dist[!curDist].end ());

    for (int i = r1 - l1; i >= 0; --i)
        dist[0][i] = r1 - l1 - i;
    curDist = true;
    for (int i = 0; i <= (r2 - l2 - 2) / 2; ++i)
    {
        dist[curDist][dist[curDist].size () - 1] = i + 1;
        for (int j = dist[curDist].size () - 2; j >= 0; --j)
            dist[curDist][j] = min (min (dist[!curDist][j], dist[curDist][j + 1]) + 1,
                                    dist[!curDist][j + 1] + (s1[l1 + j] != s2[r2 - i - 1]));

        curDist = !curDist;
    }

    size_t minDistI = 0;
    for (size_t i = 1; i < leftDistance.size (); ++i)
    {
        if (leftDistance[minDistI] + dist[!curDist][minDistI] > leftDistance[i] + dist[!curDist][i])
            minDistI = i;
    }


    levenshteinDistance (s1, s2, l1, l1 + minDistI, l2, mid, ans);
    levenshteinDistance (s1, s2, l1 + minDistI, r1, mid, r2, ans);
}

inline void levenshteinDistance (const string& s1, const string& s2,
                                  vector<Action>& res)
{
    levenshteinDistance (s1, s2, 0, s1.size (), 0, s2.size (), res);
}

int main ()
{
    string s1, s2;
    cin >> s1 >> s2;

    vector<Action> ans;
    levenshteinDistance (s1, s2, ans);
    cout << ans.size () << '\n';
    int shiftI = 0;
    for (size_t i = 0; i < ans.size (); ++i)
    {
        if (ans[i].type == INSERT)
        {
            cout << "INSERT " << ans[i].c << " after " << ans[i].pos + shiftI << '\n';
            ++shiftI;
        }
        else if (ans[i].type == DELETE)
        {
            cout << "DELETE " << ans[i].c << " at pos " << ans[i].pos + shiftI << '\n';
            --shiftI;
        }
        else
            cout << "REPLACE at pos " << ans[i].pos + shiftI << " to " << ans[i].c << '\n';
    }

    return 0;
}

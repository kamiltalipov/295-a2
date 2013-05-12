#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool dfs(int v, vector<bool> &used, vector<int> &back,  vector< vector<int> > &graph)
{
    used[v] = true;
    for (int i = 0; i < graph[v].size(); i++)
    {
        int u = graph[v][i];
        int temp = back[u];
        bool p;
        if (temp != -1)
            p = used[back[u]];
        if (back[u] == -1 || !used[back[u]] && dfs(back[u], used, back, graph))
        {
            back[u] = v;
            return true;
        }
    }
    return false;
}

int main()
{
    string word;
    int n;
    vector<int> refer[256];
    cin >> word >> n;
    int v = word.length();
    vector< vector<int> > graph(v);
    for (int i = 0; i < v; i++)
    {
        refer[word[i]].push_back(i);
    }
    for (int i = 0; i < n; i++)
    {
        string sides;
        cin >> sides;
        int length = sides.length();
        for (int j = 0; j < length; j++)
            for (int k = 0; k < refer[sides[j]].size(); k++)
            {
                int temp = refer[sides[j]][k];
                graph[refer[sides[j]][k]].push_back(i);
            }
    }
    vector<int> back(n, -1);
    vector<bool> used(v);
    bool possible = true;
    for (int i = 0; i < v; i++)
    {
        for (int i = 0; i < v; i++)
            used[i] = false;
        possible &= dfs(i, used, back, graph);
    }
    cout << (possible ? "YES" : "NO") << endl;
    for (int i = 0; i < n; i++)
    {
        if (back[i] != -1)
            cout << i + 1 << ": " << word[back[i]] << endl;
    }
    return 0;
}

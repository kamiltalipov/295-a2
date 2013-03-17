#include <iostream>
#include <vector>
#include <stack>

using namespace std;

vector< vector<int> > graph;

int main()
{
    int n;
    cin >> n;
    graph.resize(n);
    for (int i = 0; i < n; i++)
    {
        int k;
        cin >> k;
        for (int j = 0; j < k; j++)
        {
            int to;
            cin >> to;
            graph[i].push_back(to);
        }
    }
    vector<int> visited(n, 0);
    stack< pair<int, int> > st;
    stack<int> topsort;
    bool loops = false;
    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            st.push(make_pair(i, 0));
            while (!st.empty())
            {
                int v = st.top().first;
                int j = st.top().second;
                st.pop();
                visited[v] = 1;
                for (; j < graph[v].size(); j++)
                {
                    int u = graph[v][j];
                    if (visited[u] == 0)
                    {
                        st.push(make_pair(v, j + 1));
                        st.push(make_pair(u, 0));
                        break;
                    }
                    if (visited[u] == 1 && u != v)
                        loops = true;
                }
                if (j == graph[v].size())
                    topsort.push(v);
                visited[v] = 2;
            }
        }
    }
    if (loops)
        cout << "Unable to sort in topological order";
    else
        for (int i = 0; i < n; i++)
        {
            int v = topsort.top();
            cout << v << " ";
            topsort.pop();
        }
    return 0;
}

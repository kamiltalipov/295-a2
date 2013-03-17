#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <vector>
#include <stack>
#include <assert.h>

using namespace std;

struct Edge
{
    int from;
    int to;

    Edge(int from, int to):
        from(from), to(to) {}

    bool operator ==(const Edge &other) const
    {
        return (from == other.from && to == other.to);
    }

    bool operator !=(const Edge &other) const
    {
        return (from != other.from || to != other.to);
    }
};

class Graph
{
    vector< vector< Edge > > graph;
    bool nonoriented;

    void visit_all_find(int v, int prev, int &t,
                    vector<Edge> &bridges,
                    vector< vector<int> > &edgeblocks,
                    vector<int> &cutvertex,
                    vector< vector<Edge> > &vertblocks,
                    vector<int> &color,
                    vector<int> &tin,
                    vector<int> &up,
                    stack<Edge> &stedge,
                    stack<int> &stvertex)
    {
        color[v] = 1;
        t++;
        tin[v] = t;
        up[v] = tin[v];
        stvertex.push(v);
        int cnt = 0;
        bool cutvert = false;
        for (int i = 0; i < graph[v].size(); i++)
        {
            int u = graph[v][i].to;
            if (color[u] == 0)
            {
                stedge.push(graph[v][i]);
                cnt++;
                visit_all_find(u, v, t, bridges, edgeblocks, cutvertex, vertblocks, color, tin, up, stedge, stvertex);
                up[v] = min(up[v], up[u]);
                if (up[u] >= tin[v])
                {
                    if (prev != - 1)
                        cutvert = true;
                    vertblocks.push_back(vector<Edge>());
                    Edge edge(0, 0);
                    do
                    {
                        edge = stedge.top();
                        vertblocks[vertblocks.size() - 1].push_back(edge);
                        stedge.pop();
                    } while (edge != graph[v][i]);
                }
                if (up[u] >= tin[u])
                {
                    bridges.push_back(graph[v][i]);
                    edgeblocks.push_back(vector<int>());
                    int vertex;
                    do
                    {
                        vertex = stvertex.top();
                        edgeblocks[edgeblocks.size() - 1].push_back(vertex);
                        stvertex.pop();
                    } while (vertex != u);
                }
            }
            if (color[u] == 1 && u != prev)
            {
                up[v] = min(up[v], tin[u]);
                stedge.push(graph[v][i]);
            }
        }
        if (cutvert)
            cutvertex.push_back(v);
        if (prev == -1)
        {
            if (cnt > 1)
                cutvertex.push_back(v);
            if (!stvertex.empty())
            {
                edgeblocks.push_back(vector<int>());
                while (!stvertex.empty())
                {
                    edgeblocks[edgeblocks.size() - 1].push_back(stvertex.top());
                    stvertex.pop();
                };
            }
        }
        t++;
        color[v] = 2;
    }

public:
    Graph(bool nonoriented = false)
    {
        this -> nonoriented = nonoriented;
    };

    Graph(int n, bool nonoriented = false)
    {
        graph.resize(n);
        this -> nonoriented = nonoriented;
    }

    int AddVertex()
    {
        graph.push_back(vector<Edge>());
        return graph.size() - 1;
    }

    void AddEdge(int from, int to)
    {
        graph[from].push_back(Edge(from, to));
        if (nonoriented)
            graph[to].push_back(Edge(to, from));
    }

    void dfs_all_find(vector<Edge> &bridges, vector< vector<int> > &edgeblocks, vector<int> &cutvertex, vector< vector<Edge> > &vertblocks)
    {
        assert(nonoriented);
        vector<int> color(graph.size(), 0), up(graph.size()), tin(graph.size());
        stack<Edge> stedge;
        stack<int> stvertex;
        int t = 0;
        for (int i = 0; i < graph.size(); i++)
        {
            if (color[i] == 0)
               visit_all_find(i, -1, t, bridges, edgeblocks, cutvertex, vertblocks, color, tin, up, stedge, stvertex);
        }
    }


};

#endif // GRAPH_H_INCLUDED

#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <iostream>
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

    void visit_strong_t(int v, int &t, vector<int> &color, vector<int> &tin, vector<int> &up, stack<int> &stvertex, vector<bool> &instack, vector<vector<int> > &components)
    {
        color[v] = 1;
        stvertex.push(v);
        instack[v] = true;
        t++;
        tin[v] = t;
        up[v] = t;
        for (int i = 0; i < graph[v].size(); i++)
        {
            int u = graph[v][i].to;
            if (color[u] == 0)
            {
                visit_strong_t(u, t, color, tin, up, stvertex, instack, components);
                up[v] = min(up[v], up[u]);
            }
            else
                if (instack[u])
                    up[v] = min(up[v], tin[u]);
        }
        if (up[v] == tin[v])
        {
            components.push_back(vector<int>());
            int vert;
            do
            {
                vert = stvertex.top();
                stvertex.pop();
                instack[vert] = false;
                components[components.size() - 1].push_back(vert);
            } while (vert != v);
        }
    }

    void visit_tsort(int v, vector<bool> &color, stack<int> &tsort)
    {
        color[v] = true;
        for (int i = 0; i < graph[v].size(); i++)
        {
            int u = graph[v][i].to;
            if (!color[u])
                visit_tsort(u, color, tsort);
        }
        tsort.push(v);
    }

    void visit_strong_k(int v, vector<bool> &color, vector<vector<Edge> > &tgraph, vector<int> &component)
    {
        color[v] = true;
        component.push_back(v);
        for (int i = 0; i < tgraph[v].size(); i++)
        {
            int u = tgraph[v][i].to;
            if (!color[u])
                visit_strong_k(u, color, tgraph, component);
        }
    }


    void visit_loop(int v, vector<int> &current, vector<int> &loop)
    {
        while (current[v] < graph[v].size())
        {
            int u = graph[v][current[v]].to;
            current[v]++;
            visit_loop(u, current, loop);
        }
        loop.push_back(v);
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

    void topsort(stack<int> &tsort)
    {
        vector<bool> color(graph.size(), false);
        for (int i = 0; i < graph.size(); i++)
        {
            if (!color[i])
                visit_tsort(i, color, tsort);
        }
    }

    void find_strong_kosaraju(vector<vector<int> > &components)
    {
        vector<vector<Edge> > tgraph(graph.size());
        for (int i = 0; i < graph.size(); i++)
            for (int j = 0; j < graph[i].size(); j++)
                tgraph[graph[i][j].to].push_back(Edge(graph[i][j].to, graph[i][j].from));
        stack<int> tsort;
        topsort(tsort);
        vector<bool> color(graph.size(), false);
        while (!tsort.empty())
        {
            int v = tsort.top();
            tsort.pop();
            if (!color[v])
            {
                components.push_back(vector<int>());
                visit_strong_k(v, color, tgraph, components[components.size() - 1]);
            }
        }
    }

    void find_strong_tarjan(vector<vector<int> > &components)
    {
        vector<int> color(graph.size(), 0), up(graph.size()), tin(graph.size());
        vector<bool> instack(graph.size(), false);
        stack<int> stvertex;
        int t = 0;
        for (int i = 0; i < graph.size(); i++)
            if (color[i] == 0)
                visit_strong_t(i, t, color, tin, up, stvertex, instack, components);
    }

    void eulerian_loop(vector<int> &loop)
    {
        vector<int> deg_in(graph.size(), 0), deg_out(graph.size(), 0);
		int v = 0;
		int cnt = 0;
        for (int i = 0; i < graph.size(); i++)
        {
            deg_out[i] = graph[i].size();
			cnt += deg_out[i];
			if (deg_out[i] != 0)
				v = i;
            for (int j = 0; j < graph[i].size(); j++)
            {
                deg_in[graph[i][j].to]++;
            }
        }
        for (int i = 0; i < graph.size(); i++)
            if (deg_in[i] != deg_out[i])
            {
                cout << "No loop";
                return;
            }
        vector<int> current(graph.size(), 0);
        visit_loop(v, current, loop);
        if (cnt != loop.size() - 1)
        {
            cout << "No loop";
            loop.clear();
            return;
        }
        int half_size = loop.size() / 2;
        for (int i = 0; i < half_size; i++)
            swap(loop[i], loop[loop.size() - 1 - i]);
    }
};

#endif // GRAPH_H_INCLUDED


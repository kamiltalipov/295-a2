#include <iostream>
using std :: cin;
using std :: cout;
#include <vector>
using std :: vector;
#include <utility>
using std :: pair;
using std :: make_pair;
#include <algorithm>
using std :: sort;
#include <cstdlib>
#include <ctime>
#include <cmath>

#include "DSU.h"

typedef pair<size_t, size_t> Edge;
typedef pair<double, Edge> CostEdge;

typedef pair<double, double> Point;

const double EPS = 0.0001;
const double RAND_MAX_D = static_cast<double> (RAND_MAX);

void findMST (vector<CostEdge>& g, size_t all_v, vector<vector<pair<size_t, double> > >& res)
{
    DSU dsu (all_v);
    sort (g.begin (), g.end ());
    for (size_t i = 0; i < g.size (); ++i)
    {
        size_t v = g[i].second.first,
                u = g[i].second.second;
        if (dsu.find_set (v) != dsu.find_set (u))
        {
            res[v].push_back (make_pair (u, g[i].first));
            res[u].push_back (make_pair (v, g[i].first));
            dsu.union_sets (v, u);
        }
    }
}

void getOrderInner (const vector<vector<pair<size_t, double> > >& g, size_t cur_v,
                    vector<bool>& used, vector<size_t>& order)
{
    if (used[cur_v])
        return;
    used[cur_v] = true;
    order.push_back (cur_v);

    for (size_t i = 0; i < g[cur_v].size (); ++i)
    {
        if (!used[g[cur_v][i].first])
            getOrderInner (g, g[cur_v][i].first, used, order);
    }
}

void getOrder (const vector<vector<pair<size_t, double> > >& mst, vector<size_t>& order)
{
    vector<bool> used (mst.size (), false);
    getOrderInner (mst, 0, used, order);
}

Point BoxMuller (const Point& center, double sigma)
{
    double x, y, s;
    do
    {
        x = 2.0 * (static_cast<double> (rand ()) / RAND_MAX_D) - 1.0;
        y = 2.0 * (static_cast<double> (rand ()) / RAND_MAX_D) - 1.0;
        s = x * x + y * y;
    } while ((s >= 1.0) || (s <= EPS));

    double lns = log (s);
    double z0 = x * sqrt (-2.0 * lns / s),
           z1 = y * sqrt (-2.0 * lns / s);
    return make_pair (center.first + sigma * z0, center.second + sigma * z1);
}

inline double dist (const Point& p1, const Point& p2)
{
    return sqrt ((p1.first - p2.first) * (p1.first - p2.first) + 
                 (p1.second - p2.second) * (p1.second - p2.second)); 
}

int main ()
{
    srand (time (0));
    
    size_t all_centers, all_point_near_center;
    cin >> all_centers >> all_point_near_center;
    double sigma1, sigma2;
    cin >> sigma1 >> sigma2;

    vector<Point> centers (all_centers);
    for (size_t i = 0; i < all_centers; ++i)
        centers[i] = BoxMuller (make_pair (0.0, 0.0), sigma1);
    vector<Point> points (all_centers * all_point_near_center);
    for (size_t i = 0; i < all_centers; ++i)
        for (size_t j = 0; j < all_point_near_center; ++j)
            points[i * all_point_near_center + j] = BoxMuller (centers[i], sigma2); 

    vector<CostEdge> g (points.size () * points.size ());
    for (size_t i = 0; i < points.size (); ++i)
        for (size_t j = 0; j < points.size (); ++j)
		{
            g[i * points.size () + j] = make_pair (dist (points[i], points[j]), 
												   make_pair (i, j));
		}
    vector<vector<pair<size_t, double> > > mst (points.size ());
    findMST (g, points.size (), mst);
    vector<size_t> v_order;
    getOrder (mst, v_order);
    for (size_t i = 0; i < v_order.size (); ++i)
        cout << v_order[i] << ' ';

    return 0;
}

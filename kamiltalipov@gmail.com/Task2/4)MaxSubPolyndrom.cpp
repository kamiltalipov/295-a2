#include <iostream>
using std :: cin;
using std :: cout;
#include <vector>
using std :: vector;


vector<int> findMaxSubPolyndrom (const vector<int>& a, int leftI, int rightI)
{
    static vector<vector<vector<int> > > pol (a.size (), vector<vector<int> > (a.size ()));
    if (leftI > rightI)
       return vector<int> ();
    if (!pol[leftI][rightI].empty ())
       return pol[leftI][rightI];
    if (leftI == rightI)
       return vector<int> (1, a[leftI]);
    
    vector<int> res1 = findMaxSubPolyndrom (a, leftI, rightI - 1),
                res2 = findMaxSubPolyndrom (a, leftI + 1, rightI);
    if (a[leftI] == a[rightI])
    {
       vector<int> res3 = findMaxSubPolyndrom (a, leftI + 1, rightI - 1);
       
       if (res1.size () > res2.size ())
       {
          if (res3.size () + 2 > res1.size ())
          {
             vector<int> res (res3.size () + 2);
             res[0] = a[leftI];
             for (int i = 0; i < res3.size (); ++i)
                 res[i + 1] = res3[i];
             res[res3.size () + 1] = a[rightI];
             
             pol[leftI][rightI] = res;
          }
          else
             pol[leftI][rightI] = res1;
       }
       else
       {
          if (res3.size () + 2 > res2.size ())
          {
             vector<int> res (res3.size () + 2);
             res[0] = a[leftI];
             for (int i = 0; i < res3.size (); ++i)
                 res[i + 1] = res3[i];
             res[res3.size () + 1] = a[rightI];
             
             pol[leftI][rightI] = res;
          }
          else
             pol[leftI][rightI] = res2;
       }
    }
    else
    {
        if (res1.size () > res2.size ())
           pol[leftI][rightI] = res1;
        else
           pol[leftI][rightI] = res2;
    }
    
    return pol[leftI][rightI];
}

inline void findMaxSubPolyndrom (const vector<int>& a, vector<int>& res)
{
    if (a.empty ())
       return;
    res = findMaxSubPolyndrom (a, 0, a.size () - 1);     
}

int main ()
{
    size_t n;
    cin >> n;
    vector<int> a (n);
    for (size_t i = 0; i < n; ++i)
        cin >> a[i];
    
    vector<int> res;
    findMaxSubPolyndrom (a, res);
    for (size_t i = 0; i < res.size (); ++i)
        cout << res[i]  << ' '; 
    
    
    cin.get ();
    cin.get ();
    
    return 0;
}

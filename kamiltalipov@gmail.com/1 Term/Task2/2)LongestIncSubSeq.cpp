#include <iostream>
using std :: cin;
using std :: cout;
#include <vector>
using std :: vector;

void findMaxSubArray (const vector<int>& a, vector<int>& res)
{
     if (a.empty ())
        return;
        
     vector<int> prev (a.size ()),
                 last (a.size ());
     int maxPos = -1;
     for (size_t i = 0; i < a.size (); ++i)
     {
         int leftI = 0,
             rightI = maxPos;
         while (leftI <= rightI)
         {
             int curI = (leftI + rightI) / 2;
             if (a[i] <= a[last[curI]])
                rightI = curI - 1;
             else
                leftI = curI + 1;
         }    
         if (rightI >= 0)
            rightI = last[rightI];
         
         prev[i] = rightI;
         last[leftI] = i;
         
         if (maxPos < leftI)
            maxPos = leftI;
     }
     
     res.resize (maxPos + 1);
     int cur = last[maxPos];
     for (int i = maxPos; i >= 0; --i)
     {
         res[i] = a[cur];
         cur = prev[cur];
     }
}

int main ()
{
    size_t n;
    cin >> n;
    vector<int> a (n);
    for (size_t i = 0; i < n; ++i)
        cin >> a[i];
    
    vector<int> res;
    findMaxSubArray (a, res);
    for (size_t i = 0; i < res.size (); ++i)
        cout << res[i]  << ' '; 
    
    
    cin.get ();
    cin.get ();
    
    return 0;
}

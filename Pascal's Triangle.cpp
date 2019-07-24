///Program for Pascal’s Triangle
/// A O(n^2) time and O(1) extra space
/// C(n,k) = nCk = n!/(k!(n-k)!)
#include <bits/stdc++.h>
using namespace std;
void printPascal(int n)
{
    for (int line = 1; line <= n; line++)
    {
        int C = 1;
        for (int i = 1; i <= line; i++)
        {
            cout<< C<<" ";
            C = C * (line - i) / i;
        }
        cout<<"\n";
    }
}
int main()
{
    int n = 10;
    printPascal(n);
    return 0;
}

/****************************
1
1 1
1 2 1
1 3 3 1
1 4 6 4 1
1 5 10 10 5 1
1 6 15 20 15 6 1
1 7 21 35 35 21 7 1
1 8 28 56 70 56 28 8 1
1 9 36 84 126 126 84 36 9 1
****************************/

#include <iostream>
long long int tribon(int n)
{
    if (n==1 || n==2) return 0;
    if (n==3 || n==4) return 1;
    return (tribon(n-3)+tribon(n-2)+tribon(n-1));
}
using namespace std;
int main()
{
    int n;
    cin>>n;
    cout<<tribon(n);
    return 0;
}

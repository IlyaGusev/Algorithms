#include <iostream>
#include <cstdlib>
using namespace std;
int main()
{
    int n;
    cin>>n;
    if (n==0)
    {
        cout<<0;
        return 0;
    }
    if (n==1 || n==2)
    {
        cout<<1;
        return 0;
    }
    int* a=(int*)malloc(n*sizeof(int));
    a[0]=0;
    a[1]=1;
    a[2]=1;
    for (int i=3; i<=n; i++)
    {
        a[i]=0;
        for (int j=1; j<=i-1; j++)
            a[i]+=a[j]*a[i-j];
    }
    cout<<a[n];
}

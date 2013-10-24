#include <iostream>
using namespace std;
long long int a[4];
int main()
{
    int n;
    cin>>n;
    a[0]=0;
    a[1]=0;
    a[2]=1;
    a[3]=1;
    int i=0;
    int j=1;
    while (j*4+1+i<=n)
    {
        a[i]=0;
        for (int k=0; k<=3; k++)
        {
            if (k!=i) a[i]+=a[k];
        }
        i++;
        if (i==4) {i=0; j++;}
    }
    if (i==0 && n>4) i=4;
    if (n>4 && i!=0)
        cout<<a[i-1];
    else
        cout<<a[n-1];
    return 0;
}

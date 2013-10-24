#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
using namespace std;
void swap(int&a, int&b)
{
    int prom=a;
    a=b;
    b=prom;
}
int partition (int *a, int p, int r)
{
    int pivot=a[r];
    int i=p-1;
    for (int j=p; j<=r-1; j++)
    {
        if (a[j]<=pivot)
        {
            ++i;
            swap(a[j], a[i]);
        }
    }
    swap(a[i+1], a[r]);
    return (i+1);
}
int rand_partition(int * a,int p,int r)
{
    srand(time(0));
    int i=(rand()%(r-p+1))+p;
    swap(a[r], a[i]);
    return partition(a,p,r);
}

int order_stat_search(int a[], int p, int r, int k)
{
    if (p>=r) return a[p];
    int q=rand_partition(a, p, r);
    int i=q-p+1;
    if (k==i) return a[q];
    else
        if (k<i)
            order_stat_search(a, p, q-1, k);
        else
            order_stat_search(a, q+1, r, k-i);
}
int main()
{
    int a[10];
    srand(time(0));
    for (int i=0; i<=9; i++)
    {
        a[i]=rand()%10;
        cout<<a[i]<<" ";
    }
    cout<<endl;
    for (int i=1; i<=10; i++)
        cout<<i<<" Stat: "<<order_stat_search(a,0,9,i)<<endl;
}

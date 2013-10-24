#include "sort.h"

void isort(int a[], int p, int r)
{
    int i=0;
    for(int j=p+1; j<=r; j++)
    {
        int key=a[j];
        i=j-1;
        while((i>p-1) && (a[i]>key))
        {
            a[i+1]=a[i];
            --i;
        }
        a[i+1]=key;
    }
}

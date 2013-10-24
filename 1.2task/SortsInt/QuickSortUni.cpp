#include "sort.h"
void qs(int a[], int p, int r, const int size)
{
    if (p<r)
    {
        if (r-p+1>size)
        {
            int pivot=rand_partition(a, p, r);
            qs(a,p,pivot-1, size);
            qs(a,pivot+1,r, size);
        }
        else isort(a,p,r);
    }
}

void qihsort(int a[], int p, int r)
{
    int deep=(int)(3*log((double)(r-p+1)));
    qs(a, p, r, deep);
}

#include "sort.h"

void hsortloop(int a[], int p, int r)
{
    build_max_heap(a, p, r);
    int j=0;
    for (int i=r; i>=p+1; i--)
    {
        swap(a[i],a[p]);
        j++;
        heapifyloop(a, p, r-j, 0);
    }
}


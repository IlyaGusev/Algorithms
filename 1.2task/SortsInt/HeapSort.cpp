#include "sort.h"

void hsort(int a[], int p, int r)
{
    build_max_heap(a, p, r);
    int j=0;
    for (int i=r; i>=p+1; i--)
    {
        swap(a[i],a[p]);
        j++;
        heapify(a, p, r-j, 0);
    }
}

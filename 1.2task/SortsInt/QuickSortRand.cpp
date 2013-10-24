#include "sort.h"
void qsortrand (int *a, int p, int r)
{
    if (p<r)
    {
        int pivot=rand_partition(a, p, r);
        qsortrand(a,p,pivot-1);
        qsortrand(a,pivot+1,r);
    }
}

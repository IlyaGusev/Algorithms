#include "sort.h"


void qsortstan (int *a, int p, int r)
{
    if (p<r)
    {
        int pivot=partition(a, p, r);
        if ((pivot-p)<=(r-pivot))
        {
            qsortstan(a,p,pivot-1);
            qsortstan(a,pivot+1,r);
        }
        else
        {
            qsortstan(a,pivot+1,r);
            qsortstan(a,p,pivot-1);
        }
    }
}


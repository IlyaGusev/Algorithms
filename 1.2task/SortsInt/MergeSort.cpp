#include "sort.h"
void merge(int a[], int p, int q, int r)
{
    int * left=(int*)malloc((q-p+1)*sizeof(int));
    int * right=(int*)malloc((r-q)*sizeof(int));
    int j=0;
    for (int i=p; i<=q; i++)
    {
        left[j]=a[i];
        ++j;
    }

    j=0;
    for (int i=q+1; i<=r; i++)
    {
        right[j]=a[i];
        ++j;
    }

    int li=0;
    int ri=0;
    int i=0;
    bool flagl=0;
    while((li<=q-p) || (ri<=r-q-1))
    {
        flagl=0;
        if (li!=q-p+1)
            if ((left[li]<=right[ri]) || (ri==r-q))
            {
                a[i+p]=left[li];
                ++i;
                ++li;
                flagl=1;
            }
        if ((ri!=r-q) && (flagl==0))
            {
                a[i+p]=right[ri];
                ++i;
                ++ri;
            }
    }
    free(left);
    free(right);
}

void msort(int a[], int p, int r)
{
    int q;
    if (p<r)
    {
        q=(p+r)/2;
        msort(a, p, q);
        msort(a, q+1, r);
        merge(a, p, q, r);
    }
}

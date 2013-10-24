#include "sort.h"
void mergeloop(int a[], int p, int q, int r, int left[], int right[])
{
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

}

void msortloop(int a[], int p, int r)
{
    int q=(p+r)/2;
    int add=1;
    while(add<(r-p+1))
        add*=2;
    add/=2;
    int * left=(int*)malloc((add)*sizeof(int));
    int * right=(int*)malloc((r-q)*sizeof(int));
    int part=2;
    int i=0;
    while(p+part<=r)
    {
        i=0;
        while(p+part*i<=r+1)
        {
            if (p+part*(i+1)<=r+1)
                mergeloop(a, p+part*i,(p+part*i+p+part*i+(part-1))/2, p+part*i+(part-1), left, right);
            else
                if ((p+part*i+p+part*i+(part-1))/2<r+1)
                    mergeloop(a, p+part*i, ((p+part*i+p+part*i+(part-1))/2), r, left, right);
            i++;
        }
        part*=2;
    }
    part/=2;
    mergeloop(a, p, p+part-1, r, left, right);
    free(left);
    free(right);
}

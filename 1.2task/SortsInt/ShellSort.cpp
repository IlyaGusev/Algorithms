#include "sort.h"
void ssort(int * a, int p, int r)
{
    int m[13]={1, 4, 10, 23, 57, 132, 301, 701, 1750, 4001, 10001, 32001, 57001};
    for (int i=12; i>=0; i--)
    {
        if ((r-p+1)>m[i])
        for (int begin=p; begin<p+m[i]; begin++)
        {
            for (int j=begin; j<(r-p+1); j+=m[i])
            {
                int mem=j;
                for (int n=j-m[i]; n>=begin ; n-=m[i])
                {
                    if (a[j]>=a[n])
                    {
                        mem=n+m[i];
                        break;
                    }
                }
                if (a[j] < a[begin])
                    mem = begin;
                if (mem != j)
                {               //vstavka
                    int temp = a[j];
                    for (int n=j; n>mem; n-=m[i])
                        a[n] = a[n-m[i]];
                    a[mem] = temp;
                }
            }
        }
    }
}

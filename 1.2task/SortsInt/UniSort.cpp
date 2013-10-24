#include "sort.h"
using namespace std;
void merge_for_uni(int a[], int p, int r,const int claster)
{
    int add=claster;
    while(add<(r-p+1))
        add*=2;
    add/=2;
    int* left=(int*)malloc((add)*sizeof(int));
    int * right=(int*)malloc((add)*sizeof(int));
    int part=claster;
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

void usort(int a[], int p, int r)
{
    int claster=22500; //Осторожно! Магическое число. Найдено эмпирически.
    int min=80;
    if (r-p+1<=min)
        isort(a,p,r);
    else
    if (r-p+1<=claster)
        qihsort(a, p, r);
    else
    {
        for (int i=1; i<=(r-p+1)/claster; i++)
            qihsort(a,p+claster*(i-1), p+claster*i);
        if (((r-p+1)-((int)((r-p+1)/claster))*claster)>0)
            qihsort(a,p+((int)((r-p+1)/claster))*claster, r);
        merge_for_uni(a,p,r,claster);
    }
}

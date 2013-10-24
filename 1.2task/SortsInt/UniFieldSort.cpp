#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <math.h>
#include <time.h>
#include <stdint.h>
#include <string.h>
#include <algorithm>
extern __inline__ uint64_t rdtsc()//Магия для вычисления времени сортировки (в тактах)
{
   uint64_t x;
  __asm__ volatile ("rdtsc\n\tshl $32, %%rdx\n\tor %%rdx, %%rax" : "=a" (x) : : "rdx");
   return x;
}
#define F(i) a[i].first
#define S(i) a[i].second
using namespace std;
typedef pair <int, int> list;

void swap (list &a, list &b)
{
    list t = a;
    a = b;
    b = t;
}
int partition (list *a, int p, int r)
{
    int pivot=a[r].first;
    int i=p-1;
    for (int j=p; j<=r-1; j++)
        if (F(j)<=pivot)
            swap(a[j], a[++i]);
    swap(a[i+1], a[r]);
    return (i+1);
}
void isort(list a[], int p, int r)
{
    int i=0;
    for(int j=p+1; j<=r; j++)
    {
        list key=a[j];
        i=j-1;
        while((i>p-1) && (F(i)>key.first))
        {
            a[i+1]=a[i];
            --i;
        }
        a[i+1]=key;
    }
}

int rand_partition(list * a,int p,int r)
{
    int i=(rand()%(r-p+1))+p;
    swap(a[r], a[i]);
    return partition(a,p,r);
}
void qs(list a[], int p, int r, const int size)
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

void qihsort(list a[], int p, int r)
{
    int deep=(int)(30*log((double)(r-p+1)));
    qs(a, p, r, deep);
}

void mergeloop(list a[], int p, int q, int r, list left[], list right[])
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
            if ((left[li].first<=right[ri].first) || (ri==r-q))
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
void merge_for_uni(list a[], int p, int r,const int claster)
{
    int add=claster;
    while(add<(r-p+1))
        add*=2;
    add/=2;
    list * left=(list*)malloc((add)*sizeof(list));
    list * right=(list*)malloc((add)*sizeof(list));
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

void usort(list a[], int p, int r)
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

int main()
{
    int n;
    cin>>n;
    srand(time(0));
    list* a=(list*)malloc(n*sizeof(list));
    for (int i=0; i<n; i++)
    {
        F(i)=rand()%100;
        S(i)=rand()%100;
    }
    list *b=(list*)malloc(n*sizeof(list));
    memcpy(b,a,n*sizeof(list));
    uint64_t clockb;
    uint64_t clocke;
    clockb=rdtsc();
    usort(b,0,n-1);
    clocke=rdtsc();
    cout<<"UniSort: "<<endl<<clocke-clockb<<endl;
    memcpy(b,a,n*sizeof(list));
    clockb=rdtsc();
    sort(b,b+n);
    clocke=rdtsc();
    cout<<"SortStd: "<<endl<<clocke-clockb<<endl;
    return 0;
}

#include "sort.h"

//Common

void display(int a[], int p, int r)
{
    for (int i=p; i<=r; i++)
        std::cout<<a[i]<<" ";
    std::cout<<std::endl;
}

void display_in_file(int a[], int p, int r)
{
    std::ofstream fout("out.txt");
    for (int i=p; i<=r; i++)
        fout<<a[i]<<" ";
    fout<<std::endl;
    fout.close();
}

void swap(int&a, int&b)
{
    int prom=a;
    a=b;
    b=prom;
}

template <typename DataType>
DataType cmp(DataType * l, DataType * r)
{
    return (*r-*l);
}

int cmp_str(void * a, void * b)
{
    char * ta=(char*)a;
    char * tb=(char*)b;
    int i=0;
    while(1)
    {
        if ((*(ta+i))>(*(tb+i)))
            return 1;
        if ((*(ta+i))<(*(tb+i)))
            return -1;
        if (((*(ta+i))=='\0') && ((*(tb+i))=='\0'))
            return 0;
        i++;
    }
}

//Qsort
int partition (int *a, int p, int r)
{
    int pivot=a[r];
    int i=p-1;
    for (int j=p; j<=r-1; j++)
        if (a[j]<=pivot)
            swap(a[j], a[++i]);
    swap(a[i+1], a[r]);
    return (i+1);
}

int rand_partition(int * a,int p,int r)
{
    int i=(rand()%(r-p+1))+p;
    swap(a[r], a[i]);
    return partition(a,p,r);
}

//Heap
int right(int i)
{
    return (2*i+2);
}

int left(int i)
{
    return (2*i+1);
}

void heapify(int a[], int p, int ri, int i)
{
    int l=left(i)+p;
    int r=right(i)+p;
    int largest=i+p;
    if (l<=ri && a[l]>a[i+p])
        largest=l;
    if (r<=ri && a[r]>a[largest])
        largest=r;
    if (largest!=i+p)
    {
        swap(a[i+p], a[largest]);
        heapify(a, p,ri, largest-p);
    }

}

void heapifyloop(int a[], int p,int ri, int i)
{
    int l=0;
    int r=0;
    int largest=i+p;
    bool flag=1;
    while(flag==1)
    {
        l=left(i)+p;
        r=right(i)+p;
        if (l<=ri && a[l]>a[i+p])
            largest=l;
        if (r<=ri && a[r]>a[largest])
            largest=r;
        flag=0;
        if (largest!=i+p)
        {
            swap(a[i+p], a[largest]);
            i=largest-p;
            flag=1;
        }
    }

}

void build_max_heap(int a[], int p, int r)
{
    int size=r-p+1;
    for (int i=(size)/2-1; i>=0; i--)
        heapify(a,p,r,i);
}

void build_max_heap_loop(int a[], int p, int r)
{
    int size=r-p+1;
    for (int i=(size)/2-1; i>=0; i--)
        heapifyloop(a,p,r,i);
}


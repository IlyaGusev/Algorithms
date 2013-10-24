#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <cstring>
#include <cstdio>
using namespace std;

typedef pair <char*, fpos_t> field;
void swap (field &a, field &b)
{
    field t = a;
    a = b;
    b = t;
}
int partition (field a[], int p, int r, int depth)
{
    char pivot=(a[r].first)[depth];
    int i=p-1;
    for (int j=p; j<=r-1; j++)
        if ((a[j].first)[depth]<=pivot)
        {
            ++i;
            swap(a[j], a[i]);
        }
    swap(a[i+1], a[r]);
    return (i+1);
}
void str_sort(field a[], int p, int r, int depth)
{
    int size=r-p+1;
    if (size <= 1)
        return;
    int q, w;
    int pivot=partition(a, p, r, depth);
    q=w=pivot;
    if (q>=p)
    {
        while((a[q].first)[depth]==(a[pivot].first)[depth])
        {
            q--;
            if (q<p)
                break;
        }
        ++q;
    }
    if (w<=r)
    {
        while((a[w].first)[depth]==(a[pivot].first)[depth])
        {
            w++;
            if (w>r)
                break;
        }
        w--;
    }
    str_sort(a, p, q-1, depth);
    str_sort(a, w+1, r, depth);
    str_sort(a, q, w, depth+1);
    }
/*int main()
{
    srand(time(0));
    int n;
    cin>>n;
    field* list=(field*)malloc(n*sizeof(field));
    for (int i=0 ;i<n; i++)
    {
        list[i].first=(char*)malloc(50*sizeof(char));
        cin>>list[i].first;
        cin>>list[i].second;
    }

    str_sort(list, 0, n-1, 0);

    for (int i=0 ;i<n; i++)
    {
        cout<<list[i].first<<" ";
        cout<<list[i].second<<endl;
    }

    for (int i=0 ;i<n; i++)
    {
        free(list[i].first);
    }
    free(list);
}*/

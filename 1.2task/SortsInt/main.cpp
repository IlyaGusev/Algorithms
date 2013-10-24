#include "sort.h"

using namespace std;

extern __inline__ uint64_t rdtsc()//Магия для вычисления времени сортировки (в тактах)
{
   uint64_t x;
  __asm__ volatile ("rdtsc\n\tshl $32, %%rdx\n\tor %%rdx, %%rax" : "=a" (x) : : "rdx");
   return x;
}

int main()
{
    srand(time(0));
    int n;
    cin>>n;
    int *a=(int*)malloc(n*sizeof(int));
    srand(time(0));
    for (int i=0; i<=n-1; i++)
        a[i]=rand()%1000;

    uint64_t clockb;
    uint64_t clocke;
    int *b=(int*)malloc(n*sizeof(int));

    memcpy(b,a,n*sizeof(int));
    clockb=rdtsc();
    sort(b,b+n);
    clocke=rdtsc();
    cout<<"SortStd: "<<endl<<clocke-clockb<<endl;

    memcpy(b,a,n*sizeof(int));
    clockb=rdtsc();
    usort(b,0,n-1);
    clocke=rdtsc();
    cout<<"Uni: "<<endl<<clocke-clockb<<endl;

    memcpy(b,a,n*sizeof(int));
    clockb=rdtsc();
    ssort(b,0,n-1);
    clocke=rdtsc();
    cout<<"Shell: "<<endl<<clocke-clockb<<endl;

    memcpy(b,a,n*sizeof(int));
    clockb=rdtsc();
    msortloop(b,0,n-1);
    clocke=rdtsc();
    cout<<"MergeLoop: "<<endl<<clocke-clockb<<endl;

    memcpy(b,a,n*sizeof(int));
    clockb=rdtsc();
    qsortstan(b,0,n-1);
    clocke=rdtsc();
    cout<<"QuickStandart: "<<endl<<clocke-clockb<<endl;

    memcpy(b,a,n*sizeof(int));
    clockb=rdtsc();
    qihsort(b,0,n-1);
    clocke=rdtsc();
    cout<<"QuickUni: "<<endl<<clocke-clockb<<endl;

    memcpy(b,a,n*sizeof(int));
    clockb=rdtsc();
    hsortloop(b,0,n-1);
    clocke=rdtsc();
    cout<<"HeapLoop: "<<endl<<clocke-clockb<<endl;

    memcpy(b,a,n*sizeof(int));
    clockb=rdtsc();
    isort(b,0,(n));
    clocke=rdtsc();
    cout<<"Insertion: "<<endl<<clocke-clockb<<endl;
}

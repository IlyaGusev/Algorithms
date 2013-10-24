#include <time.h>
#include "apar.h"
using namespace std;

extern __inline__ uint64_t rdtsc()//Магия для вычисления времени(в тактах)
{
   uint64_t x;
  __asm__ volatile ("rdtsc\n\tshl $32, %%rdx\n\tor %%rdx, %%rax" : "=a" (x) : : "rdx");
   return x;
}


int main()
{
    LongNum a, b;
    //int c;
    //uint64_t clockb;
    //uint64_t clocke;
    time_t t1;
    time_t t2;
    //clockb=rdtsc();
    t1=time(0);
    cout<<(LongNum(2)^300000)<<endl;
    t2=time(0);
    //clocke=rdtsc();
    //cout<<(clocke-clockb)/1000000<<endl;
    cout<<t2-t1<<endl;
    return 0;
}

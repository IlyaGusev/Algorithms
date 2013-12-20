#ifndef SPEEDTEST_H_INCLUDED
#define SPEEDTEST_H_INCLUDED

#include <gtest/gtest.h>
#include <iostream>
using std::cout;
using std::endl;
namespace my{
    extern __inline__ uint64_t rdtsc()//Магия для вычисления времен (в тактах)
    {
       uint64_t x;
      __asm__ volatile ("rdtsc\n\tshl $32, %%rdx\n\tor %%rdx, %%rax" : "=a" (x) : : "rdx");
       return x;
    }
    class SpeedTest : public ::testing::Test {
        private:
            uint64_t clockb;
            uint64_t clocke;
        protected:
            SpeedTest() { clockb=rdtsc(); }
            virtual ~SpeedTest() { clocke=rdtsc(); cout<<"Time: "<<(clocke-clockb)/1000<<endl; }
            virtual void SetUp() {}
            virtual void TearDown() {}
    };
}


#endif // SPEEDTEST_H_INCLUDED

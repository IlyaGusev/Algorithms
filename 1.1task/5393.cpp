#include <iostream>
#include <math.h>
using namespace std;
int main()
{
    int n;
    cin>>n;
    bool prost=true;
    for (int i=2; i<=(int)(sqrt((double)n));i++)
    {
        if (n%i==0) prost=false;
    }
    cout<<prost;
}

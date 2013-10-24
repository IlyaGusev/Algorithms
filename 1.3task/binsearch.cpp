#include <iostream>
using namespace std;
int bin_search(int a[], int first, int last, int selem)
{
    int mid;
    while(first<last)
    {
        mid=first+(last-first)/2;
        if (selem<=a[mid])
            last=mid;
        else
            first=mid+1;
    }
    if (a[last]==selem)
        return last;
    else
        return 0;
}
int main()
{
    int a[]={1,2,4,5,5,6,7,10,14,23};
    cout<<bin_search(a, 0,9,10);
}

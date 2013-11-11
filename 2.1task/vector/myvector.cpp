#include <iostream>
#include "myvector.h"
#include "myboolvector.h"
#include <algorithm>
#include <time.h>
#include <cstdio>
#include <stdlib.h>
using namespace std;
int main()
{
    /*srand(time(0));
    using my::vector;
    using my::bit;
    vector<int> v=vector<int>(30, 20);
    for (int i=0; i<v.size(); i++)
        v[i]=i;
    while(1)
    {
        random_shuffle(v.begin(), v.end());
        for (int i=0; i<v.size(); i++)
            cout<<v[i]<<" ";
        getchar();
        system("clear");
    }*/
    using my::vector;
    vector<bool> a(31);
    a[0]=1;
    a[28]=1;
    a[30]=1;

    for (int i=0; i<a.size();i++){
        cout<<a[i];
    }
    cout<<endl;

    for (auto i : a)
        cout<<i;
    cout<<endl;
    auto it=a.begin();
    auto it2=a.end();
    cout<<(*it)<<" "<<(*it2)<<endl;
    cout<< (it2-it)<<endl;


}

#include <iostream>

#include <math.h>
using namespace std;
int main()
{
    setlocale(LC_CTYPE, "");
    cout<<"������� ���������� �����:"<<endl;
    int n;
    cin>>n;
    cout<<"������� �����:"<<endl;
    int * p=(int *)malloc(sizeof(int)*n);
    double sum=0;
    int min=2147483647;
    int max=-2147483647;
    for (int i=0; i<n; i++)
    {
        cin>>p[i];
        sum+=p[i];
        if (p[i]<min) min=p[i];
        if (p[i]>max) max=p[i];
    }
    double mid=0;
    mid=sum/n;
    double dispersion=0;
    for (int i=0; i<n; i++)
    {
        dispersion+=(mid-p[i])*(mid-p[i]);
    }
    dispersion/=(n*(n-1));
    double stddev=sqrt(dispersion);
    cout<<"�������: "<<mid<<endl;
    cout<<"�����������: "<<min<<endl;
    cout<<"������������: "<<max<<endl;
    cout<<"���������: "<<dispersion<<endl;
    cout<<"����������� ����������: "<<stddev<<endl;
    return 0;
}

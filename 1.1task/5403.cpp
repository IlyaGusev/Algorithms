#include <iostream>
#include <math.h>
using namespace std;
double KahanSum(double* ptr, int len)
{
    double sum=0;
    double c=0;
    double y=0, t=0;
    for (int i=0; i<len; i++)
    {
        y=ptr[i]-c;
        t=sum+y;
        c=(t-sum)-y;
        sum=t;
    }
    return sum;
}
double StandartSum(double *ptr, int len)
{
    double sum=0;
    for (int i=0; i<len; i++)
        sum+=ptr[i];
    return sum;
}
int main()
{
    setlocale(LC_CTYPE, "");
    cout<<"Введите количество чисел:"<<endl;
    int n;
    cin>>n;
    cout<<"Введите числа:"<<endl;
    double* p=(double*) malloc(sizeof(double)*n);
    for (int i=0; i<n; i++)
        cin>>p[i];
    cout<<"Сумма по Кахану: "<<KahanSum(p,n)<<endl;
    cout<<"Сумма стандартно: "<<StandartSum(p,n)<<endl;
    cout<<"Разница: "<<(-KahanSum(p,n)+StandartSum(p,n));
    return 0;
}

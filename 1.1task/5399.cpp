#include <iostream>
using namespace std;
int len(char a[])
{
    int i=0;
    while(a[i]!='\0')
        i++;
    return i;
}
int main()
{
    char a[100];
    cin>>a;
    int n=0;
    for (int i=0; i<len(a); i++)
    {
        if (a[i]=='(') n++;
        if (a[i]==')') n--;
        if (n<0) { break;}
    }
    if (n==0) cout<<"YES";
    else cout<<"NO";
    return 0;
}

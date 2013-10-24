#include <iostream>
#include <cstdlib>
using namespace std;
int len(char c[])
{
    int i=0;
    while(c[i]!='\0')
        i++;
    return i;
}
char** split(char *str, char *delim)
{
    char** lines=new char *[100];
    for (int i=0;i<100;i++)
        lines[i]=new char[100];
    bool flag=true;
    int i=0;
    int index=0;
    flag=false;
    int prom=0;
    while(str[i]!='\0') {
        while(str[i]!='\0')
        {
            flag=true;
            for (int j=i; j<=i+len(delim)-1; ++j)
                if (delim[j-i]!=str[j]) flag=false;
            if (flag==true) break;
            ++i;
        }
        int j;
        for (j=prom; j<=i-1; j++)
            lines[index][j-prom]=str[j];
        lines[index][i-prom]='\0';
        prom=j+1;
        index++;
        i++;
        if (flag==false)
            break;
    }
    lines[index]='\0';
    return lines;
}
void delete_string_array(char **str)
{
    for(int i=0 ; i<100 ;i++)
        delete[]str[i];
    delete[]str;
}
int main()
{
    char str[1000];
    char delim[1000];
    cin>>str>>delim;
    char** lines=split(str, delim);
    int i=0;
    while(lines[i]!='\0')
        cout<<lines[i++]<<endl;
    int a;
    delete_string_array(lines);
    return 0;
}

#include <iostream>
#include <cstdlib>
#include <vector>
#include <conio.h>
using namespace std;
int len(char a[])
{
    int i=0;
    while(a[i]!='\0')
        i++;
    return i;
}
char* concat(char a[], char b[])
{
    int k;
    int l=len(a)+1;
    a[len(a)]=' ';
    for (k=0; k<len(b); k++)
        a[l+k]=b[k];
    a[l+k]='\0';
    return a;
}
int strcompare(char a[], char b[])
{
    int i=0;
    while(1)
    {
        if (a[i]>b[i]) return -1;
        if (a[i]<b[i]) return 1;
        i++;
        if (a[i]=='\0' && b[i]=='\0')
            return 0;
    }
}
struct Student
{
    char name[32];
    int mark;
};
void swap(char *a, char *b, int &an, int &bn)
{
    char c[100];
    int i=0;
    while(a[i]!='\0')
    {
        c[i]=a[i];
        i++;
    }
    c[i]='\0';
    memcpy(a,b,sizeof(char)*len(b));
    a[len(b)]='\0';

    memcpy(b,c,sizeof(char)*len(c));
    b[len(c)]='\0';

    int temp;
    temp=an;
    an=bn;
    bn=temp;
}
void bub_sort(vector<Student> &students, int l)
{
    for (int i=l-1; i>=1; i--)
        for (int j=1; j<=i; j++)
        {
            if (strcompare(students[j-1].name, students[j].name)<=0)
            {
                swap(students[j-1].name, students[j].name,
                     students[j-1].mark, students[j].mark);
            }
        }
}
int bin_search(vector<Student> &students, int last, char compr[])
{
    int mid;
    int first=0;
    while(first<last)
    {
        mid=first+(last-first)/2;
        if (strcompare(compr, students[mid].name)>=0)
            last=mid;
        else
            first=mid+1;
    }
    if (strcompare(compr, students[last].name)==0)
        return last;
    else
        return -1;
}
int main()
{
    setlocale(LC_CTYPE, "");
    int n,a;
    cout<<"Введите количество студентов:"<<endl;
    cin>>n;
    cout<<"Вводите данные студентов в формате Номер-студака_Фамилия_И.О._Оценка:"<<endl;
    vector<Student> students(n);
    char sf[32];
    char ss[32];
    for (int i=0 ;i<=n-1; i++)
    {
        cin>>a>>sf>>ss>>students[i].mark;
        char* temp=concat(sf,ss);
        for (int j=0; j<=len(temp);j++)
        {
            students[i].name[j]=temp[j];
        }
    }
    bub_sort(students, n);
    int m;
    cout<<"Введите количество планируемых запросов:"<<endl;
    cin>>m;
    char *c;
    for (int i=0 ;i<=m-1; i++)
    {
        cout<<"Введите ФИО студента: ";
        cin>>sf>>ss;
        c=concat(sf,ss);
        int j=bin_search(students, n-1, c);
        if (j==-1)
            cout<<"Студент не найден"<<endl;
        else
            cout<<"Оценка студента: "<<students[j].mark<<endl;
    }
    return 0;
}

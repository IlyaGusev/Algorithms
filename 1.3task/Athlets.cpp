#include <iostream>
#include <cstdlib>
struct Athlete
{
    int m;
    int s;
};

Athlete* find_max_tower(Athlete* a, int n)
{
    Athlete * answer= (Athlete*) malloc((2)*sizeof(Athlete));
    long long int cur_sum=a[0].m;
    int cur_at=1;
    answer[1]=a[0];
    int j=2;
    while(cur_at<=n-1)
    {
        while (cur_sum>a[cur_at].s && cur_at<=n-1)
            cur_at++;
        if (cur_at<=n-1)
        {
            answer= (Athlete*) realloc(answer,(j+1)*sizeof(Athlete));
            cur_sum+=a[cur_at].m;
            answer[j]=a[cur_at];
            j++;
        }
        cur_at++;
    }
    answer=(Athlete*)realloc(answer, j*sizeof(Athlete));
    answer[0].m=j-1;
    return answer;
}
int compare (const void * a, const void * b)
{
  return ( (*(Athlete*)a).s - (*(Athlete*)b).s);
}
using namespace std;
int main()
{
    int n;
    cin>>n;

    Athlete *a=(Athlete*)malloc(n*sizeof(Athlete));
    for (int i=0; i<=n-1; i++)
        cin>>a[i].m>>a[i].s;

    qsort (a, n, sizeof(Athlete), compare);

    Athlete* b=find_max_tower(a, n);
    cout<<b[0].m<<endl;

    free(b);
    free(a);
    return 0;
}

#include <iostream>
#include <cstdlib>
using namespace std;
int max_index(int a[], int p, int r)
{
    int maxi=p;
    for (int i=p; i<=r; i++)
        if (a[i]>=a[maxi])
            maxi=i;
    return maxi;
}
int * LIS (int a[], int p, int r)
{
    int * pred= (int*) malloc((r-p+1)*sizeof(int));
    int * length= (int*) malloc((r-p+1)*sizeof(int));
    for (int i=0; i<=r-p; i++)
    {
        pred[i]=0;
        length[i]=1;
    }
    for (int i=p; i<=r; i++)
        for (int j=i+1; j<=r; j++)
            if (a[i]<a[j])
                if (length[i-p]+1>length[j-p])
                {
                    length[j-p]=length[i-p]+1;
                    pred[j-p]=i;
                }
    for (int i=0; i<=r-p; i++)
        cout<<pred[i]<<" ";
    cout<<endl;
    for (int i=0; i<=r-p; i++)
        cout<<length[i]<<" ";
    cout<<endl;

    int max=max_index(length, 0,(r-p));
    int * answer= (int*) malloc((length[max]+1)*sizeof(int));
    int temp=max;
    answer[(length[max])]=a[temp+p];
    for (int i=(length[max])-1; i>=1; i--)
    {
        temp=pred[temp];
        answer[i]=a[temp+p];
    }
    answer[0]=length[max];

    free(length);
    free(pred);
    return answer;
}

int main()
{
    cout<<"Enter X length: ";
    int n;
    cin>>n;
    cout<<"Enter X: ";
    int *x=(int*)malloc(n*sizeof(int));
    for (int i=0; i<=n-1; i++)
        cin>>x[i];

    int *b;
    b=LIS(x,0,n-1);
    cout<<"LIS: ";
    for (int i=1; i<=b[0]; i++)
        cout<<b[i]<<" ";
    free(x);
    free(b);
    return 0;
}

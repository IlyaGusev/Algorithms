#include <iostream>
#include <cstdlib>
using namespace std;
int min(int a, int b, int c)
{
    int min=a;
    if (b<a)
        min=b;
    if (c<min)
        min=c;
    return min;
}
int min(int a, int b, int c, int d)
{
    int min=a;
    if (b<a)
        min=b;
    if (c<min)
        min=c;
    if (d<min)
        min=d;
    return min;
}
int * get_prices()
{
    int* prices=(int*)malloc(6*sizeof(int));
    cout<<"Copy: ";
    cin>>prices[0];
    cout<<"Exchange: ";
    cin>>prices[1];
    cout<<"Delete: ";
    cin>>prices[2];
    cout<<"Insert: ";
    cin>>prices[3];
    cout<<"Replase: ";
    cin>>prices[4];
    cout<<"Balance: ";
    cin>>prices[5];
    return prices;
}
int** create_map(char x[], char y[], int xl, int yl, int prices[])
{
    int** map=(int**)malloc((xl+1)*sizeof(int*));
    for (int i=0; i<=xl; i++)
        map[i]=(int*)malloc((yl+1)*sizeof(int));
    map[0][0]=0;
    for (int j=1; j<=yl; j++)
        map[0][j]=map[0][j-1]+prices[3];

    for (int i=1; i<=xl; i++)
    {
        map[i][0]=map[i-1][0]+prices[2];
        for (int j=1; j<=yl; j++)
        {
            if (x[i-1]==y[j-1])
                if (i>=3 && j>=3)
                    if (x[i-3]==y[j-2] && x[i-2]==y[j-3])
                        map[i][j]=min(map[i-1][j]+prices[2], map[i][j-1]+prices[3], map[i-1][j-1]+prices[0], map[i-2][j-2]+prices[4]);
                    else
                        map[i][j]=min(map[i-1][j]+prices[2], map[i][j-1]+prices[3], map[i-1][j-1]+prices[0]);
                else
                    map[i][j]=min(map[i-1][j]+prices[2], map[i][j-1]+prices[3], map[i-1][j-1]+prices[0]);
            else
                if (i>=3 && j>=3)
                    if (x[i-3]==y[j-2] && x[i-2]==y[j-3])
                        map[i][j]=min(map[i-1][j]+prices[2], map[i][j-1]+prices[3], map[i-1][j-1]+prices[1], map[i-2][j-2]+prices[4]);
                    else
                        map[i][j]=min(map[i-1][j]+prices[2], map[i][j-1]+prices[3], map[i-1][j-1]+prices[1]);
                else
                    map[i][j]=min(map[i-1][j]+prices[2], map[i][j-1]+prices[3], map[i-1][j-1]+prices[1]);
        }
    }
    return map;

}
int main()
{
    int* prices=get_prices();

    int xl, yl;
    cout<<"Enter X length: ";
    cin>>xl;
    cout<<"Enter Y length: ";
    cin>>yl;
    cout<<"Enter X: ";
    char *x=(char*)malloc((xl+1)*sizeof(char));
        cin>>x;
    cout<<"Enter Y: ";
    char *y=(char*)malloc((yl+1)*sizeof(char));
        cin>>y;
    int**map=create_map(x,y,xl,yl,prices);
    cout<<"Conversion map: "<<endl;
    for (int i=0; i<=xl; i++)
    {
        for (int j=0; j<=yl; j++)
        {
            if (map[i][j]<10)
                cout<<map[i][j]<<"  ";
            else cout<<map[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    int edit_distance=map[xl][yl];
    for (int i=0; i<xl; i++)
        if (map[i][yl]+prices[5]<edit_distance)
            edit_distance=map[i][yl]+prices[5];
    cout<<"Edit distance: "<<edit_distance;
    free(x);
    free(y);
    for (int i=0; i<=xl; i++)
        free(map[i]);
    free(map);
    return 0;
}

#include <iostream>
#include <cstdlib>
using namespace std;
struct table
{
    int length;
    int direction; //0-diag, 1-left, 2-up
};
table** LCS_build(char x[], char y[], int xl, int yl)
{
    table** map=(table**)malloc((xl+1)*sizeof(table*));
    for (int i=0; i<=xl; i++)
        map[i]=(table*)malloc((yl+1)*sizeof(table));

    for (int i=0; i<=xl; i++)
        map[i][0].length=0;
    for (int j=0; j<=yl; j++)
        map[0][j].length=0;

    for (int i=1; i<=xl; i++)
        for (int j=1; j<=yl; j++)
        {
            if (x[i-1]==y[j-1])
            {
                map[i][j].length=map[i-1][j-1].length+1;
                map[i][j].direction=0;
            }
            else
                if (map[i-1][j].length>=map[i][j-1].length)
                {
                    map[i][j].length=map[i-1][j].length;
                    map[i][j].direction=2;
                }
                else
                {
                    map[i][j].length=map[i][j-1].length;
                    map[i][j].direction=1;
                }
        }
    for (int i=1; i<=xl; i++)
    {
        for (int j=1; j<=yl; j++)
        {
            cout<<map[i][j].length<<"|"<<map[i][j].direction<<" ";
        }
        cout<<endl;
    }
    return map;
}
void print_LCS(table ** map, char x[], int i, int j)
{
    if (i==0 || j==0)
        return;
    if (map[i][j].direction==0)
    {
        print_LCS(map, x, i-1, j-1);
        cout<<x[i-1]<<" ";
    }
    else
        if(map[i][j].direction==2)
            print_LCS(map,x,i-1,j);
        else print_LCS(map,x,i,j-1);
}
using namespace std;
int main()
{
    cout<<"Enter X & Y length: ";
    int xl, yl;
    cin>>xl>>yl;
    cout<<"Enter X: ";
    char *x=(char*)malloc(xl*sizeof(int));
    for (int i=0; i<=xl-1; i++)
        cin>>x[i];
    cout<<"Enter Y: ";
    char *y=(char*)malloc(yl*sizeof(int));
    for (int i=0; i<=yl-1; i++)
        cin>>y[i];

    table ** map=LCS_build(x,y,xl,yl);
    cout<<"LCS: ";
    print_LCS(map, x, xl, yl);
    cout<<endl;
    for (int i=0; i<=xl; i++)
        free(map[i]);
    free(map);
    return 0;
}

#include <iostream>
#include <string>
#include <vector>
#include <string.h>
#include <cstring>
#include <algorithm>

using namespace std;

const int pos[16][2] =
{
    {3, 3}, {0, 0}, {0, 1}, {0, 2},
    {0, 3}, {1, 0}, {1, 1}, {1, 2},
    {1, 3}, {2, 0}, {2, 1}, {2, 2},
    {2, 3}, {3, 0}, {3, 1}, {3, 2}
};

const int dx[4] = { 0, 1, 0,-1};
const int dy[4] = {-1, 0, 1, 0};
const char c[4] = {'L','D','R','U'};
const int rev[4]= {2, 3, 0, 1};

struct board
{
    int a[4][4];
    void print(){
        for (int i=0; i<4; i++){
            for (int j=0; j<4; j++)
                cout<<a[i][j]<<" ";
            cout<<endl;
        }
        cout<<endl;
    }
};

int d[4][4][4][4];
vector <char> res;

board BD;
bool have_answer;

int max_dist;

int ab(int x) {return x >= 0 ? x : -x;}

void calc_d()
{
    for (int i = 0; i < 4; i ++)
        for (int j = 0; j < 4; j ++)
            for (int r = 0; r < 4; r ++)
                for (int s = 0; s < 4; s ++)
                    d[i][j][r][s] = ab(r - i) + ab(s - j);
}

int dist(board X)
{
    int res = 0;
    for (int i = 0; i < 4; i ++)
        for (int j = 0; j < 4; j ++)
            if (X.a[i][j] != 0) res += d[i][j][pos[X.a[i][j]][0]][pos[X.a[i][j]][1]];
    return res;
}

bool val(int p, int q)
{
    if (p >= 0 && q >= 0 && p < 4 && q < 4) return true;
    return false;
}

void rec(int g, int x0, int y0, int prev)
{
    if (have_answer) return;
    int h = dist(BD);
    if (h == 0)
    {
        for (int i = 0; i < res.size(); i ++) printf("%c", res[i]);
        printf("\n");
        have_answer = true;
        return;
    }
    if (g + h > max_dist) return;

    for (int i = 0; i < 4 && !have_answer; i ++)
        if (val(x0 + dx[i], y0 + dy[i]) && rev[i] != prev)
        {
            swap(BD.a[x0][y0], BD.a[x0 + dx[i]][y0 + dy[i]]);
            cout<<h<<endl;
            BD.print();
            res.push_back(c[i]);
            rec(g + 1, x0 + dx[i], y0 + dy[i], i);
            res.pop_back();
            swap(BD.a[x0][y0], BD.a[x0 + dx[i]][y0 + dy[i]]);
        }
}

bool solution()
{
    int sum = 0;
    int a[16], k = -1;
    for (int i = 0; i < 4; i ++)
        for (int j = 0; j < 4; j ++)
            k ++, a[k] = BD.a[i][j];
    for (int i = 0; i < 16; i ++)
        for (int j = i; j < 16; j ++)
            if (a[j] != 0 && a[j] < a[i]) sum ++;
    for (int i = 0; i < 4; i ++)
        for (int j = 0; j < 4; j ++)
            if (BD.a[i][j] == 0) sum += i + 1;

    return (sum % 2) ? false : true;
}

void solve()
{
    for (int i = 0; i < 4; i ++)
        for (int j = 0; j < 4; j ++)
            scanf("%d", &BD.a[i][j]);

    if (!solution())
    {
        printf("This puzzle is not solvable.\n");
        return;
    }

    res.resize(0);
    have_answer = false;
    int x0, y0;
    for (int i = 0; i < 4; i ++)
        for (int j = 0; j < 4; j ++)
            if (BD.a[i][j] == 0) x0 = i, y0 = j;

    int s = dist(BD);
    for (int i = s; i <= 50 && !have_answer; i ++)
    {
        max_dist = i;
        rec(0, x0, y0, -1);
    }

    if (!have_answer)
    {
        printf("No solutions found.\n");
    }
}

int main()
{
    calc_d(); int t;
    scanf("%d", &t);
    for (int it = 1; it <= t; it ++) solve();
    return 0;
}

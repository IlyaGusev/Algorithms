#include "sort.h"
using namespace std;
bool is_correct(const char b[])
{
    fstream file;
    file.open(b, ios::in);
    int x, y, r = 1;
    file >> x;
    while (file >> y)
    {
        if (x > y) return false;
        x = y;
        r++;
        if (r % 1000000 == 0) cout << r << endl;
    }
    file.close();
    return 1;

}

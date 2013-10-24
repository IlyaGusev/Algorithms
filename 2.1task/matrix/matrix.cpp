#include "matrix.h"
int main()
{
    Matrix<int> m("identity",3,3);
    Matrix<int> n(2, 2, 2);
    cin>>n;

    cout<<n.inverse()<<endl;
    return 0;
}

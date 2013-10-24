#include "rbtree.h"
int main()
{
    RBtree<int> test;


    for (int i=0; i<3000000; i++)
    {
        test.insert(i);

    }
    for (int i=0; i<2999998; i++)
        test.remove(test.max(test.getRoot()));
    test.show(test.getRoot());
}

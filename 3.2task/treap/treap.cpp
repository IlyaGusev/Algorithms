#include <iostream>
#include "treap.h"

namespace {
    class TreapTest : public ::testing::Test {
    public:
    protected:
        TreapTest(){}
        virtual ~TreapTest() {}
        virtual void SetUp() {}
        virtual void TearDown() {}
    };
    TEST_F(TreapTest, BuildTest1){
        Treap<int, int> treap;
        vector<int> d(6);
        d[0] = 20;
        d[1] = 4;
        d[2] = 2;
        d[3] = 8;
        d[4] = 6;
        d[5] = 0;
        treap.build(d);
        EXPECT_EQ(treap.root()->priority(), 0);
        EXPECT_EQ(treap.root()->left()->priority(), 2);
        EXPECT_EQ(treap.root()->left()->left()->priority(), 4);
        EXPECT_EQ(treap.root()->left()->left()->left()->priority(), 20);
        EXPECT_EQ(treap.root()->left()->right()->priority(), 6);
        EXPECT_EQ(treap.root()->left()->right()->left()->priority(), 8);
    }
    TEST_F(TreapTest, MergeTest1){
        Treap<int, int> treap1;
        vector<int> d(5);
        d[0] = 20;
        d[1] = 4;
        d[2] = 2;
        d[3] = 8;
        d[4] = 6;
        treap1.build(d);

        Treap<int, int> treap2;
        vector<int> f(5);
        f[0] = 21;
        f[1] = 5;
        f[2] = 3;
        f[3] = 9;
        f[4] = 7;
        treap2.build(f);

        treap1.merge(treap2);
        treap1.print();
    }
    TEST_F(TreapTest, SplitTest1){
        Treap<int, int> treap;
        vector<int> d(5);
        d[0] = 20;
        d[1] = 4;
        d[2] = 2;
        d[3] = 8;
        d[4] = 6;
        treap.build(d);

        treap.split(1);
        treap.print(treap.root()->left());
        treap.print(treap.root()->right());
    }
    TEST_F(TreapTest, InsertTest1){
        Treap<int, int> treap;
        treap.insert(0, 20);
        EXPECT_EQ(treap.root()->priority(), 20);
        EXPECT_EQ(treap.root()->key(), 0);
        treap.insert(1, 30);
        treap.insert(-1, 1);
        treap.insert(20, 4);
        treap.insert(-2, 0);
        EXPECT_EQ(treap.root()->right()->right()->left()->priority(), 20);
        EXPECT_EQ(treap.root()->right()->right()->left()->right()->priority(), 30);
        treap.insert(21, 5);
        treap.print();
    }
    TEST_F(TreapTest, EraseTest1){
        Treap<int, int> treap;
        treap.insert(0, 20);
        treap.insert(0, 30);
        treap.insert(0, 1);
        treap.insert(1, 4);
        treap.insert(1, 2);
        treap.insert(-1, 90);
        treap.insert(-1, 100);
        treap.erase(0);
        treap.print();
    }
    TEST_F(TreapTest, MinimumTest1){
        Treap<int, int> treap;
        treap.insert(1, 20);
        treap.insert(2, 30);
        treap.insert(-1, 1);
        treap.insert(-2, 4);
        treap.insert(0, 2);
        treap.insert(20, 90);
        treap.insert(-100, 100);
        treap.erase(-100);
        treap.insert(-90, 100);
        EXPECT_EQ(treap.minimum()->key(), -90);
        EXPECT_EQ(treap.root()->priority(), 1);
        treap.print();
    }
}

int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

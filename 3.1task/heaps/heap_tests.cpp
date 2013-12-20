#include <iostream>
#include <gtest/gtest.h>
#include <pthread.h>
#include "../speedtest/speedtest.h"
#include "binheap/binheap.h"
#include "fibheap/fibheap.h"
#define Heap BinHeap
namespace {
    class HeapIntTest : public my::SpeedTest {
    protected:
        Heap<int> heap;
        HeapIntTest() : SpeedTest() {}
        virtual ~HeapIntTest() {}
        virtual void SetUp() {
            heap.insert(3);
            heap.insert(4);
            heap.insert(8);
            heap.insert(5);
        }
        virtual void TearDown() {}
    };

    TEST_F(HeapIntTest, InsertAndMinimumTest) {
        EXPECT_EQ(3, heap.minimum()->first());
        heap.insert(2);
        EXPECT_EQ(2, heap.minimum()->first());
        heap.insert(8);
        heap.insert(10);
        heap.insert(1);
        EXPECT_EQ(1, heap.minimum()->first());
        heap.insert(1);
        EXPECT_EQ(1, heap.minimum()->first());
        heap.insert(-100);
        EXPECT_EQ(-100, heap.minimum()->first());
    }
    TEST_F(HeapIntTest, ExtractMinimumTest) {
        EXPECT_EQ(3, heap.extract_minimum()->first());
        heap.insert(7);
        EXPECT_EQ(4, heap.extract_minimum()->first());
        heap.insert(2);
        EXPECT_EQ(2, heap.extract_minimum()->first());
        heap.insert(1);
        EXPECT_EQ(1, heap.extract_minimum()->first());
        heap.insert(-5);
        EXPECT_EQ(-5, heap.extract_minimum()->first());

        heap.extract_minimum();
        heap.extract_minimum();
        heap.extract_minimum();
        ASSERT_THROW(heap.extract_minimum(), logic_error);
    }
    TEST_F(HeapIntTest, DecreaseKeyTest) {
        heap.decrease_key(heap.minimum(), 2);
        EXPECT_EQ(2, heap.minimum()->first());
        auto node = heap.minimum();
        heap.insert(0);
        heap.insert(-2);
        heap.insert(10);
        heap.insert(-1);
        heap.decrease_key(node, 1);
        heap.extract_minimum();
        heap.extract_minimum();
        heap.extract_minimum();
        EXPECT_EQ(1, heap.minimum()->first());

        ASSERT_THROW(heap.decrease_key(nullptr, 3), logic_error);
    }
    TEST_F(HeapIntTest, EraseTest) {
        heap.erase(heap.minimum());
        heap.erase(heap.minimum());
        heap.erase(heap.minimum());
        EXPECT_EQ(8, heap.minimum()->first());
        heap.erase(heap.minimum());

        ASSERT_THROW(heap.erase(heap.minimum()), logic_error);
    }
    TEST_F(HeapIntTest, Test) {
        for(int i=1; i<200000; i++)
            heap.insert(2*i);
        //heap.print();
    }
}

int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#include <iostream>
#include <string>
#include "rmq.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

vector<int> speed_data;
RMQ<int, less<int>, SegmentTree<int>>  speed_STR;
RMQ<int, less<int>, SqrtDecomposition<int>> speed_SQR;
RMQ<int, less<int>, FKB<int>> speed_FKB;
const int cases_n = 100000000;
const int speed_s = 10000000;
int cases1[cases_n];
int cases2[cases_n];
namespace {
    class RMQTest : public my::SpeedTest {
    protected:
        RMQTest(){}
        virtual ~RMQTest() {}
        static void SetUpTestCase() {
            srand(time(0));
            speed_data = vector<int>(speed_s);
            for (int i=0; i<(int)speed_data.size(); i++)
                speed_data[i] = rand()%1000000+1;
            int j, i;
            for (int k=0; k<cases_n; k++){
                j = rand()%(speed_s-1)+1;
                i = rand()%j+1;
                cases1[k] = i;
                cases2[k] = j;
            }
            speed_STR = RMQ<int, less<int>, SegmentTree<int>>(speed_data);
            speed_SQR = RMQ<int, less<int>, SqrtDecomposition<int>>(speed_data);
            speed_FKB = RMQ<int, less<int>, FKB<int>>(speed_data);
        }
        virtual void TearDown() {}
    };
    TEST_F(RMQTest, SQRTDTest1){
        vector<int> data(20);
        for (int i=0; i<20; i++)
            data[i] = i;
        RMQ<int> rmq(data);
        EXPECT_EQ(4, rmq.find(4, 11));
        EXPECT_EQ(0, rmq.find(0, 5));
        EXPECT_EQ(4, rmq.find(4, 6));
        EXPECT_EQ(0, rmq.find(0, 19));
        EXPECT_EQ(10, rmq.find(10, 19));
        EXPECT_EQ(15, rmq.find(15, 16));
    }
    TEST_F(RMQTest, SQRTDTest2){
        vector<int> data(10);
        data[0] = 3;
        data[1] = 8;
        data[2] = 6;
        data[3] = 4;
        data[4] = 2;
        data[5] = 5;
        data[6] = 9;
        data[7] = 0;
        data[8] = 7;
        data[9] = 1;
        RMQ<int> rmq(data);
        EXPECT_EQ(2, rmq.find(1, 6));
        EXPECT_EQ(0, rmq.find(1, 7));
        EXPECT_EQ(1, rmq.find(8, 9));
        EXPECT_EQ(2, rmq.find(0, 4));
        EXPECT_EQ(0, rmq.find(0, 9));
    }
    TEST_F(RMQTest, SQRTDTest3){
        vector<int> data(10);
        data[0] = 21;
        data[1] = 99;
        data[2] = 1;
        data[3] = 2;
        data[4] = 3;
        data[5] = 51;
        data[6] = 60;
        data[7] = 77;
        data[8] = 7;
        data[9] = 2;
        RMQ<int, less<int>, SqrtDecomposition<int> > rmq(data);
        EXPECT_EQ(21, rmq.find(0, 1));
        EXPECT_EQ(1, rmq.find(1, 4));
        rmq.change(1, -1);
        EXPECT_EQ(-1, rmq.find(0, 1));
        EXPECT_EQ(-1, rmq.find(1, 4));
    }
    TEST_F(RMQTest, STRTest1){
        vector<int> data(10);
        data[0] = 3;
        data[1] = 8;
        data[2] = 6;
        data[3] = 4;
        data[4] = 2;
        data[5] = 5;
        data[6] = 9;
        data[7] = 0;
        data[8] = 7;
        data[9] = 1;
        RMQ<int, less<int>, SegmentTree<int> > rmq(data);
        EXPECT_EQ(2, rmq.find(1, 6));
        EXPECT_EQ(0, rmq.find(1, 7));
        EXPECT_EQ(1, rmq.find(8, 9));
        EXPECT_EQ(2, rmq.find(0, 4));
        EXPECT_EQ(0, rmq.find(0, 9));
    }
    TEST_F(RMQTest, STRTest2){
        vector<int> data(10);
        data[0] = 21;
        data[1] = 99;
        data[2] = 1;
        data[3] = 2;
        data[4] = 3;
        data[5] = 51;
        data[6] = 60;
        data[7] = 77;
        data[8] = 7;
        data[9] = 2;
        RMQ<int, less<int>, SegmentTree<int> > rmq(data);
        EXPECT_EQ(21, rmq.find(0, 1));
        EXPECT_EQ(1, rmq.find(1, 4));
        rmq.change(1, -1);
        EXPECT_EQ(-1, rmq.find(0, 1));
        EXPECT_EQ(-1, rmq.find(1, 4));
    }
    TEST_F(RMQTest, FKBTest){
        vector<int> data(20);
        data[0] = 21;
        data[1] = 99;
        data[2] = 1;
        data[3] = 2;
        data[4] = 3;
        data[5] = 51;
        data[6] = 60;
        data[7] = 77;
        data[8] = 7;
        data[9] = 2;
        data[10] = 12;
        data[11] = 55;
        data[12] = 0;
        data[13] = -7;
        data[14] = 99;
        data[15] = 4;
        data[16] = 4;
        data[17] = 432;
        data[18] = -100;
        data[19] = 8;
        RMQ<int, less<int>, SqrtDecomposition<int> > rmqs(data);
        RMQ<int, less<int>, FKB<int> > rmq(data);
        for (int i=0; i<20; i++)
            for (int j=i; j<20; j++)
               EXPECT_EQ(rmqs.find(i,j), rmq.find(i,j))<<i<<" "<<j;
        rmq.print_preprocess();
    }
    TEST_F(RMQTest, SpeedTestFKB){
        for (int k=0; k<cases_n; k++)
            speed_FKB.find(cases1[k], cases2[k]);
    }
    TEST_F(RMQTest, SpeedTestSQR){
        //for (int k=0; k<cases_n; k++)
        //    speed_SQR.find(cases1[k], cases2[k]);
    }
    TEST_F(RMQTest, SpeedTestSTR){
        for (int k=0; k<cases_n; k++)
            speed_STR.find(cases1[k], cases2[k]);
    }
    TEST_F(RMQTest, EqualTest){
        for (int l = 0; l<100; l++){
            int size = rand()%10000 + 1;
            speed_data = vector<int>(size);
            for (int i=0; i<(int)speed_data.size(); i++)
                speed_data[i] = rand()%10000+1;
            speed_STR = RMQ<int, less<int>, SegmentTree<int>>(speed_data);
            speed_SQR = RMQ<int, less<int>, SqrtDecomposition<int>>(speed_data);
            speed_FKB = RMQ<int, less<int>, FKB<int>>(speed_data);
            for (int k=0; k<10000; k++){
                int i= rand()%(size-2);
                int j= rand()%(size-2);
                if (i<=j){
                    int fkb = speed_FKB.find(i,j);
                    int sqr = speed_SQR.find(i,j);
                    int str = speed_STR.find(i,j);
                    EXPECT_EQ(fkb, str)<<i<<" "<<j;
                    EXPECT_EQ(fkb, sqr)<<i<<" "<<j;
                    EXPECT_EQ(str, sqr)<<i<<" "<<j;
                }
            }
        }
    }
    TEST_F(RMQTest, StringTest){
        vector<string> data(10, string());
        data[0] = string("aaaaa");
        data[1] = string("aaaa");
        data[2] = string("aaa");
        data[3] = string("baaaa");
        data[4] = string("baaa");
        data[5] = string("aca");
        data[6] = string("cafaaf");
        data[7] = string("agretwe");
        data[8] = string("rewyeu");
        data[9] = string("qqqqq");
        RMQ<string, less<string>, SqrtDecomposition<string> > rmqs(data);
        RMQ<string, less<string>, FKB<string> > rmq(data);
        rmq.print_preprocess();
        for (int i=0; i<10; i++)
            for (int j=i; j<10; j++)
               EXPECT_EQ(rmqs.find(i,j), rmq.find(i,j))<<i<<" "<<j;
    }
}

int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#include <iostream>
#include <gtest/gtest.h>
#include <climits>

using std::cout;
using std::cin;
using std::endl;

void countingsort(vector<string>& in, int n){
    int cnt[k-1];
    string out;
    for (int i=0; i<k; i++)
        cnt[i] = 0;
    for (int i=0; i<n; i++)
        cnt[in[i]] = cnt[in[i]] + 1;
    for (int i=1; i<k; i++)
        cnt[j] = cnt[j] + cnt[j - 1];
    for (int i=n-1; i>=0; i--){
        cnt[in[i]] = cnt[in[i]] - 1;
        out[cnt[in[i]]] = in[i];
    }
    in=out;
}
void radixsort(vector<string*>& in, int n){
    vector<vector<string*>> buckets(UCHAR_MAX, vector<string*>());
    bool flag = false;
    for (int i=0; i<in.size(); i++){
        buckets[(*in)[i][n]-1].push_back(in[i]);
        if (buckets.size()>1)
            flag = true;
    }
    if (flag==true || n==)
    for (int i=0; i<buckets.size(); i++){
        if
    }
}
class Karkajnen{
    void add_string();
};

TEST(KarkajnenTest, Test1){
}

int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_inLL_TESTS();
}

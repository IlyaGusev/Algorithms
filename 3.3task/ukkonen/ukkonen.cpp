#include <gtest/gtest.h>
#include "ukkonen.h"
#include <algorithm>

TEST(UkkonenTest, Test1){
    Ukkonen u("lear.txt");
    EXPECT_EQ(u.count("Lear"), 201);
    EXPECT_EQ(u.count("Lea"), 214);
    EXPECT_EQ(u.count("ear"), 416);
    EXPECT_EQ(u.count("Kent"), 134);
    EXPECT_EQ(u.count("Edmond"), 12);
    EXPECT_EQ(u.count("Flourish"), 4);
    EXPECT_EQ(u.count("Bastard"), 11);
    EXPECT_EQ(u.count("Gloster"), 22);
    EXPECT_EQ(u.count("a"), 6954);
    EXPECT_EQ(u.count("b"), 1110);
    EXPECT_EQ(u.count("."), 1653);
    EXPECT_EQ(u.count(","), 2741);

    vector<int> l = u.find("Lear");
    std::sort(l.begin(), l.end());
    EXPECT_EQ(l.size(), 201);
    EXPECT_EQ(l[0], 25);
}
TEST(UkkonenTest, Test2){
    Ukkonen u("example1.txt");
    u.print();
}
int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

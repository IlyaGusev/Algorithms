#include <gtest/gtest.h>
#include "aho.h"

TEST(AhoTest, Test1){
    Aho a;
    string str = my::read("lear.txt");
    a.add_string("Lear");
    a.add_string("ear");
    a.add_string("Kent");
    a.add_string("Edmond");
    a.add_string("Flourish");
    a.add_string("Bastard");
    a.add_string("Gloster");
    a.add_string("a");
    a.add_string("b");
    a.add_string(".");
    a.add_string(",");
    auto l = a.find_all_patterns(str);
    EXPECT_EQ(l["Lear"].size(), 201);
    EXPECT_EQ(l["ear"].size(), 416);
    EXPECT_EQ(l["Kent"].size(), 134);
    EXPECT_EQ(l["Edmond"].size(), 12);
    EXPECT_EQ(l["Flourish"].size(), 4);
    EXPECT_EQ(l["Bastard"].size(), 11);
    EXPECT_EQ(l["Gloster"].size(), 22);
    EXPECT_EQ(l["a"].size(), 6954);
    EXPECT_EQ(l["b"].size(), 1110);
    EXPECT_EQ(l["."].size(), 1653);
    EXPECT_EQ(l[","].size(), 2741);
}

int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

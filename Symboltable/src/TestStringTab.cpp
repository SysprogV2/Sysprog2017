#include "../includes/StringTab.h"
#include "gtest/gtest.h"

char *testInsert(StringTab *stringTab, char *input);

TEST(stringtable, insert) {
    StringTab *stringTab = new StringTab();
    EXPECT_TRUE(stringTab != nullptr);

    EXPECT_TRUE(testInsert(stringTab, "reallyreal") != nullptr);
    EXPECT_TRUE(testInsert(stringTab, "a") != nullptr);
    EXPECT_TRUE(testInsert(stringTab, "b") != nullptr);
    EXPECT_TRUE(testInsert(stringTab, "c") != nullptr);
    EXPECT_TRUE(testInsert(stringTab, "d") != nullptr);
    EXPECT_TRUE(testInsert(stringTab, "mio moi mio") != nullptr);
    EXPECT_TRUE(testInsert(stringTab, "RACINGTEAM") != nullptr);
    EXPECT_TRUE(testInsert(stringTab, "trytohandleths") != nullptr);
    EXPECT_TRUE(testInsert(stringTab, "not impressed at all") != nullptr);
    EXPECT_TRUE(testInsert(stringTab, "reallyreallyreallyreallyreallyreallyreallyreallyreallyreallyString") != nullptr);
}


char *testInsert(StringTab *stringTab, char *input) {
    std::string copy = input;
    return stringTab->insert(copy.c_str(), (int) copy.length());
}
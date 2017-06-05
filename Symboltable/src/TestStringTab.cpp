#include "../includes/StringTab.h"
#include "gtest/gtest.h"

char *testInsert(StringTab *stringTab, char *input);

TEST(stringtable, insert1) {
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

// TODO: StringTab Test here? Better move to TestStringTab
TEST(stringtable, insert2) {
    // setup
    StringTab * st = new StringTab();

    const char *charPtr1 = "a";
    int charPtrLen1 = 10;
    const char *charPtr2 = "veryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryverylongstring";
    int charPtrLen2 = 114;
    const char *charPtr3 = "veryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryverylongstringveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryverylongstringveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryverylongstringveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryverylongstringveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryverylongstring";
    int charPtrLen3 = 570;

    // #1
    char *entry1 = st->insert(charPtr1, charPtrLen1);
    EXPECT_TRUE(charPtr1 != entry1);
    EXPECT_FALSE(strcmp(charPtr1, entry1) );

    // #2
    char *entry2 = st->insert(charPtr2, charPtrLen2);
    EXPECT_TRUE(charPtr2 != entry2);
    EXPECT_FALSE(strcmp(charPtr2, entry2) );

    // #3
    char *entry3 = st->insert(charPtr3, charPtrLen3);
    EXPECT_TRUE(charPtr3 != entry3);
    EXPECT_FALSE(strcmp(charPtr3, entry3) );
}

char *testInsert(StringTab *stringTab, char *input) {
    std::string copy = input;
    return stringTab->insert(copy.c_str(), (int) copy.length());
}
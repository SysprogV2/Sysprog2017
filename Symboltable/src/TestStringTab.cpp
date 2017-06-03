#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"

#include "../includes/StringTab.h"

#define CATCH_CONFIG_MAIN

#include "../../CatchLib/includes/catch.hpp"

char *testInsert(StringTab *stringTab, char *input);

TEST_CASE("default", "[stringtable]") {
    StringTab *stringTab = new StringTab();
    REQUIRE(stringTab != nullptr);

    REQUIRE(testInsert(stringTab, "reallyreal") != nullptr);
    REQUIRE(testInsert(stringTab, "a") != nullptr);
    REQUIRE(testInsert(stringTab, "b") != nullptr);
    REQUIRE(testInsert(stringTab, "c") != nullptr);
    REQUIRE(testInsert(stringTab, "d") != nullptr);
    REQUIRE(testInsert(stringTab, "mio moi mio") != nullptr);
    REQUIRE(testInsert(stringTab, "RACINGTEAM") != nullptr);
    REQUIRE(testInsert(stringTab, "trytohandleths") != nullptr);
    REQUIRE(testInsert(stringTab, "not impressed at all") != nullptr);
    REQUIRE(testInsert(stringTab, "reallyreallyreallyreallyreallyreallyreallyreallyreallyreallyString") != nullptr);
}


char *testInsert(StringTab *stringTab, char *input) {
    std::string copy = input;
    return stringTab->insert(copy.c_str(), (int) copy.length());
}

#pragma clang diagnostic pop
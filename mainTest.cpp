#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"
#define CATCH_CONFIG_MAIN

#include "Parser/includes/Parser.h"
#include "./CatchLib/includes/catch.hpp"


TEST_CASE("Main test", "[main]") {
    char *TEST_FILE = (char *) "./test/scanner0.txt";
    Parser *parser = new Parser(TEST_FILE);
    REQUIRE(parser != nullptr);

    ParseTree *tree = parser->parse();
    REQUIRE(tree != nullptr);

    REQUIRE(tree->typeCheck());
    REQUIRE_NOTHROW(tree->makeCode());
}

#pragma clang diagnostic pop
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"
#include "../includes/Parser.h"
#define CATCH_CONFIG_MAIN
#include "../../CatchLib/includes/catch.hpp"

TEST_CASE("parser main", "[parser]") {
    const char* INPUT_FILE = (string(PROJECT_SOURCE_DIR) + "/test/parser0.txt").c_str();

	Parser* parser = new Parser((char *) INPUT_FILE);
    REQUIRE(parser != nullptr);

	ParseTree* tree = parser->parse();
    REQUIRE(tree != nullptr);

	REQUIRE(tree->typeCheck());
	REQUIRE_NOTHROW(tree->makeCode());
}

#pragma clang diagnostic pop
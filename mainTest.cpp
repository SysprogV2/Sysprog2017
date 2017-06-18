#include "gtest/gtest.h"
#include "Parser/includes/Parser.h"

TEST(main, test1) {
    auto TEST_FILE = (char *) "test/scanner0.txt";
    Parser *parser = new Parser(TEST_FILE);
    EXPECT_TRUE(parser != nullptr);

    ParseTree *tree = parser->parse();
    EXPECT_TRUE(tree != nullptr);

    EXPECT_TRUE(tree->typeCheck());
    EXPECT_NO_THROW(tree->makeCode());
}

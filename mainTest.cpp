#include "gtest/gtest.h"
#include "Parser/includes/Parser.h"

TEST(main, test1) {
    auto TEST_FILE = (char *) "test/scanner0.txt";
    Parser *parser = new Parser(TEST_FILE);
    EXPECT_TRUE(parser != nullptr);

    EXPECT_ANY_THROW(parser->parse());
}

TEST(main, test2) {
    char *TEST_FILE = (char *) "test/scanner1.txt";
    Parser *parser = new Parser(TEST_FILE);
    EXPECT_TRUE(parser != nullptr);

    EXPECT_ANY_THROW(parser->parse());
}

TEST(main, test3) {
    char *TEST_FILE = (char *) "test/scanner2.txt";
    Parser *parser = new Parser(TEST_FILE);
    EXPECT_TRUE(parser != nullptr);

    EXPECT_ANY_THROW(parser->parse());
}

TEST(main, test4) {
    char *TEST_FILE = (char *) "test/scanner3.txt";
    Parser *parser = new Parser(TEST_FILE);
    EXPECT_TRUE(parser != nullptr);

    EXPECT_ANY_THROW(parser->parse());
}

TEST(main, test5) {
    char *TEST_FILE = (char *) "test/scanner4.txt";
    Parser *parser = new Parser(TEST_FILE);
    EXPECT_TRUE(parser != nullptr);

    EXPECT_ANY_THROW(parser->parse());
}

TEST(main, test6) {
    char *TEST_FILE = (char *) "test/scanner5.txt";
    Parser *parser = new Parser(TEST_FILE);
    EXPECT_TRUE(parser != nullptr);

    EXPECT_ANY_THROW(parser->parse());
}

TEST(main, test7) {
    char *TEST_FILE = (char *) "test/scanner6.txt";
    Parser *parser = new Parser(TEST_FILE);
    EXPECT_TRUE(parser != nullptr);

    EXPECT_ANY_THROW(parser->parse());
}

TEST(main, test8) {
    char *TEST_FILE = (char *) "test/scanner7.txt";
    Parser *parser = new Parser(TEST_FILE);
    EXPECT_TRUE(parser != nullptr);

    EXPECT_ANY_THROW(parser->parse());
}

TEST(main, test9) {
    char *TEST_FILE = (char *) "test/scanner8unix.txt";
    Parser *parser = new Parser(TEST_FILE);
    EXPECT_TRUE(parser != nullptr);

    EXPECT_ANY_THROW(parser->parse());
}

TEST(main, test10) {
    char *TEST_FILE = (char *) "test/scanner9.txt";
    Parser *parser = new Parser(TEST_FILE);
    EXPECT_TRUE(parser != nullptr);

    EXPECT_ANY_THROW(parser->parse());
}

TEST(main, test11) {
    char *TEST_FILE = (char *) "test/short.txt";
    Parser *parser = new Parser(TEST_FILE);
    EXPECT_TRUE(parser != nullptr);

    EXPECT_ANY_THROW(parser->parse());
}

TEST(main, test12) {
    char *TEST_FILE = (char *) "test/parser0.txt";
    Parser *parser = new Parser(TEST_FILE);
    EXPECT_TRUE(parser != nullptr);

    EXPECT_ANY_THROW(parser->parse());
}

TEST(main, test13) {
    char *TEST_FILE = (char *) "test/parser1.txt";
    Parser *parser = new Parser(TEST_FILE);
    EXPECT_TRUE(parser != nullptr);

    EXPECT_ANY_THROW(parser->parse());
}

TEST(main, test14) {
    char *TEST_FILE = (char *) "test/parser2.txt";
    Parser *parser = new Parser(TEST_FILE);
    EXPECT_TRUE(parser != nullptr);

    EXPECT_ANY_THROW(parser->parse());
}

TEST(main, test15) {
    char *TEST_FILE = (char *) "test/parser3.txt";
    Parser *parser = new Parser(TEST_FILE);
    EXPECT_TRUE(parser != nullptr);

    ParseTree *tree = parser->parse();
    EXPECT_TRUE(tree != nullptr);

    EXPECT_FALSE(tree->typeCheck());
}

TEST(main, test16) {
    char *TEST_FILE = (char *) "test/parser4.txt";
    Parser *parser = new Parser(TEST_FILE);
    EXPECT_TRUE(parser != nullptr);

    ParseTree *tree = parser->parse();
    EXPECT_TRUE(tree != nullptr);

    EXPECT_FALSE(tree->typeCheck());
}

TEST(main, test17) {
    char *TEST_FILE = (char *) "test/parser5.txt";
    Parser *parser = new Parser(TEST_FILE);
    EXPECT_TRUE(parser != nullptr);

    ParseTree *tree = parser->parse();
    EXPECT_TRUE(tree != nullptr);

    EXPECT_TRUE(tree->typeCheck());
    EXPECT_NO_THROW(tree->makeCode());
}

TEST(main, test18) {
    char *TEST_FILE = (char *) "test/p0.txt";
    Parser *parser = new Parser(TEST_FILE);
    EXPECT_TRUE(parser != nullptr);

    ParseTree *tree = parser->parse();
    EXPECT_TRUE(tree != nullptr);

    EXPECT_TRUE(tree->typeCheck());
    EXPECT_NO_THROW(tree->makeCode());
}

TEST(main, test19) {
    char *TEST_FILE = (char *) "test/p1Test.txt";
    Parser *parser = new Parser(TEST_FILE);
    EXPECT_TRUE(parser != nullptr);

    ParseTree *tree = parser->parse();
    EXPECT_TRUE(tree != nullptr);

    EXPECT_TRUE(tree->typeCheck());
    EXPECT_NO_THROW(tree->makeCode());
}

TEST(main, test20) {
    char *TEST_FILE = (char *) "test/p2Test.txt";
    Parser *parser = new Parser(TEST_FILE);
    EXPECT_TRUE(parser != nullptr);

    ParseTree *tree = parser->parse();
    EXPECT_TRUE(tree != nullptr);

    EXPECT_TRUE(tree->typeCheck());
    EXPECT_NO_THROW(tree->makeCode());
}

TEST(main, test21) {
    char *TEST_FILE = (char *) "test/p3Test.txt";
    Parser *parser = new Parser(TEST_FILE);
    EXPECT_TRUE(parser != nullptr);

    ParseTree *tree = parser->parse();
    EXPECT_TRUE(tree != nullptr);

    EXPECT_TRUE(tree->typeCheck());
    EXPECT_NO_THROW(tree->makeCode());
}

TEST(main, test22) {
    char *TEST_FILE = (char *) "test/p4Test.txt";
    Parser *parser = new Parser(TEST_FILE);
    EXPECT_TRUE(parser != nullptr);

    ParseTree *tree = parser->parse();
    EXPECT_TRUE(tree != nullptr);

    EXPECT_TRUE(tree->typeCheck());
    EXPECT_NO_THROW(tree->makeCode());
}

TEST(main, test23) {
    char *TEST_FILE = (char *) "test/p5Test.txt";
    Parser *parser = new Parser(TEST_FILE);
    EXPECT_TRUE(parser != nullptr);

    ParseTree *tree = parser->parse();
    EXPECT_TRUE(tree != nullptr);

    EXPECT_TRUE(tree->typeCheck());
    EXPECT_NO_THROW(tree->makeCode());
}

TEST(main, test24) {
    char *TEST_FILE = (char *) "test/p6Test.txt";
    Parser *parser = new Parser(TEST_FILE);
    EXPECT_TRUE(parser != nullptr);

    ParseTree *tree = parser->parse();
    EXPECT_TRUE(tree != nullptr);

    EXPECT_TRUE(tree->typeCheck());
    EXPECT_NO_THROW(tree->makeCode());
}

TEST(main, test25) {
    char *TEST_FILE = (char *) "test/p7Test.txt";
    Parser *parser = new Parser(TEST_FILE);
    EXPECT_TRUE(parser != nullptr);

    ParseTree *tree = parser->parse();
    EXPECT_TRUE(tree != nullptr);

    EXPECT_TRUE(tree->typeCheck());
    EXPECT_NO_THROW(tree->makeCode());
}

TEST(main, test26) {
    char *TEST_FILE = (char *) "test/p8Test.txt";
    Parser *parser = new Parser(TEST_FILE);
    EXPECT_TRUE(parser != nullptr);

    ParseTree *tree = parser->parse();
    EXPECT_TRUE(tree != nullptr);

    EXPECT_TRUE(tree->typeCheck());
    EXPECT_NO_THROW(tree->makeCode());
}

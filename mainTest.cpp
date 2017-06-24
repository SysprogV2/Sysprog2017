#include "gtest/gtest.h"
#include "Parser/includes/Parser.h"


#define PATH()

TEST(main, test1) {

	auto TEST_FILE = (string(PROJECT_SOURCE_DIR) + string("/test/scanner0.txt")).c_str();

	Parser *parser = new Parser(TEST_FILE);
	EXPECT_TRUE(parser != nullptr);

	EXPECT_ANY_THROW(parser->parse());
}

TEST(main, test2) {
	auto TEST_FILE = (string(PROJECT_SOURCE_DIR) + string("/test/scanner1.txt")).c_str();
	Parser *parser = new Parser(TEST_FILE);
	EXPECT_TRUE(parser != nullptr);

	EXPECT_ANY_THROW(parser->parse());
}

TEST(main, test3) {
	auto TEST_FILE = (string(PROJECT_SOURCE_DIR) + string("/test/scanner2.txt")).c_str();
	Parser *parser = new Parser(TEST_FILE);
	EXPECT_TRUE(parser != nullptr);

	EXPECT_ANY_THROW(parser->parse());
}

TEST(main, test4) {
	auto TEST_FILE = (string(PROJECT_SOURCE_DIR) + string("/test/scanner3.txt")).c_str();
	Parser *parser = new Parser(TEST_FILE);
	EXPECT_TRUE(parser != nullptr);

	EXPECT_ANY_THROW(parser->parse());
}

TEST(main, test5) {
	auto TEST_FILE = (string(PROJECT_SOURCE_DIR) + string("/test/scanner4.txt")).c_str();
	Parser *parser = new Parser(TEST_FILE);
	EXPECT_TRUE(parser != nullptr);

	EXPECT_ANY_THROW(parser->parse());
}

TEST(main, test6) {
	auto TEST_FILE = (string(PROJECT_SOURCE_DIR) + string("/test/scanner5.txt")).c_str();
	Parser *parser = new Parser(TEST_FILE);
	EXPECT_TRUE(parser != nullptr);

	EXPECT_ANY_THROW(parser->parse());
}

TEST(main, test7) {
	auto TEST_FILE = (string(PROJECT_SOURCE_DIR) + string("/test/scanner6.txt")).c_str();
	Parser *parser = new Parser(TEST_FILE);
	EXPECT_TRUE(parser != nullptr);

	EXPECT_ANY_THROW(parser->parse());
}

TEST(main, test8) {
	auto TEST_FILE = (string(PROJECT_SOURCE_DIR) + string("/test/scanner7.txt")).c_str();
	Parser *parser = new Parser(TEST_FILE);
	EXPECT_TRUE(parser != nullptr);

	EXPECT_ANY_THROW(parser->parse());
}

TEST(main, test9) {
	auto TEST_FILE = (string(PROJECT_SOURCE_DIR) + string("/test/scanner8unix.txt")).c_str();
	Parser *parser = new Parser(TEST_FILE);
	EXPECT_TRUE(parser != nullptr);

	EXPECT_ANY_THROW(parser->parse());
}

TEST(main, test10) {
	auto TEST_FILE = (string(PROJECT_SOURCE_DIR) + string("/test/scanner9.txt")).c_str();
	Parser *parser = new Parser(TEST_FILE);
	EXPECT_TRUE(parser != nullptr);

	EXPECT_ANY_THROW(parser->parse());
}

TEST(main, test11) {
	auto TEST_FILE = (string(PROJECT_SOURCE_DIR) + string("/test/short.txt")).c_str();
	Parser *parser = new Parser(TEST_FILE);
	EXPECT_TRUE(parser != nullptr);

	EXPECT_ANY_THROW(parser->parse());
}

TEST(main, test12) {
	auto TEST_FILE = (string(PROJECT_SOURCE_DIR) + string("/test/parser0.txt")).c_str();
	Parser *parser = new Parser(TEST_FILE);
	EXPECT_TRUE(parser != nullptr);

	EXPECT_ANY_THROW(parser->parse());
}

TEST(main, test13) {
	auto TEST_FILE = (string(PROJECT_SOURCE_DIR) + string("/test/parser1.txt")).c_str();
	Parser *parser = new Parser(TEST_FILE);
	EXPECT_TRUE(parser != nullptr);

	EXPECT_ANY_THROW(parser->parse());
}

TEST(main, test14) {
	auto TEST_FILE = (string(PROJECT_SOURCE_DIR) + string("/test/parser2.txt")).c_str();
	Parser *parser = new Parser(TEST_FILE);
	EXPECT_TRUE(parser != nullptr);

	EXPECT_ANY_THROW(parser->parse());
}

TEST(main, test15) {
	auto TEST_FILE = (string(PROJECT_SOURCE_DIR) + string("/test/parser3.txt")).c_str();
	Parser *parser = new Parser(TEST_FILE);
	EXPECT_TRUE(parser != nullptr);

	ParseTree *tree = parser->parse();
	EXPECT_TRUE(tree != nullptr);

	EXPECT_FALSE(tree->typeCheck());
}

TEST(main, test16) {
	auto TEST_FILE = (string(PROJECT_SOURCE_DIR) + string("/test/parser4.txt")).c_str();
	Parser *parser = new Parser(TEST_FILE);
	EXPECT_TRUE(parser != nullptr);

	ParseTree *tree = parser->parse();
	EXPECT_TRUE(tree != nullptr);

	EXPECT_FALSE(tree->typeCheck());
}

TEST(main, test17) {
	auto TEST_FILE = (string(PROJECT_SOURCE_DIR) + string("/test/parser5.txt")).c_str();
	Parser *parser = new Parser(TEST_FILE);
	EXPECT_TRUE(parser != nullptr);

	ParseTree *tree = parser->parse();
	EXPECT_TRUE(tree != nullptr);

	EXPECT_TRUE(tree->typeCheck());
	EXPECT_NO_THROW(tree->makeCode());
}

TEST(main, test18) {
	auto TEST_FILE = (string(PROJECT_SOURCE_DIR) + string("/test/p0.txt")).c_str();
	Parser *parser = new Parser(TEST_FILE);
	EXPECT_TRUE(parser != nullptr);

	ParseTree *tree = parser->parse();
	EXPECT_TRUE(tree != nullptr);

	EXPECT_TRUE(tree->typeCheck());
	EXPECT_NO_THROW(tree->makeCode());
}

TEST(main, test19) {
	auto TEST_FILE = (string(PROJECT_SOURCE_DIR) + string("/test/p1Test.txt")).c_str();
	Parser *parser = new Parser(TEST_FILE);
	EXPECT_TRUE(parser != nullptr);

	ParseTree *tree = parser->parse();
	EXPECT_TRUE(tree != nullptr);

	EXPECT_TRUE(tree->typeCheck());
	EXPECT_NO_THROW(tree->makeCode());
}

TEST(main, test20) {
	auto TEST_FILE = (string(PROJECT_SOURCE_DIR) + string("/test/p2Test.txt")).c_str();
	Parser *parser = new Parser(TEST_FILE);
	EXPECT_TRUE(parser != nullptr);

	ParseTree *tree = parser->parse();
	EXPECT_TRUE(tree != nullptr);

	EXPECT_TRUE(tree->typeCheck());
	EXPECT_NO_THROW(tree->makeCode());
}

TEST(main, test21) {
	auto TEST_FILE = (string(PROJECT_SOURCE_DIR) + string("/test/p3Test.txt")).c_str();
	Parser *parser = new Parser(TEST_FILE);
	EXPECT_TRUE(parser != nullptr);

	ParseTree *tree = parser->parse();
	EXPECT_TRUE(tree != nullptr);

	EXPECT_TRUE(tree->typeCheck());
	EXPECT_NO_THROW(tree->makeCode());
}

TEST(main, test22) {
	auto TEST_FILE = (string(PROJECT_SOURCE_DIR) + string("/test/p4Test.txt")).c_str();
	Parser *parser = new Parser(TEST_FILE);
	EXPECT_TRUE(parser != nullptr);

	ParseTree *tree = parser->parse();
	EXPECT_TRUE(tree != nullptr);

	EXPECT_TRUE(tree->typeCheck());
	EXPECT_NO_THROW(tree->makeCode());
}

TEST(main, test23) {
	auto TEST_FILE = (string(PROJECT_SOURCE_DIR) + string("/test/p5Test.txt")).c_str();
	Parser *parser = new Parser(TEST_FILE);
	EXPECT_TRUE(parser != nullptr);

	ParseTree *tree = parser->parse();
	EXPECT_TRUE(tree != nullptr);

	EXPECT_TRUE(tree->typeCheck());
	EXPECT_NO_THROW(tree->makeCode());
}

TEST(main, test24) {
	auto TEST_FILE = (string(PROJECT_SOURCE_DIR) + string("/test/p6Test.txt")).c_str();
	Parser *parser = new Parser(TEST_FILE);
	EXPECT_TRUE(parser != nullptr);

	ParseTree *tree = parser->parse();
	EXPECT_TRUE(tree != nullptr);

	EXPECT_TRUE(tree->typeCheck());
	EXPECT_NO_THROW(tree->makeCode());
}

TEST(main, test25) {
	auto TEST_FILE = (string(PROJECT_SOURCE_DIR) + string("/test/p7Test.txt")).c_str();
	Parser *parser = new Parser(TEST_FILE);
	EXPECT_TRUE(parser != nullptr);

	ParseTree *tree = parser->parse();
	EXPECT_TRUE(tree != nullptr);

	EXPECT_TRUE(tree->typeCheck());
	EXPECT_NO_THROW(tree->makeCode());
}

TEST(main, test26) {
	auto TEST_FILE = (string(PROJECT_SOURCE_DIR) + string("/test/p8Test.txt")).c_str();
	Parser *parser = new Parser(TEST_FILE);
	EXPECT_TRUE(parser != nullptr);

	ParseTree *tree = parser->parse();
	EXPECT_TRUE(tree != nullptr);

	EXPECT_TRUE(tree->typeCheck());
	EXPECT_NO_THROW(tree->makeCode());
}

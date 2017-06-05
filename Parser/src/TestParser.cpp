#include "../includes/Parser.h"
#include "gtest/gtest.h"

#define FILE0 string(PROJECT_SOURCE_DIR "/test/parser0.txt")

inline bool file_exists (const std::string& name) {
    ifstream f(name.c_str());
    return f.good();
}

TEST(parser, test1) {
    EXPECT_TRUE(file_exists(FILE0));

	Parser* parser = new Parser(FILE0.c_str());
    EXPECT_TRUE(parser != nullptr);


	ParseTree *tree = nullptr;
    EXPECT_ANY_THROW(tree = parser->parse()); // TODO: Process finished with exit code 139 (interrupted by signal 11: SIGSEGV)

    EXPECT_TRUE(tree != nullptr);

	EXPECT_TRUE(tree->typeCheck());
	EXPECT_NO_THROW(tree->makeCode());
}
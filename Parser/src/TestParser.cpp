#include "../includes/Parser.h"
#include "gtest/gtest.h"

std::string* testfiles = new string[15] {
		string(PROJECT_SOURCE_DIR) + string("/test/p0.txt"),
		string(PROJECT_SOURCE_DIR) + string("/test/p1Test.txt"),
		string(PROJECT_SOURCE_DIR) + string("/test/p2Test.txt"),
		string(PROJECT_SOURCE_DIR) + string("/test/p3Test.txt"),
		string(PROJECT_SOURCE_DIR) + string("/test/p4Test.txt"),
		string(PROJECT_SOURCE_DIR) + string("/test/p5Test.txt"),
		string(PROJECT_SOURCE_DIR) + string("/test/p6Test.txt"),
		string(PROJECT_SOURCE_DIR) + string("/test/p7Test.txt"),
		string(PROJECT_SOURCE_DIR) + string("/test/p8Test.txt"),
		string(PROJECT_SOURCE_DIR) + string("/test/parser0.txt"),
		string(PROJECT_SOURCE_DIR) + string("/test/parser1.txt"),
		string(PROJECT_SOURCE_DIR) + string("/test/parser2.txt"),
		string(PROJECT_SOURCE_DIR) + string("/test/parser3.txt"),
		string(PROJECT_SOURCE_DIR) + string("/test/parser4.txt"),
		string(PROJECT_SOURCE_DIR) + string("/test/parser5.txt")
};

inline bool file_exists (const std::string& name) {
    ifstream f(name.c_str());
    return f.good();
}

TEST(parser, test1) {


	for(int i = 0; i < 15; i++) {
		cout << endl << endl << "Next file: " << testfiles[i].c_str() << endl;

		ASSERT_TRUE(file_exists(testfiles[i]));

		Parser* parser = nullptr;
		EXPECT_NO_FATAL_FAILURE(parser = new Parser(testfiles[i].c_str()));
		ASSERT_TRUE(parser != nullptr);


		ParseTree *tree = nullptr;
		EXPECT_NO_FATAL_FAILURE(tree = parser->parse());
		EXPECT_TRUE(tree != nullptr);

		EXPECT_NO_FATAL_FAILURE(tree->typeCheck());
		EXPECT_NO_FATAL_FAILURE(tree->makeCode());
	}

}

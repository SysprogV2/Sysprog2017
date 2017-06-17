#include "../includes/Parser.h"
#include "gtest/gtest.h"

std::string* testfiles = new string[15] {
		"/test/p0.txt",
		"/test/p1Test.txt",
		"/test/p2Test.txt",
		"/test/p3Test.txt",
		"/test/p4Test.txt",
		"/test/p5Test.txt",
		"/test/p6Test.txt",
		"/test/p7Test.txt",
		"/test/p8Test.txt",
		"/test/parser0.txt",
		"/test/parser1.txt",
		"/test/parser2.txt",
		"/test/parser3.txt",
		"/test/parser4.txt",
		"/test/parser5.txt"
};

inline bool file_exists (const std::string& name) {
    ifstream f(name.c_str());
    return f.good();
}

TEST(parser, test1) {


	for(int i = 0; i < 15; i++) {
		cout << endl << endl << "Next file: " << testfiles[i].c_str() << endl;

		//ASSERT_TRUE(file_exists(testfiles[i]));

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

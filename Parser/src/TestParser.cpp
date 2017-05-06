/*
 * TestParser.cpp
 *
 *  Created on: Jan 22, 2016
 *      Author: arty
 */
#include "../includes/Parser.h"
typedef unsigned long long timestamp_t;
static timestamp_t
get_timestamp ()
{
   struct timeval now;
   gettimeofday (&now, NULL);
   return  now.tv_usec + (timestamp_t)now.tv_sec * 1000000;
}

int TEST(int argc, char* argv[]) {
	std::cout << "Compiler running now (TestParser)\n";
	timestamp_t t0 = get_timestamp();

	if (argc < 2) return EXIT_FAILURE;

	/* unlike previous version, this is self-made,
	 * but the test should run correctly
	 */
	Parser* parser = new Parser(argv[1]);
	ParseTree* tree = parser->parse();
	if (!tree->typeCheck()) {
		return EXIT_FAILURE;
	}
	tree->makeCode();
	std::cout << "Time: " << (get_timestamp() - t0) / 1000000.0L << "secs"  << std::endl;
	return EXIT_SUCCESS;
}

int main(int argc, char* argv[]) {
	switch(TEST(argc, argv)) {
		case EXIT_SUCCESS:
			cout << "SUCCESS" << endl;
		default:
			cout << "FAIL" << endl;
	}
}

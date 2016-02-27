/*
 * main.cpp
 *
 *  Created on: Nov 11, 2015
 *      Author: arty
 */
#include "Parser/includes/Parser.h"

#include <sys/time.h>
#include <iostream>
#include <unistd.h> /* for WRITE */
#include <fcntl.h>

/* copypasted piece of code for running-time measurements */
typedef unsigned long long timestamp_t;
static timestamp_t
get_timestamp ()
{
   struct timeval now;
   gettimeofday (&now, nullptr);
   return  now.tv_usec + (timestamp_t)now.tv_sec * 1000000;
}


int main(int argc, char* argv[]) {
	std::cout << "Compiler running now (main)\n";
    timestamp_t t0 = get_timestamp();

	if (argc < 1) return EXIT_FAILURE;

	/* unlike previous version, this is self-made,
	 * but the test should run correctly
	 */
	Parser* parser = new Parser(argv[0]);
	ParseTree* tree = parser->parse();
	int compile_error;
	if (tree->typeCheck()) {
		compile_error = 0;
		tree->makeCode();
	} else {
		compile_error = 1;
	}
	std::cout << "Time: " << (get_timestamp() - t0) / 1000000.0L << "secs"  << std::endl;
	return compile_error;
}



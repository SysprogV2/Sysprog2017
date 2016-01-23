/*
 * TestParser.cpp
 *
 *  Created on: Jan 22, 2016
 *      Author: arty
 */
#include "../includes/Parser.h"


int main(int argc, char **argv) {
	Parser *par = new Parser("/home/arty/workspace/SysProg2015/test/scanner0.txt");
	ParseTree *tree = par->parse();
	return 0;
}

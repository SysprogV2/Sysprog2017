/*
 * Parser.cpp
 *
 *  Created on: 16.01.2016
 *      Author: work
 */

#include "../includes/Parser.h"

Parser::Parser(char* filename) {
	this->scanner = new Scanner (filename);
	ParseTree::initStatic();
}

ParseTree* Parser::parse() {
	return new ProgOnly(this->scanner);
}

Parser::~Parser() {
	delete this->scanner;
	// clean up all static ParseTree members (only the Parser ever calls first() and isMatching(), and there is only one)
	ParseTree::cleanupStatic();
}

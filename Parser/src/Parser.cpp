/*
 * Parser.cpp
 *
 *  Created on: 16.01.2016
 *      Author: work
 */

#include "../includes/Parser.h"

Parser::Parser(char* filename) {
	this->scanner = new Scanner (filename); // the Scanner that will be used all along the process
	ParseTree::initStatic();
}

ParseTree* Parser::parse() {
	return new ProgOnly(this->scanner); // the actual parsing process happens in the ParseTree
}

Parser::~Parser() {
	delete this->scanner;
	// clean up all static ParseTree members (only the Parser ever calls first() and isMatching(), and there is only one)
	// side note: should the Parser be explicitly set up as singleton?
	ParseTree::cleanupStatic();
}

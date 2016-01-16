/*
 * Parser.h
 *
 *  Created on: 16.01.2016
 *      Author: work
 */

#ifndef PARSER_INCLUDES_PARSER_H_
#define PARSER_INCLUDES_PARSER_H_

#include "ParseTree.h"

class Parser {
private:
	// might be incomplete
	TokenSequence* currentCodeSnippet;
	TokenSequence* composeTable();
public:
	Parser();
	ParseTree* parse();
	~Parser();
};


#endif /* PARSER_INCLUDES_PARSER_H_ */

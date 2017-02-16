/*
 * Parser.h
 *
 *  Created on: 16.01.2016
 *      Author: work
 */

#ifndef PARSER_INCLUDES_PARSER_H_
#define PARSER_INCLUDES_PARSER_H_

#include "ParseTree.h"
#include "../../Scanner/includes/Scanner.h"
#include <sys/time.h>

class Parser {
private:
	Scanner* scanner;
public:
	Parser(char* filename);
	ParseTree* parse();
	~Parser();
};

#endif /* PARSER_INCLUDES_PARSER_H_ */

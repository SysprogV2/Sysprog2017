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

class Parser {
private:
	TokenSequence* currentCodeSnippet;
	TokenSequence* composeTable(char* filename);
	void buildDecl (Decl** toBuild, TokenSequence* relatedSequence);
	void buildStatement (Statement** toBuild, TokenSequence* relatedSequence);
	Index* buildIndex(TokenSequence* related);
	Exp* buildExp(TokenSequence* related);
	Exp2* buildExp2(TokenSequence* related);
public:
	Parser(char* filename);
	ParseTree* parse();
	~Parser();
};

#endif /* PARSER_INCLUDES_PARSER_H_ */

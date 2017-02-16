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
	delete ParseTree::bracketsToken;
	delete ParseTree::epsToken;
	delete ParseTree::identifierToken;
	delete ParseTree::integerToken;
	delete ParseTree::minusToken;
	delete DeclOnly::firstToken;
	delete StatementWrite::firstToken;
	delete StatementRead::firstToken;
	delete StatementBlock::firstToken;
	delete StatementIfElse::firstToken;
	delete StatementWhile::firstToken;
	delete Exp2Nested::firstToken;
	delete Exp2LogicalNegation::firstToken;
	delete OpPlus::firstToken;
	delete OpMult::firstToken;
	delete OpDiv::firstToken;
	delete OpLess::firstToken;
	delete OpEquals::firstToken;
	delete OpAnd::firstToken;
}

/*
 * Parser.cpp
 *
 *  Created on: 16.01.2016
 *      Author: work
 */

#include "../includes/Parser.h"

Parser::Parser() {
	this->currentCodeSnippet = this->composeTable();
	ParseTree::initStatic();
}

ParseTree* Parser::parse() {
	if (!ProgOnly::isMatching(this->currentCodeSnippet)) {
		// TODO initialize error and throw it
	}
	// if it does match, the entire code (in the test file) is OK
	ParseTree* prog = new ProgOnly();
	TokenSequence* declarationPart = nullptr;
	TokenSequence* statementPart = nullptr; // TODO somehow fetch split index from ProgOnly and split currentCodeSnippet on declarationPart and statementPart
	if (Decls::first()->isSet(this->currentCodeSnippet->tokenAt(0, false))) {
		((ProgOnly*) prog)->declarationSegment = new DeclsSeq();
		// TODO resolve declarations subtree (any amount of split indexes can be necessary)
	} else {
		((ProgOnly*) prog)->declarationSegment = new DeclsEps();
	}
	// TODO resolve statements side (any amount of split indexes can be necessary)
	return prog;
}

Parser::~Parser() {
	delete this->currentCodeSnippet;
	// clean up all static ParseTree members (only the Parser ever calls first())
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
	delete OpGreater::firstToken;
	delete OpEquals::firstToken;
	delete OpNotEquals::firstToken;
	delete OpAnd::firstToken;
}

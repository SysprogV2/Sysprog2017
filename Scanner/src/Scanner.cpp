/*
 * Scanner.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */
#include "../includes/Scanner.h"

Scanner::Scanner(char *filename) {
	buffer = new Buffer(filename);
	automat = new Automat();
	syntax = new Syntax();
}

Scanner::Scanner(char *filename, Symboltable* st) {
	/* initialize buffer and automata */
	stab = st;
	buffer = new Buffer(filename);
	automat = new Automat();
	syntax = new Syntax();
}

Token *Scanner::nextToken() {
	char currentChar;
	/* run automat and feed it char by char, till any token is found */
	while ( currentChar != '\0' && !automat->isLexemReady()) {
		currentChar = buffer->getChar();
		int back_steps = automat->read(currentChar);
		tokenType = automat->getFinalState();
		buffer->ungetChar(back_steps);
		if (automat->isLexemReady() && (tokenType == WSP_Z || tokenType == CLSC_Z)) {
			automat->reset();
		}
	}

	/* save all information about the lexem */
	char* lexem = automat->getLexem();
	int lexemLength = automat->getLexemLength();
	Information* info;
	int line = automat->getLine();
	int col = automat->getColumn();

	// creating corresponding token
	if (tokenType == Syntax::IDEN_Z) {
		info = stab->lookup(lexem);
		if (info == NULL) {
			SymtabEntry* entry = stab->insert(lexem, lexemLength);
			info = entry->getInfo();
		} else {
			// do nothing
		}
	} else {
		if (tokenType == Syntax::INTG_Z) {
			info = new Information(lexem);
		} else {
			info = new Information(lexem);
		}
	}
	Token* t = new Token(tokenType, line, col, info);
	automat->reset();

	/* if we need to finish already*/
	if (currentChar == '\0') {
		std::cout << "Processing is finished" << std::endl;
		return NULL;
	} else {
		return t;
	}
}



Scanner::~Scanner() {
	delete buffer;
	delete automat;
}


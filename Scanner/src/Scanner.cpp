/*
 * Scanner.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */
#include "../includes/Scanner.h"

#define CONV_ERR "error: cannot convert given CHAR* to LONG INT"
#define CONV_ERR_OVERFLOW "error: given integer is too big to be converted to LONG INT"

Scanner::Scanner(char *filename) {
	buffer = new Buffer(filename);
	automat = new Automat();
	syntax = new Syntax();
	tokenType = Syntax::STRT_Z;
	stab = NULL;
}

Scanner::Scanner(char *filename, Symboltable* st) {
	/* initialize buffer and automata */
	stab = st;
	buffer = new Buffer(filename);
	automat = new Automat();
	syntax = new Syntax();
	tokenType = Syntax::STRT_Z;
}

Token *Scanner::nextToken() {
	char currentChar;

	/* run automat and feed it char by char, till any token is found */
	while ( currentChar != '\0' && !automat->isLexemReady()) {
		currentChar = buffer->getChar();
		int back_steps = automat->read(currentChar);
		tokenType = automat->getFinalState();
		buffer->ungetChar(back_steps);
		if (automat->isLexemReady() && (tokenType == Syntax::WSP_Z || tokenType == Syntax::CLSC_Z)) {
			automat->reset();
		}
	}

	/* save all information about the lexem */
	Information* info;
	char* lexem = automat->getLexem();
	int lexemLength = automat->getLexemLength();
	int line = automat->getLine();
	int col = automat->getColumn();
	int ttttype = typeFromState(tokenType, lexem);

	/* create Token */
	Token* t = new Token(ttttype, line, col);

	/* add additional information to the token */
	if (ttttype == Syntax::IDEN_Z) {
		info = stab->lookup(lexem);
		if (info == NULL) {
			SymtabEntry* entry = stab->insert(lexem, lexemLength);
			info = entry->getInfo();
		}
		t->setInformation(info);
	} else {
		if (ttttype == Syntax::INTG_Z) {
			long int value = valueFromLexem(lexem);
			t->setValue(value);
		}
		if (ttttype == Syntax::PROH_Z) {
			t->setSymbol(lexem[0]);
		}
	}

	/* now we can reset automat */
	automat->reset();

	/* if we need to finish already*/
	if (currentChar == '\0') {
		return NULL;
	} else {
		return t;
	}
}

Scanner::~Scanner() {
	delete buffer;
	delete automat;
}

int Scanner::typeFromState(int state, char* lexem) {
	/* determine the token type using STATE and LEXEM as basis */
	char symbol = lexem[0];
	int tType = state;
	if (state == Syntax::ASGN_Z) {
		tType = syntax->unpackSignToState(symbol);
	} else if (state == Syntax::IDEN_Z) {
		int koo = syntax->ifKeyword(lexem);
		if (koo > 0) tType = koo; // 30..35
	}
	return tType;
}

long int Scanner::valueFromLexem(char* lexem) {
	long int value = 0;
	char *pEnd;
	value = strtol(lexem, &pEnd, 10);
	if (errno == EINVAL) {
		std::cout << CONV_ERR << std::endl;
	} else if (errno == ERANGE) {
		std::cout << CONV_ERR_OVERFLOW << std::endl;
	}
	return value;
}

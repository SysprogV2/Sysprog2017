/*
 * Scanner.h
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */
#ifndef IOSTREAM_H
#define IOSTREAM_H
#include <iostream>
#endif /* IOSTREAM_H */


#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#endif /* IOSTREAM_H */

#ifndef SCANNER_H_
#define SCANNER_H_

#include "../../Buffer/includes/Buffer.h"
#include "../../Automat/includes/Automat.h"
#include "../../Scanner/includes/Token.h"
#include "../../Scanner/includes/Information.h"
#include "../../Symboltable/includes/StringTab.h"
#include "../../Symboltable/includes/Symboltable.h"
#define WSP_Z 12
#define CLSC_Z 16


class Scanner {
	Symboltable *stab;
	Buffer* buffer;
	Automat* automat;
	int tokenType;
	Token *t;
	Syntax* syntax;
public:
	Scanner(char *filename, Symboltable* st);
	Token* nextToken();
	virtual ~Scanner();
};

Scanner::Scanner(char *filename, Symboltable* st) {
	/* initialize buffer and automata */
	stab = st;
	buffer = new Buffer(filename);
	automat = new Automat();
	syntax = new Syntax();
}

Token *Scanner::nextToken() {
	Information* info;
	char currentChar;
	/* run automat and feed it char by char, till any token is found */
	while ( currentChar != '\0' && !automat->isTokenReady()) {
		currentChar = buffer->getChar();
		int back_steps = automat->read(currentChar);
		tokenType = automat->getFinalState();
		buffer->ungetChar(back_steps);
		if (automat->isTokenReady() && (tokenType == WSP_Z || tokenType == CLSC_Z)) {
			automat->freeToken();
		}
	}

	/* create token and return it */
	char* lexem = automat->getLexem();
	int lexemLength = automat->getLexemLength();
	char* lexemPtr = stab->insert(lexem, lexemLength);
	info = new Information(lexemPtr);
	t = new Token(tokenType,
				  automat->getLine(),
				  automat->getColumn(),
				  info,
				  syntax);
	automat->freeToken();

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


#endif /* SCANNER_H_ */

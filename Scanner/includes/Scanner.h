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

#define MAX_TOKEN_SIZE 32
#include "../../Buffer/includes/Buffer.h"
#include "../../Automat/includes/Automat.h"
#include "../../Scanner/includes/Token.h"

#define WSP_Z 12
#define CLSC_Z 16


class Scanner {
	Buffer* buffer;
	Automat* automat;
	char* toReturn;
	bool isEof = false;
	int tokenType;
	Token *t;

	bool debugMode = false; // set to TRUE if you want to see ALL tokens
public:
	Scanner(char *filename, bool mode);
	Token* nextToken();
	int getX();
	int getY();
	bool isEofReached();
	int getTokenType();
	virtual ~Scanner();
};

Scanner::Scanner(char *filename, bool mode) {
	/* initialize buffer and automata */
	toReturn = new char[MAX_TOKEN_SIZE];
	buffer = new Buffer(filename);
	automat = new Automat();
	debugMode = mode;
}

Token *Scanner::nextToken() {
	char currentChar;
	/* run automat and feed it char by char, till any token is found */
	while ( currentChar != '\0' && !automat->isTokenReady()) {
		currentChar = buffer->getChar();
		int back_steps = automat->read(currentChar);
		tokenType = automat->getTokenType();
		buffer->ungetChar(back_steps);
	}
	
	/* create token and return it */
	if (debugMode || (getTokenType() != WSP_Z && getTokenType() != CLSC_Z) ) {
		t = new Token(getTokenType(),
				automat->getLine(),
				automat->getColumn(),
				automat->stackGet());
		t->toString();
	}

	/* indicate that Eof has been reached */
	if (currentChar == '\0') isEof = true;

	/* update the automata's state to default */
	automat->freeToken();
	return t;
}

int Scanner::getTokenType() {
	return tokenType;
}

Scanner::~Scanner() {
	delete buffer;
	delete automat;
	delete toReturn;
}

bool Scanner::isEofReached() {
	return isEof;
}
#endif /* SCANNER_H_ */

/*
 * Scanner.h
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#ifndef SCANNER_H_
#define SCANNER_H_

#include "../../Buffer/includes/Buffer.h"
#include "../../Automat/includes/Automat.h"

#include <string.h> // TODO: DELETE THIS LATER!!! Prohibited library!

class Scanner {
	Buffer* buffer;
	Automat* automat;
	char* toReturn;
public:
	Scanner();
	char* nextToken();
	virtual ~Scanner();
};

Scanner::Scanner() {
	/* initialize buffer and automata */
	toReturn = new char[32];
	buffer = new Buffer("../scan1");
	automat = new Automat();
}

char *Scanner::nextToken() {
	char currentChar;
	while ( currentChar != '\0' && !automat->isTokenReady() ) {
		currentChar = buffer->getChar();
		int back_steps = automat->read(currentChar);
		buffer->ungetChar(back_steps);
	}
	strcpy(toReturn, automat->stackGet()); // TODO: rewrite this function to avoid using stdlib!
	automat->freeToken();
	return toReturn;
}

Scanner::~Scanner() {
	delete buffer;
	delete automat;
	delete toReturn;
}

#endif /* SCANNER_H_ */

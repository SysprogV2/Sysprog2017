/*
 * Scanner.h
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */
#ifndef SCANNER_H_
#define SCANNER_H_

#include <iostream>
#include <stdio.h>
#include "../../Automat/includes/Automat.h"
#include "../../Buffer/includes/Buffer.h"
#include "../../Symboltable/includes/Symboltable.h"
#include "../../Scanner/includes/Token.h"
#include "../../Automat/includes/Syntax.h"

class Scanner {
	Symboltable *stab;
	Buffer* buffer;
	Automat* automat;
	int tokenType;
	Syntax* syntax;
public:
	Scanner(char *filename);
	Scanner(char *filename, Symboltable* st);
	int typeFromState(int state, char* lexem);
	long int valueFromLexem(char* lexem);
	Token* nextToken();
	virtual ~Scanner();
};


#endif /* SCANNER_H_ */

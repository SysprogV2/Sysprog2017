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
#include "../../Compatibility/compab.h"
#include "TokenTypeRegistry.h"

class Scanner {
	Symboltable *stab;
	Buffer* buffer;
	Automat* automat;
	Syntax* syntax;
	Token* cToken;
	TokenTypeRegistry* idenInt;
public:
	Scanner(char *filename);
	Scanner(char *filename, Symboltable* st);
	int mapStateToType(int state, const char* lexem);
	void getNumberToken(const char* lexem, Token* t);
	Token* nextToken();
	Token* currentToken();
	virtual ~Scanner();
};


#endif /* SCANNER_H_ */

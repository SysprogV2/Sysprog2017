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



#define WSP_Z 12
#define CLSC_Z 16


class Scanner {
	Symboltable *stab;
	Buffer* buffer;
	Automat* automat;
	int tokenType;
	Syntax* syntax;
public:
	Scanner(char *filename);
	Scanner(char *filename, Symboltable* st);
	Token* nextToken();
	virtual ~Scanner();
};


#endif /* SCANNER_H_ */

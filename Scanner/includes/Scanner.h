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
#include "../../Compab/includes/compab.hpp"
#include "TokenTypeRegistry.h"

class Scanner {
	Symboltable *stab;
	Buffer* buffer;
	Automat* automat;
	Syntax* syntax;
	Token* cToken;
	TokenTypeRegistry* idenInt;
public:
    /**
     * Creates a code{Scanner} over the given file, with newly created code{Symboltable}.
     * @param filename the file to scan
     */
	Scanner(const char *filename);
    /**
     * Creates a code{Scanner} over the given file, with the given code{Symboltable}.
     * @param filename  the file to scan
     * @param st the code{Symboltable} to use
     */
	Scanner(const char *filename, Symboltable *st);
    /**
     * Calculates what type a code{Token} with the given lexem under the given state would have.
     * @return the type the code{Token} will have according to the calculation
     */
	int mapStateToType(int state, const char* lexem); // maybe could be private?
    /**
     * Converts a given integer lexem to a long value and assigns it to a given code{Token}.
     * @param lexem the integer lexem to convert
     * @param t the code{Token} to fill with the lexem
     * @return void
     */
	void getNumberToken(const char* lexem, Token* t); // maybe could be private?
    /**
     * Constructs the next code{Token} from the scanned file. There's no need to free the constructed code{Token}, unless it's of type code{identifier} or
     * code{integer}.
     * @return the next code{Token} occurring in the scanned file
     */
	Token* nextToken();
    /**
     * Re-returns the last constructed code{Token}. Use this if you need the exact same code{Token} (at the same position in the file) multiple times.
     * @return the last constructed code{Token}
     */
	Token* currentToken();
	virtual ~Scanner(); // why the hell virtual? does anything inherit from Scanner?
};


#endif /* SCANNER_H_ */

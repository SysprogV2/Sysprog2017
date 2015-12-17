/*
 * Token.cpp
 *
 *  Created on: Nov 18, 2015
 *      Author: arty
 */

#include "../includes/Token.h"
#include "../../Automat/includes/Syntax.h"
#include <iostream>
#include <errno.h>
Token::Token() {
	tType = 0;
	line = 0;
	column = 0;
	value = 0;
	symbol = 'a';
}



Token::Token(int state, int l, int c, Information* info) {
	symbol = 'a';
	line = l;
	column = c;
	information = info;

	/* determine the token type using STATE and INFO as basis */
	/* if STATE corresponds to REST SIGNS */
	if (state == Syntax::ASGN_Z) {
		for (int i=0; i < 11; i++) {
			if (info->getLexem()[0] == signArray[i])
				tType = i + 19;
		}
		delete info;
	} else {
		if (state == Syntax::PROH_Z) symbol = info->getLexem()[0];
		tType = state;



		/* determine the value of integer */
		char *pEnd;
		if (tType == Syntax::INTG_Z) {
			value = strtol(info->getLexem(), &pEnd, 10);
			if (errno == EINVAL) {
				std::cout << "error: cannot convert given CHAR* to LONG INT" << std::endl;
			} else if (errno == ERANGE) {
				std::cout << "error: given integer is too big to be converted to LONG INT. MAX (2147483647) assigned instead." << std::endl;
			}
			delete info; // we don't need the lexem anymore
		}

		if (state == Syntax::IDEN_Z) {
			if (info->matches("if") || info->matches("IF")) {
				tType = 30;
				std::cout << "we;ve got IF" << std::endl;
			} else if (info->matches("WHILE") || info->matches("while")) {
				tType = 31;
				std::cout << "we;ve got WHULE" << std::endl;
			} else if (info->matches("INT") || info->matches("int")) {
				tType = 32;
				std::cout << "we;ve got INT" << std::endl;
			} else if (info->matches("WRITE") || info->matches("write")) {
				tType = 33;
				std::cout << "we;ve got WRITE" << std::endl;
			} else if (info->matches("ELSE") || info->matches("else")) {
				tType = 34;
				std::cout << "we;ve got ELSE" << std::endl;
			} else if (info->matches("READ") || info->matches("read")) {
				std::cout << "we;ve got READ" << std::endl;
				tType = 35;
			}
		}
	}


}

Token::~Token() {
	delete information;
}

Information* Token::getInformation() {
	return information;
}

int Token::getType(){
	return tType;
}

char* Token::getLexem() {
	return information->getLexem();
}

int Token::getLine() {
	return line;
}

int Token::getColumn() {
	return column;
}

char* Token::typeAsString() {
	return ttypeString[tType];
}


int Token::getValue() {
	return value;
}

char Token::getSymbol() {
	return symbol;
}


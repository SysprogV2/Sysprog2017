/*
 * Token.cpp
 *
 *  Created on: Nov 18, 2015
 *      Author: arty
 */

#include "../includes/Token.h"
#include "../../Automat/includes/Syntax.h"
#include <iostream>
Token::Token() {
	tType = 0;
	line = 0;
	column = 0;
	value = 0;
}

Token::Token(int state, int l, int c, Information* info) {
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
		tType = state;
		/* determine the value of integer */
		char *pEnd;
		if (tType == Syntax::INTG_Z) {
			// TODO: where's Bereichueberschreitung, ha?
			value = strtol(info->getLexem(), &pEnd, 10);
			delete info; // we don't need the lexem anymore
		}
	}


}

Token::~Token() {
	delete information;
}

void Token::print() {
	char* typeToStr = new char[11]; /* TODO: alloc either with POSIX or simply create global var */
	strcpy(typeToStr, ttypeString[tType]);
	std::cout << "Token " << typeToStr << "  Line: " << line << " Column: " << column << "  ";

	if (tType == Syntax::IDEN_Z) {
		std::cout << "Lexem: " << information->getLexem();
	} else if (tType == Syntax::INTG_Z) {
		std::cout << "Value: " << value;
	} else {
		std::cout << "------";
	}
	std::cout << std::endl;
}

/* TODO: yet to be implemented */
char* Token::typeToString() {
	char* buf = new char[50];
	memcpy(buf, ttypeString[tType], 10);
	buf += sizeof(char) * 10;
	memcpy(buf, "  Line: ", 8);
	buf += sizeof(char) * 8;
	char *lineStr = new char[50];

	return buf;
	//itoa(line, buf, 10);
}



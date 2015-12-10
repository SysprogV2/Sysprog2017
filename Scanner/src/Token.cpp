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
			value = strtol(info->getLexem(), &pEnd, 10);
			if (errno == EINVAL) {
				std::cout << "Cannot convert given CHAR* to LONG INT. Unknown error." << std::endl;
			} else if (errno == ERANGE) {
				std::cout << "A given integer is too big to be converted to LONG INT. MAX (2147483647) assigned instead." << std::endl;
			}
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

char* Token::toString() {

	char* buf = new char[70];
	char* toReturn = buf;
	strcpy(buf, ttypeString[tType]);
	buf += sizeof(char) * 10;

	strcpy(buf, "  Line: ");
	buf += sizeof(char) * 8;
	strcpy(buf, itoc(line));
	buf += sizeof(char) * 8;

	strcpy(buf, "   Col: ");
	buf += sizeof(char) * 8;
	strcpy(buf, itoc(column));
	buf += sizeof(char) * 8;
	strcpy(buf, "  ");
	buf += sizeof(char) * 2;

	if (tType == Syntax::IDEN_Z) {
		strcpy(buf, " Lexem ");
		buf += sizeof(char) * 7;
		strcpy(buf, information->getLexem());
	} else if (tType == Syntax::INTG_Z) {
		strcpy(buf, " Value ");
		buf += sizeof(char) * 7;
		strcpy(buf, itoc(value));
	} else {
		strcpy(buf, " ------");

	}
	buf += sizeof(char) * 8;

	buf[0] = '\0';
	return toReturn;
	//itoa(line, buf, 10);
}

char* Token::itoc(int number) {
	int maxLength = 7;
	char* output = new char[maxLength + 2];
	output[8] = '\0';
	int shift = 0;
	int tmp = number;

	while (tmp > 0) {
		output[maxLength - shift] = '0' + (tmp % 10);
		shift++;
		tmp /= 10;
	}

	while (shift <= maxLength) {
		output[maxLength - shift] =' ';
		shift++;
	}

	return output;
}

Information* Token::getInformation() {
	return information;
}


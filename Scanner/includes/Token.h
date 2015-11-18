#include <string.h> // TODO: DELETE THIS LATER!!! Prohibited library!
#include <stdlib.h>  // for strtol()
#include "Information.h"
#include "../../Automat/includes/Syntax.h"

class Token {
	int tType;
	int line;
	int column;
	long int value;
	Information* information;
	Syntax* syntax;

	const char signArray[SIGN_ARRAY_SZ] = {'+','-','!','&',';','(',')','{','}','[',']'};
public:
	Token();
	Token(int type, int l, int c, Information* info, Syntax* syn);
	virtual ~Token();
	void toString();
	char* typeToString();

};

Token::Token() {
	tType = 0;
	line = 0;
	column = 0;
	value = 0;
}

Token::Token(int state, int l, int c, Information* info, Syntax* syn) {
	line = l;
	column = c;
	information = info;
	syntax = syn;

	/* determine the token type using STATE and INFO as basis */
	/* if STATE corresponds to REST SIGNS */
	if (state == Syntax::ASGN_Z) {
		for (int i=0; i < 11; i++) {
			if (info->getLexem()[0] == signArray[i])
				tType = i + 19;
		}
	} else {
		tType = state;
		/* determine the value of integer */
		char *pEnd;
		if (tType == Syntax::INTG_Z) {
			// TODO: where's Bereichueberschreitung, ha?
			value = strtol(info->getLexem(), &pEnd, 10);
		}
	}


}

Token::~Token() {
	delete information;
}

void Token::toString() {
	char typeToStr[11];
	const char *cms = syntax->getTokenTypeAsChar(tType);
	strcpy(typeToStr, cms);
	std::cout << "Token " << typeToStr
			  << "  Line: " << line << " Column: " << column << "  ";

	if (tType == Syntax::IDEN_Z) {
		std::cout << "Lexem: " << information->getLexem() << std::endl;
	} else if (tType == Syntax::INTG_Z) {
		std::cout << "Value: " << value << std::endl;
	} else {
		std::cout << "------" << std::endl;
	}
}
/*
char* Token::typeToString() {
	char* buf = new char[50];
	memcpy(buf, ttypeString[tType], 10);
	buf += sizeof(char) * 10;
	memcpy(buf, "  Line: ", 8);
	buf += sizeof(char) * 8;
	char *lineStr = new char[50];
	//itoa(line, buf, 10);
}

*/

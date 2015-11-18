#include <string.h> // TODO: DELETE THIS LATER!!! Prohibited library!
#include <stdlib.h>  // for strtol()
#include "Information.h"

class Token {
	int tType;
	int line;
	int column;
	Information* information;

	enum TokenType {
		WHITESPACE, UNKNOWN, COMMENT,

		IDENTIFIER, INTEGER, WHILE, IF,

		PLUS_S, MINUS_S, DIVIS_S, MULT_S,
		LESS_S, GREA_S, EQUAL_S, ASSIGN_S,
		SPEC_S, /* <:> */
		EXCLM_S, AND_S, SEMICOL_S,

		SQ_BRACKET_OPEN, SQ_BRACKET_CLOSE,
		PARANTHESE_OPEN, PARANTHESE_CLOSE,
		CRL_BRACKET_OPEN, CRL_BRACKET_CLOSE
	};

	long int value;
	// TODO: remove this bullshit & add normal link-like references a-la Automat::States
	enum States {STRT_Z, IDEN_Z, INTG_Z, LESS_Z, GREA_Z, COLN_Z,
					 EQLS_Z, ASGN_Z, LCLN_Z, LCLL_Z, ASSG_Z, EOF_Z,
					 WSP_Z, MULT_Z, OPNC_Z, COMM_Z, CLSC_Z, PROH_Z,
					 NULL_STATE};
	/*
	char* ttypeString[10] = {"Start", "Identifier", "Integer", "Less", "Greater", "Division"
							 "Equals", "<:>-hellknows", "Assignment", "Multiplication",
							 "Prohibited"};
	char* ttypeString[10] = {"Plus", "Minus", "Exclamation", "And", "Semicolon",
							 "Paranthese O", "Paranthese C", "Braces O", "Braces C",
							 "Brackets O", "Brackets C"};
							 */
	const char charArray[11] = {'+', '-', '!', '&', ';', '(', ')','{', '}', '[', ']'};
public:
	Token();
	Token(int type, int l, int c, Information* info);
	virtual ~Token();
	void toString();
};

Token::Token() {
	tType = 0;
	line = 0;
	column = 0;
	value = 0;
}

Token::Token(int type, int l, int c, Information* info) {
	tType = type;
	line = l;
	column = c;
	information = info;
	char *pEnd;
	if (tType == INTG_Z) {
		// TODO: where's Bereichueberschreitung, ha?
		value = strtol(info->getLexem(), &pEnd, 10);
	}
}

Token::~Token() {
	// haha, nothing!
}

void Token::toString() {
	char typeToStr[11];
	switch (tType) {
		case IDEN_Z:
			strcpy(typeToStr, "Identifier");
			break;
		case INTG_Z:
			strcpy(typeToStr, "Integer   ");
			break;
		case LESS_Z:
			strcpy(typeToStr, "Less      ");
			break;
		case GREA_Z:
			strcpy(typeToStr, "Greater   ");
			break;
		case COLN_Z:
			strcpy(typeToStr, "Division  ");
			break;
		case EQLS_Z:
			strcpy(typeToStr, "Equals    ");
			break;
		case LCLL_Z:
			strcpy(typeToStr, "<:>-type  ");
			break;
		case ASSG_Z:
			strcpy(typeToStr, "Assignment");
			break;
		case MULT_Z:
			strcpy(typeToStr, "Multiplcat");
			break;
		case PROH_Z:
			strcpy(typeToStr, "Prohibited");
			break;
		case ASGN_Z:
			strcpy(typeToStr, "  sign    "); // TODO: describe more precisely!
			typeToStr[0] = information->getLexem()[0];
			break;
		default:
			strcpy(typeToStr, "--no idea-");

	}

	std::cout << "Token " << typeToStr
			  << "  Line: " << line << " Column: " << column << "  ";

	if (tType == IDEN_Z) {
		std::cout << "Lexem: " << information->getLexem() << std::endl;
	} else if (tType == INTG_Z) {
		std::cout << "Value: " << value << std::endl;
	} else {
		std::cout << "------" << std::endl;
	}
}



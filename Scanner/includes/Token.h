#include <string.h> // TODO: DELETE THIS LATER!!! Prohibited library!
#include <stdlib.h>  // for strtol()
class Token {
	int tType;
	int line;
	int column;
	char lexem[32];
	long int value;
	enum States {STRT_Z, IDEN_Z, INTG_Z, LESS_Z, GREA_Z, COLN_Z,
					 EQLS_Z, ASGN_Z, LCLN_Z, LCLL_Z, ASSG_Z, EOF_Z,
					 WSP_Z, MULT_Z, OPNC_Z, COMM_Z, CLSC_Z, PROH_Z,
					 NULL_STATE};
	const char charArray[11] = {'+', '-', '!', '&', ';', '(', ')','{', '}', '[', ']'};
public:
	Token();
	Token(int type, int l, int c, char *lex);
	virtual ~Token();
	void toString();
};

Token::Token() {
	tType = 0;
	line = 0;
	column = 0;
	value = 0;
}

Token::Token(int type, int l, int c, char *lex) {
	tType = type;
	line = l;
	column = c;
	strcpy(lexem, lex);
	char *pEnd;
	if (tType == INTG_Z) {
		value = strtol(lexem, &pEnd, 10);
	}
}

Token::~Token() {
	delete lexem;
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
			typeToStr[0] = lexem[0];
			break;
		default:
			strcpy(typeToStr, "--no idea-");

	}

	std::cout << "Token " << typeToStr
			  << "  Line: " << line << " Column: " << column << "  ";

	if (tType == IDEN_Z) {
		std::cout << "Lexem: " << lexem << std::endl;
	} else if (tType == INTG_Z) {
		std::cout << "Value: " << value << std::endl;
	} else {
		std::cout << "------" << std::endl;
	}
}



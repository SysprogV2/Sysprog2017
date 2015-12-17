
#ifndef Token_H_
#define Token_H_

#include <string.h> // TODO: DELETE THIS LATER!!! Prohibited library!
#include <stdlib.h>  // for strtol()
#include "Information.h"

#define SIGN_ARRAY_SZ 11
class Token {
	int tType;
	int line;
	int column;
	long int value;
	Information* information;
	char symbol;
	//Syntax* syntax;
	char* ttypeString[36] = {"Start     ", "Identifier", "Integer   ", "Less      ",
							 "Greater   ", "Colon     ", "Equals    ", "<:>-sign  ",
										 "  --<:--  ", "<:>       ", "Assignment", " --eof--  ",
										 "Whitespace", "Multipl   ", "  --:*--  ", " --comm-- ",
										 "  --*:--  ", "Prohibited", " --null-- ", "Plus      ",
										 "Minus     ", "Not       ", "And       ", "Semicol   ",
										 "Paranth ( ", "Paranth ) ", "Braces {  ", "Braces }  ",
										 "Brackets [", "Brackets ]" ,"IF-Token  " , "WHILE-Token",
										 "INT-Token ", "WRITE-Toke", "ELSE-Token", "READ-Token"
	};
	const char signArray[SIGN_ARRAY_SZ] = {'+','-','!','&',';','(',')','{','}','[',']'};
public:
	Token();
	Token(int state, int l, int c, Information* info);
	virtual ~Token();
	char* itoc(int number);
	int getType();
	Information* getInformation();
	char* getLexem();
	int getLine();
	int getColumn();
	char* typeAsString();
	int getValue();
	char getSymbol();
};

#endif


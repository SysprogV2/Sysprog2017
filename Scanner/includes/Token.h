
#ifndef Token_H_
#define Token_H_

//#include <string.h> // TODO: DELETE THIS LATER!!! Prohibited library!
#include <stdlib.h>  // for strtol()
#include "Information.h"
#include "../../Compatibility/compab.h"

#define SIGN_ARRAY_SZ 11
class Token {
	int tType;
	int line;
	int column;
	long int value;
	Information* information;
	char symbol;
	const char signArray[SIGN_ARRAY_SZ] = {'+','-','!','&',';','(',')','{','}','[',']'};
public:
	static char* nameOf(int tokenType);
	Token(int type, int line, int column);
	Token(int state, int l, int c, Information* info);
	virtual ~Token();
	char* itoc(int number);
	int getType();
	Information* getInformation();
	char* getLexem();
	int getLine();
	int getColumn();
	int getValue();
	void setValue(long int value);
	char getSymbol();
	void setSymbol(char symbol);
	void setInformation(Information* info);
	bool hasSameTypeAs (Token* other);
};

#endif


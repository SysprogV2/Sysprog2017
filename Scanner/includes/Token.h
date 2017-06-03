
#ifndef Token_H_
#define Token_H_

//#include <string.h> // TODO: DELETE THIS LATER!!! Prohibited library!
#include <stdlib.h>  // for strtol()
#include "Information.h"
#include "../../Compatibility/compab.h"

#ifndef SIGN_ARRAY_SZ
#define SIGN_ARRAY_SZ 14
#endif
class Token {
	int tType;
	int line;
	int column;
	long int value;
	Information* information;
	char symbol;
	const char* signArray;
	char* errorMessage;
public:
	static char* nameOf(int tokenType);
	Token(int type, int line, int column);
	Token(int state, int l, int c, Information* info);
	virtual ~Token();
	char* itoc(int number);
	int getType();
	void setType(int type);
	Information* getInformation();
	char* getLexem();
	int getLine();
	int getColumn();
	long int getValue();
	void setValue(long int value);
	char getSymbol();
	void setSymbol(char symbol);
	void setInformation(Information* info);
	bool hasSameTypeAs (Token* other);
	char* getErrorMessage();
	void setErrorMessage(char* errorMessage);
};

class StringUtil {
public:
	static char* concat(char* first, char* second);
	static int calcLength(char* string);
	static char* format(char* format, ...);
};

#endif


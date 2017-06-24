/*
 * Information.h
 *
 *  Created on: Nov 11, 2015
 *      Author: arty
 */

#ifndef SCANNER_INCLUDES_INFORMATION_H_
#define SCANNER_INCLUDES_INFORMATION_H_

typedef enum {
	uncheckedType,

	intType,
	intArrayType,
	arrayType,
	noType,
	errorType
}CheckableType;

class Information {
	char* lexem;
	CheckableType type;
	Token* token;
public:
	Information(Token* token);
	Information(char* lexem, Token* token);
	virtual ~Information();
	void setLexem(char* lexem);
	char* getLexem();
	Token* getToken();
	CheckableType getType();
	bool matches(const char* other);
	void setType (CheckableType type);
};


#endif /* SCANNER_INCLUDES_INFORMATION_H_ */

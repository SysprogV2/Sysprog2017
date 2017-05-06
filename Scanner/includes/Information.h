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
public:
	Information();
	Information(char* lexem);
	virtual ~Information();
	void setLexem(char* lexem);
	char* getLexem();
	CheckableType getType();
	bool matches(const char* other);
	void setType (CheckableType type);
};


#endif /* SCANNER_INCLUDES_INFORMATION_H_ */

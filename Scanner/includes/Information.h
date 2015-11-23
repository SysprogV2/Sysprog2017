/*
 * Information.h
 *
 *  Created on: Nov 11, 2015
 *      Author: arty
 */

#ifndef SCANNER_INCLUDES_INFORMATION_H_
#define SCANNER_INCLUDES_INFORMATION_H_

class Information {
	char* lexem;
public:
	Information();
	Information(char* lexem);
	virtual ~Information();
	void setLexem(char* lexem);
	char* getLexem();
	bool matches(char* other);
};


#endif /* SCANNER_INCLUDES_INFORMATION_H_ */

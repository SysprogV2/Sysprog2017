/*
 * TokenSequence.h
 *
 *  Created on: 03.01.2016
 *      Author: work
 */

#ifndef PARSER_INCLUDES_TOKENSEQUENCE_H_
#define PARSER_INCLUDES_TOKENSEQUENCE_H_

#include "../../Compatibility/compab.h"
#include "../../Scanner/includes/Token.h"

class TokenSequence {
private:
	Token* sequence[];
	int currentPos;
	int size;
	int capacity;
	int increment;
public:
	TokenSequence (int initialCapacity, int initialIncrement);
	void add (Token* token, bool setAsCurrent);
	void clear (bool areStillReferenced);
	Token* tokenAt (int index, bool jumpTo);
	Token* current();
	Token* next (bool jumpTo);
	Token* previous (bool jumpTo);
	void setIncrement (int nextIncrement);
	int getSize();
	~TokenSequence (bool tokensReferenced);
};



#endif /* PARSER_INCLUDES_TOKENSEQUENCE_H_ */

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

typedef enum {
	AND,
	OR,
	NOR,
	NAND,
	XOR,
	XNOR
}CheckoutMode;

class TokenSequence {
private:
	Token* sequence[];
	int currentPos;
	int size;
	int capacity;
	int increment;
public:
	TokenSequence (int initialCapacity, int initialIncrement);
	TokenSequence (TokenSequence* other);
	void add (Token* token, bool setAsCurrent);
	void clear (bool areStillReferenced);
	Token* tokenAt (int index, bool jumpTo);
	Token* current();
	Token* next (bool jumpTo);
	Token* previous (bool jumpTo);
	void setIncrement (int nextIncrement);
	int getSize();
	TokenSequence* splitOn (int index, TokenSequence** subsequence2);
	~TokenSequence (bool tokensReferenced = true);
};

class TokenTypeRegistry {
private:
	bool tokenTypes[];
	const int size = 36;
public:
	TokenTypeRegistry();
	// single Token modifications do not alter the Tokens
	void set (Token* token);
	void unset (Token* token);
	void toggle (Token* token);
	// all Tokens from a Sequence modifications do not alter the Sequences
	void setAll (TokenSequence* sequence);
	void unsetAll (TokenSequence* sequence);
	void toggleAll (TokenSequence*  sequence);
	// checkout operations do not alter anything
	bool isSet (Token* token);
	bool areSet (TokenSequence* sequence, CheckoutMode mode);
	// set operations do not alter the argument (only the call Registry)
	void intersectWith (TokenTypeRegistry* other);
	void uniteWith (TokenTypeRegistry* other);
	~TokenTypeRegistry();
};



#endif /* PARSER_INCLUDES_TOKENSEQUENCE_H_ */

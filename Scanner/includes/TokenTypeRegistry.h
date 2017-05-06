/*
 * TokenTypeRegistry.h
 *
 *  Created on: 06.05.2017
 *      Author: root
 */

#ifndef SCANNER_INCLUDES_TOKENTYPEREGISTRY_H_
#define SCANNER_INCLUDES_TOKENTYPEREGISTRY_H_

#include "TokenSequence.h"

class TokenTypeRegistry {
private:
	bool* tokenTypes;
	int size;
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
	char* allSetTokenNames();
	~TokenTypeRegistry();
};



#endif /* SCANNER_INCLUDES_TOKENTYPEREGISTRY_H_ */

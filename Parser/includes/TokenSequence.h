/*
 * TokenSequence.h
 *
 *  Created on: 03.01.2016
 *      Author: work
 */

#ifndef PARSER_INCLUDES_TOKENSEQUENCE_H_
#define PARSER_INCLUDES_TOKENSEQUENCE_H_

#include "../../Compab/includes/compab.hpp"
#include "../../Scanner/includes/Token.h"
#include <iostream>

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
	Token** sequence;
	int currentPos;
	int size;
	int capacity;
	int increment;
	bool tokensReferenced;
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
	void prepareDelete(bool tokensReferenced);
	~TokenSequence ();
};

class IntQueue {
private:
	class IntLinker {
	private:
		int value;
		IntLinker* previous;
		IntLinker* next;
	public:
		IntLinker();
		~IntLinker();
		friend class IntQueue;
	};
	int size;
	IntLinker* first;
	IntLinker* last;
public:
	IntQueue();
	void push(int value);
	void undoPushing(); // title is saying what the method is meant for, however it can be used for non-fetching front delete at any time
	int pop(); // cannot be undone because it's a delete action
	int fetch(); // nothing to undo, only a reading action
	int getSize();
	~IntQueue();
};

class LabelFactory {
private:
	int currentLabelNo;
public:
	LabelFactory(int firstLabelNo);
	int newLabel();
	~LabelFactory();
};


#endif /* PARSER_INCLUDES_TOKENSEQUENCE_H_ */

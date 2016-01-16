/*
 * TokenSequence.cpp
 *
 *  Created on: 03.01.2016
 *      Author: work
 */

#include "../includes/TokenSequence.h"

TokenSequence::TokenSequence(int initialCapacity, int initialIncrement) {
	this->capacity = initialCapacity < 0 ? 0 : initialCapacity;
	this->increment = initialIncrement < 1 ? 1 : initialIncrement;
	this->sequence = new Token* [this->capacity];
	this->size = 0;
	this->currentPos = 0;
}

void TokenSequence::add (Token* token, bool setAsCurrent) {
	if (this->size == this->capacity) {
		Token* temp[] = this->sequence;
		this->capacity += this->increment;
		this->sequence = new Token* [this->capacity];
		for (int i = 0; i < this->size; i++) {
			this->sequence[i] = temp [i];
			temp [i] = nullptr;
		}
		delete[] temp;
	}
	this->sequence [this->size++] = token;
	if (setAsCurrent) {
		this->currentPos = this->size - 1;
	}
}

void TokenSequence::clear (bool areStillReferenced) {
	for (int i = 0; i < this->size; i++) {
		if (!areStillReferenced) delete this->sequence[i];
		else this->sequence[i] = nullptr;
	}
	this->size = 0;
}

Token* TokenSequence::tokenAt (int index, bool jumpTo) {
	if (jumpTo) this->currentPos = index;
	return this->sequence[index];
}

Token* TokenSequence::current() {
	return this->sequence[this->currentPos];
}

Token* TokenSequence::next (bool jumpTo) {
	if (jumpTo) this->currentPos++;
	return this->sequence [this->currentPos + (jumpTo ? 0 : 1)];
}

Token* TokenSequence::previous (bool jumpTo) {
	if (jumpTo) this->currentPos--;
	return this->sequence [this->currentPos - (jumpTo ? 0 : 1)];
}

void TokenSequence::setIncrement( int nextIncrement) {
	this->increment = nextIncrement < 1 ? 1 : nextIncrement;
}

int TokenSequence::getSize() {
	return this->size;
}

TokenSequence* TokenSequence::splitOn(int index, TokenSequence** subsequence2) {
	if (index < 0) {
		*subsequence2 = new TokenSequence (this); // subsequence2 is entire sequence
		return new TokenSequence (10, 10); // subsequence1 is empty
	}
	if (index >= this->size - 1) {
		*subsequence2 = new TokenSequence (10, 10); // subsequence2 is empty
		return new TokenSequence (this); // subsequence1 is entire sequence
	}
	TokenSequence* subsequence1 = new TokenSequence (10, 10);
	*subsequence2 = new TokenSequence (10, 10);
	// TODO modify subsequences so that:
	// - subsequence1 contains all Tokens from first (inclusive) to index (inclusive)
	// - subsequence2 contains all Tokens from index (exclusive) to last (inclusive)
	// - no array copy loop is involved
	return subsequence1;
}

TokenSequence::~TokenSequence (bool tokensReferenced) {
	this->clear(tokensReferenced);
	delete[] this->sequence;
}

TokenTypeRegistry::TokenTypeRegistry() {
	this->tokenTypes = new bool [this->size];
	for (int i = 0; i < this->size; i++) {
		this->tokenTypes[i] = false;
	}
}

void TokenTypeRegistry::set (Token* token) {
	this->tokenTypes [token->getType()] = true;
}

void TokenTypeRegistry::unset (Token* token) {
	this->tokenTypes [token->getType()] = false;
}

void TokenTypeRegistry::toggle (Token* token) {
	this->tokenTypes [token->getType()] = !this->tokenTypes [token->getType()];
}

void TokenTypeRegistry::setAll (TokenSequence* sequence) {
	for (int i = 0; i < sequence->getSize(); i++) {
		this->set(sequence->tokenAt(i, false));
	}
}

void TokenTypeRegistry::unsetAll (TokenSequence* sequence) {
	for (int i = 0; i < sequence->getSize(); i++) {
		this->unset(sequence->tokenAt(i, false));
	}
}

void TokenTypeRegistry::toggleAll (TokenSequence* sequence) {
	for (int i = 0; i < sequence->getSize(); i++) {
		this->toggle(sequence->tokenAt(i, false));
	}
}

bool TokenTypeRegistry::isSet (Token* token) {
	return this->tokenTypes[token->getType()];
}

bool TokenTypeRegistry::areSet (TokenSequence* sequence, CheckoutMode mode) {
	switch (mode) {
	case AND:
		for (int i = 0; i < sequence->getSize(); i++) {
			if (!this->isSet(sequence->tokenAt(i, false))) return false;
		}
		return true;
	case OR:
		for (int i = 0; i < sequence->getSize(); i++) {
			if (this->isSet(sequence->tokenAt(i, false))) return true;
		}
		return false;
	case NOR:
		for (int i = 0; i < sequence->getSize(); i++) {
			if (this->isSet(sequence->tokenAt(i, false))) return false;
		}
		return true;
	case NAND:
		for (int i = 0; i < sequence->getSize(); i++) {
			if (!this->isSet(sequence->tokenAt(i, false))) return true;
		}
		return false;
	case XOR:
		int registeredTokens = 0;
		for (int i = 0; i < sequence->getSize(); i++) {
			if (this->isSet(sequence->tokenAt(i, false))) registeredTokens++;
		}
		return registeredTokens % 2 == 1;
	case XNOR:
		int registeredTokens = 0;
		for (int i = 0; i < sequence->getSize(); i++) {
			if (this->isSet(sequence->tokenAt(i, false))) registeredTokens++;
		}
		return registeredTokens % 2 == 0;
	}
}

void TokenTypeRegistry::intersectWith(TokenTypeRegistry* other) {
	for (int i = 0; i < this->size; i++) {
		this->tokenTypes[i] = this->tokenTypes[i] && other->tokenTypes[i];
	}
}

void TokenTypeRegistry::uniteWith(TokenTypeRegistry* other) {
	for (int i = 0; i < this->size; i++) {
		this->tokenTypes[i] = this->tokenTypes[i] || other->tokenTypes[i];
	}
}

TokenTypeRegistry::~TokenTypeRegistry() {
	delete[] this->tokenTypes;
}

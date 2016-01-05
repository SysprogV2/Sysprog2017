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

TokenSequence::~TokenSequence (bool tokensReferenced) {
	this->clear(tokensReferenced);
	delete[] this->sequence;
}
